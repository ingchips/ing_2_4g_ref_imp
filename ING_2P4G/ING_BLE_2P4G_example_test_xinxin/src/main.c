#include <stdio.h>
#include <string.h>
#include "profile.h"
#include "ingsoc.h"
#include "platform_api.h"
#include "FreeRTOS.h"
#include "task.h"
#include "trace.h"
#include "ll_api.h"
#include "../data/setup_soc.cgen"

#include "TEST_2P4G.h"
#include "uart_console.h"

#define SWITCH_KEY_GPIO     GIO_GPIO_10

static uint32_t cb_hard_fault(hard_fault_info_t *info, void *_)
{
    platform_printf("HARDFAULT:\nPC : 0x%08X\nLR : 0x%08X\nPSR: 0x%08X\n"
                    "R0 : 0x%08X\nR1 : 0x%08X\nR2 : 0x%08X\nP3 : 0x%08X\n"
                    "R12: 0x%08X\n",
                    info->pc, info->lr, info->psr,
                    info->r0, info->r1, info->r2, info->r3, info->r12);
    for (;;);
}

static uint32_t cb_assertion(assertion_info_t *info, void *_)
{
    platform_printf("[ASSERTION] @ %s:%d\n",
                    info->file_name,
                    info->line_no);
    for (;;);
}

static uint32_t cb_heap_out_of_mem(uint32_t tag, void *_)
{
    platform_printf("[OOM] @ %d\n", tag);
    for (;;);
}

#define PRINT_PORT    APB_UART0

uint32_t cb_putc(char *c, void *dummy)
{
    while (apUART_Check_TXFIFO_FULL(PRINT_PORT) == 1);
    UART_SendData(PRINT_PORT, (uint8_t)*c);
    return 0;
}

int fputc(int ch, FILE *f)
{
    cb_putc((char *)&ch, NULL);
    return ch;
}

void config_uart(uint32_t freq, uint32_t baud)
{
    UART_sStateStruct config;

    config.word_length       = UART_WLEN_8_BITS;
    config.parity            = UART_PARITY_NOT_CHECK;
    config.fifo_enable       = 1;
    config.two_stop_bits     = 0;
    config.receive_en        = 1;
    config.transmit_en       = 1;
    config.UART_en           = 1;
    config.cts_en            = 0;
    config.rts_en            = 0;
    config.rxfifo_waterlevel = 1;
    config.txfifo_waterlevel = 1;
    config.ClockFrequency    = freq;
    config.BaudRate          = baud;

    apUART_Initialize(PRINT_PORT, &config, (1 << bsUART_RECEIVE_INTENAB) | (1 << bsUART_TIMEOUT_INTENAB));
}

void setup_peripherals(void)
{
    config_uart(OSC_CLK_FREQ, 115200);
    SYSCTRL_ClearClkGateMulti(  (1 << SYSCTRL_ClkGate_APB_GPIO0)
                              | (1 << SYSCTRL_ClkGate_APB_PinCtrl)
                              | (1 << SYSCTRL_ClkGate_APB_TMR0)
                              | (1 << SYSCTRL_ClkGate_APB_GPIO1));

    PINCTRL_SetPadMux(SWITCH_KEY_GPIO, IO_SOURCE_GPIO);
    GIO_SetDirection(SWITCH_KEY_GPIO, GIO_DIR_INPUT);
    PINCTRL_Pull(SWITCH_KEY_GPIO, PINCTRL_PULL_UP);
    GIO_ConfigIntSource(SWITCH_KEY_GPIO,
                        GIO_INT_EN_LOGIC_LOW_OR_FALLING_EDGE,
                        GIO_INT_EDGE);
    GIO_DebounceCtrl(1, 200, GIO_DB_CLK_32K);
    GIO_DebounceEn(SWITCH_KEY_GPIO, 1);

    PINCTRL_SetPadMux(PULSE_TEST_GPIO1, IO_SOURCE_GPIO);
    GIO_SetDirection(PULSE_TEST_GPIO1, GIO_DIR_OUTPUT);
    GIO_WriteValue(PULSE_TEST_GPIO1, 0);
    PINCTRL_SetPadMux(PULSE_TEST_GPIO2, IO_SOURCE_GPIO);
    GIO_SetDirection(PULSE_TEST_GPIO2, GIO_DIR_OUTPUT);
    GIO_WriteValue(PULSE_TEST_GPIO2, 0);
    PINCTRL_SetPadMux(PULSE_TEST_GPIO3, IO_SOURCE_GPIO);
    GIO_SetDirection(PULSE_TEST_GPIO3, GIO_DIR_OUTPUT);
    GIO_WriteValue(PULSE_TEST_GPIO3, 0);
    PINCTRL_SetPadMux(PULSE_TEST_GPIO4, IO_SOURCE_GPIO);
    GIO_SetDirection(PULSE_TEST_GPIO4, GIO_DIR_OUTPUT);
    GIO_WriteValue(PULSE_TEST_GPIO4, 0);
    
    PINCTRL_SetPadMux(PULSE_TEST_GPIO5, IO_SOURCE_GPIO);
    GIO_SetDirection(PULSE_TEST_GPIO5, GIO_DIR_OUTPUT);
    GIO_WriteValue(PULSE_TEST_GPIO5, 0);
    PINCTRL_SetPadMux(PULSE_TEST_GPIO6, IO_SOURCE_GPIO);
    GIO_SetDirection(PULSE_TEST_GPIO6, GIO_DIR_OUTPUT);
    GIO_WriteValue(PULSE_TEST_GPIO6, 0);
}

