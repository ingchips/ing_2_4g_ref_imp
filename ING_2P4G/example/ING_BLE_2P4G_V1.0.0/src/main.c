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

#include "../2P4G/ing_2p4g.h"
#include "../2P4G/BLE_2p4g_Switch.h"

#define switch_key GIO_GPIO_10

static uint16_t miss_cnt = 0;
static uint16_t miss_time = 0;
static uint16_t ack_cnt = 0;

static uint16_t gpio_cnt = 0;

static comm_mode_t comm_mode = MODE_BLE;

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

    apUART_Initialize(PRINT_PORT, &config, 0);
}

void setup_peripherals(void)
{
    config_uart(OSC_CLK_FREQ, 115200);
    SYSCTRL_ClearClkGateMulti(  (1 << SYSCTRL_ClkGate_APB_GPIO0)
                              | (1 << SYSCTRL_ClkGate_APB_PinCtrl)
                              | (1 << SYSCTRL_ClkGate_APB_TMR0));

    PINCTRL_SetPadMux(switch_key, IO_SOURCE_GPIO);
    GIO_SetDirection(switch_key, GIO_DIR_INPUT);
    GIO_ConfigIntSource(switch_key,
                        GIO_INT_EN_LOGIC_LOW_OR_FALLING_EDGE,
                        GIO_INT_EDGE);
    GIO_DebounceCtrl(1, 200, GIO_DB_CLK_32K);
    GIO_DebounceEn(switch_key, 1);
}

uint32_t on_lle_init(void *dummy, void *user_data)
{
    (void)(dummy);
    (void)(user_data);
    cube_on_lle_init();
    return 0;
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
    }
};


static uint8_t len = 30;
static uint8_t tx_data[]={0,5,4,2,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31}; 
static uint8_t rx_data[256];
ING2P4G_RxPacket   RxPkt111;
    
uint32_t gpio_isr(void *user_data)
{
    static uint8_t gpio_isr_cnt = 0;
    GIO_ClearAllIntStatus();
    
    if(gpio_isr_cnt == 0)
    {
        switch_mode(MODE_2G4);
        platform_printf("to 2.4g\r\n");
    }
    else
    {
#if DEF_MASTER
        start_2p4g_TX(len, tx_data);
#else
        start_2p4g_RX(len, tx_data);
#endif
    }
    gpio_isr_cnt++;
    return 0;
}

void pacent_cnt(uint16_t count, uint8_t rev_flg)
{
    if(rev_flg == 0)
    {
        ack_cnt++;
    }
    else
    {
        miss_cnt++;
    }
    if(ack_cnt > count)
    {
        if(miss_cnt > 0)
        {
            miss_time++;
        }
        printf("1000 packet! miss: %d, misstime:%d\r\n", miss_cnt, miss_time);
        ack_cnt = 0;
        miss_cnt = 0;
    }
}

void print_data(uint8_t len, uint8_t *data)
{
    uint8_t i = 0;
    platform_printf("%d data:", len);
    for(i=0; i<len; i++)
    {
        platform_printf("%d ", data[i]);
    }
    platform_printf("\r\n");
}
void EventIrqCallBack(void)
{
    uint8_t i;
    uint8_t flag;
    clear_event_int();
    flag = GetRxData(&RxPkt111);

    tx_data[0]++;

#if DEF_MASTER
        pacent_cnt(1000, flag);
        start_2p4g_TX(len, tx_data);
#else
        start_2p4g_RX(len, tx_data);
        print_data(RxPkt111.DataLen, RxPkt111.Data);
#endif

}

void RxPktIrqCallBack(void)
{
    //uint8_t flag = GetRxData(rx_data, &len);
    clear_rx_int();
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
    
    ing2p4g_set_irq_callback(ING2P4G_CB_EVENT, EventIrqCallBack);
    ing2p4g_set_irq_callback(ING2P4G_CB_RX, RxPktIrqCallBack);
    
    init_dual_mode();

    return 0;
}

