#include <stdio.h>
#include <string.h>
#include "profile.h"
#include "ingsoc.h"
#include "platform_api.h"
#include "FreeRTOS.h"
#include "task.h"
#include "trace.h"
#include "TEST_2P4G.h"



static uint32_t cb_hard_fault(hard_fault_info_t *info, void *_)
{
    platform_printf("HARDFAULT:\nPC : 0x%08X\nLR : 0x%08X\nPSR: 0x%08X\n"
                    "R0 : 0x%08X\nR1 : 0x%08X\nR2 : 0x%08X\nR3 : 0x%08X\n"
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
}

uint32_t on_lle_init(void *dummy, void *user_data)
{
    (void)(dummy);
    (void)(user_data);
    return 0;
}

#define LOW_POWER_WAKE_UP_GPIO      GIO_GPIO_9
#define LOW_POWER_WAKE_UP_LEVEL     1

void key_board_wake_up_enable(void) {
    PINCTRL_SetPadMux(LOW_POWER_WAKE_UP_GPIO, IO_SOURCE_GPIO);
    PINCTRL_Pull(LOW_POWER_WAKE_UP_GPIO, PINCTRL_PULL_UP);
    GIO_SetDirection(LOW_POWER_WAKE_UP_GPIO, GIO_DIR_INPUT);
    GIO_EnableDeepSleepWakeupSource(LOW_POWER_WAKE_UP_GPIO, 1, GIO_WAKEUP_MODE_LOW_LEVEL, PINCTRL_PULL_UP);
    return;
}

#define w32(a,b) *(volatile uint32_t*)(a) = (uint32_t)(b)
#define r32(a)   *(volatile uint32_t*)(a)

#define ING916_SW_PATCH_001 (0)

//w32(0x4010012c,(r32(0x4010012c) & (~(0x1 << 7))) | (0x0 << 7)); // disable rtc
//w32(0x4010012c,(r32(0x4010012c) & (~(0x1 << 7))) | (0x1 << 7)); // enable rtc
//printf("read rtc en:%d\n", (r32(0x4010012c)>>7 & 0x1)); // read rtc en bit

void rtc_wakeup_interrupt_set(uint8_t en)
{
    if(en){
        w32(0x4010012c,(r32(0x4010012c) & (~(0x1 << 7))) | (0x1 << 7)); // enable rtc wakeup function.
    } else {
        w32(0x4010012c,(r32(0x4010012c) & (~(0x1 << 7))) | (0x0 << 7)); // disable rtc wakeup function.
    }
}

uint8_t rtc_wakeup_interrupt_get(void)
{
    return ((r32(0x4010012c) >> 7) & 0x1);
}

uint32_t rtc_wakeup_interrupt_compare_counter_get(void)
{
    return r32(0x40102004);
}

uint32_t rtc_timer_wakeup_running_check(void)
{
    uint32_t status = 0;
    
    // TODO: 如果任何使用软件定时唤醒相关资源的情况发生，需设置 status = 1;
    // - RTOS的task中的vTaskDelay被调用
    // - RTOS周期性timer被创建并启动，或单次触发timer被启动但回调还未产生。
    // - platform_set_timer 被启动，但回调还未产生。
    // - platform_set_abs_timer 被启动，但回调还未产生。
    // - platform_create_us_timer 被启动，但回调还未产生。
    // - 蓝牙处于活动状态：
    //   - 周期性广播；
    //   - 保持连接（周期性连接事件唤醒）；
    //   - 其它启动host软件定时器的行为；
    // - 其它未列出的使用RTC定时唤醒MCU的场景。
    status = 1;
    
    return status;
}

static uint32_t test_wkup_cnt = 0;

uint32_t on_deep_sleep_wakeup(void *dummy, void *user_data)
{
    SYSCTRL_WakeupSource_t source = {0};
    uint8_t ret;
    uint32_t i;
    
    const platform_wakeup_call_info_t *info = dummy;
    
    (void)(dummy);
    (void)(user_data);
    GIO_EnableRetentionGroupB(0);
    GIO_EnableRetentionGroupA(0);
    
    setup_peripherals();
    
    printf("wkup_cnt:%d\n", rtc_wakeup_interrupt_compare_counter_get());
    printf("rtc_en:%d\n", rtc_wakeup_interrupt_get()); // read rtc en bit
    
    ret = SYSCTRL_GetLastWakeupSource(&source);
    if (PLATFORM_WAKEUP_REASON_NORMAL == info->reason) {
        
    } else if(PLATFORM_WAKEUP_REASON_ABORTED == info->reason) {
        
    }
    
    return 0;
}

uint32_t query_deep_sleep_allowed(void *dummy, void *user_data)
{
    (void)(dummy);
    (void)(user_data);
    
    key_board_wake_up_enable();
    SYSCTRL_EnableWakeupSourceDetection();			//使能获取唤醒源
    
    printf("slp rtc_en:%d\n", rtc_wakeup_interrupt_get()); // read rtc en bit
    while (apUART_Check_TXFIFO_EMPTY(PRINT_PORT) == 0);
    
    GIO_EnableRetentionGroupB(1);						//锁存IO
    GIO_EnableRetentionGroupA(1);
    
    uint32_t is_app_sleep_allow_now = 0;
    is_app_sleep_allow_now |= (!(app_2g4_rf_state()));
    if(is_app_sleep_allow_now){
        
        
#if ING916_SW_PATCH_001
        if(rtc_timer_wakeup_running_check()){
            rtc_wakeup_interrupt_set(0); // disable rtc interrupt wakeup function.
        }
#endif
        
    }
    
    // TODO: return 0 if deep sleep is not allowed now; else deep sleep is allowed
    return is_app_sleep_allow_now;
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
        [PLATFORM_CB_EVT_ON_DEEP_SLEEP_WAKEUP] = {
            .f = (f_platform_evt_cb)on_deep_sleep_wakeup,
        },
        [PLATFORM_CB_EVT_QUERY_DEEP_SLEEP_ALLOWED] = {
            .f = query_deep_sleep_allowed,
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

int app_main()
{
    SYSCTRL_Init();
    // setup event handlers
    platform_set_evt_callback_table(&evt_cb_table);

    platform_config(PLATFORM_CFG_POWER_SAVING, PLATFORM_CFG_ENABLE);    
    setup_peripherals();

    trace_rtt_init(&trace_ctx);
    // TODO: config trace mask
    platform_config(PLATFORM_CFG_TRACE_MASK, 0);
    ing2p4g_init_dual_mode();
    ing24g_test_init();
    SYSCTRL_SelectMemoryBlocks(SYSCTRL_RESERVED_MEM_BLOCKS);

    return 0;
}