uint32_t on_lle_init(void *dummy, void *user_data)
{
    (void)(dummy);
    (void)(user_data);
    cube_on_lle_init();
    return 0;
}

uint32_t on_deep_sleep_wakeup(const platform_wakeup_call_info_t *info, void *user_data)
{

    if (PLATFORM_WAKEUP_REASON_NORMAL == info->reason)
        setup_peripherals();
    else
        GIO_EnableRetentionGroupA(0);
    platform_printf("w:%d,%d", info->reason, info->mode);
    return 1;
}

uint32_t query_deep_sleep_allowed(void *dummy, void *user_data)
{
    (void)(dummy);
    (void)(user_data);

    GIO_EnableRetentionGroupA(1);

    return PLATFORM_ALLOW_DEEP_SLEEP;
}

trace_rtt_t trace_ctx = {0};


static const platform_evt_cb_table_t evt_cb_table =
{
    .callbacks = {
        [PLATFORM_CB_EVT_HARD_FAULT] = {
            .f = (f_platform_evt_cb)cb_hard_fault,
        },
        [PLATFORM_CB_EVT_ASSERTION] = {
            .f = (f_platform_evt_cb)cb_assertion,
        },
        [PLATFORM_CB_EVT_HEAP_OOM] = {
            .f = (f_platform_evt_cb)cb_heap_out_of_mem,
        },
        [PLATFORM_CB_EVT_PROFILE_INIT] = {
            .f = setup_profile,
        },
        [PLATFORM_CB_EVT_LLE_INIT] = {
            .f = on_lle_init,
        },
        [PLATFORM_CB_EVT_PUTC] = {
            .f = (f_platform_evt_cb)cb_putc,
        },
        [PLATFORM_CB_EVT_TRACE] = {
            .f = (f_platform_evt_cb)cb_trace_rtt,
            .user_data = &trace_ctx,
        },
        [PLATFORM_CB_EVT_ON_DEEP_SLEEP_WAKEUP] = {
            .f = (f_platform_evt_cb)on_deep_sleep_wakeup
        },
        [PLATFORM_CB_EVT_QUERY_DEEP_SLEEP_ALLOWED] = {
            .f = query_deep_sleep_allowed
        },
    }
};

uint32_t gpio_isr(void *user_data)
{
    GIO_ClearAllIntStatus();
    ing24g_test_switch_mode_handler();    
    return 0;
}

uint32_t uart_isr(void *user_data)
{
    uint32_t status;

    while(1)
    {
        status = apUART_Get_all_raw_int_stat(APB_UART0);
        if (status == 0)
            break;

        APB_UART0->IntClear = status;

        while (apUART_Check_RXFIFO_EMPTY(APB_UART0) != 1)
        {
            char c = APB_UART0->DataRead;
            console_rx_data(&c, 1);
        }
    }
    return 0;
}

int app_main()
{
    cube_soc_init();

    // setup event handlers
    platform_set_evt_callback_table(&evt_cb_table);

    setup_peripherals();
    SYSCTRL_Init();

    trace_rtt_init(&trace_ctx);
    // TODO: config trace mask
    platform_config(PLATFORM_CFG_TRACE_MASK, 0);
    platform_set_irq_callback(PLATFORM_CB_IRQ_GPIO, gpio_isr, NULL);
    platform_set_irq_callback(PLATFORM_CB_IRQ_UART0, uart_isr, NULL);

    platform_config(PLATFORM_CFG_LL_DBG_FLAGS, 0x10);
    // BLE and ing2.4g dual mode init.
    ing2p4g_init_dual_mode();
    uart_console_start();
    // 2.4G init.
    ing24g_test_init();
    //platform_config(PLATFORM_CFG_POWER_SAVING, PLATFORM_CFG_ENABLE);

    return 0;
}

