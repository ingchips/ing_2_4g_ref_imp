#include "stdio.h"
#include "TEST_2P4G.h"
#include "platform_api.h"
#include "btstack_event.h"
#include "profile.h"
#include "ing_2p4g.h"

#define PULSE_TEST_GPIO     GIO_GPIO_28

static comm_mode_t comm_mode = MODE_BLE;

static uint8_t master_tx_len = 20;
static uint8_t slave_tx_len = 4;
static uint8_t tx_data[]={0,5,4,2,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31}; 
static uint8_t rx_data[256];
static ING2P4G_RxPacket RxPkt111;
static ING2P4G_Config_t ing_2p4g_config;
static uint8_t continus_2g4 = 0;
void ing24g_test_switch_mode_trigger(comm_mode_t mode);

// ================================================================================

void gpio_pluse_num(uint16_t num)
{
    uint16_t i = 0;
    for(i=0; i<num; i++)
    {
        GIO_WriteValue(PULSE_TEST_GPIO, 1);
        GIO_WriteValue(PULSE_TEST_GPIO, 0);
    }
}
void ing_2p4g_config_init(void)
{
    ing_2p4g_config.Mode          = MODE_MASTER;
    ing_2p4g_config.AccAddr       = 0x1234567A;
    ing_2p4g_config.PHY           = LLE_PHY_2M;
    ing_2p4g_config.Channel       = 2400;
    ing_2p4g_config.TXPOW         = 63;
    ing_2p4g_config.WhiteEn       = 0x1;
    ing_2p4g_config.WhiteIdx      = 0x0;
    ing_2p4g_config.CRCInit       = 0x123456;
    ing_2p4g_config.TimeOut       = 1600;//10000;//6.25s
    ing_2p4g_config.RxPktIntEn    = 1;
    ing_2p4g_config.TxPktIntEn    = 1;
}

void ing24g_test_do_switch_to_2p4g(void){
    if(ing_2p4g_config.Mode == MODE_MASTER){
        platform_printf("DO SWITCH 2.4G: MASTER.\n");
    } else {
        platform_printf("DO SWITCH 2.4G: SLAVE.\n");
    }
    ing2p4g_switch_to_2G4(&ing_2p4g_config);
}

void ing24g_test_do_switch_to_BLE(void){
    ing2p4g_switch_to_ble_mode_start();
    ing2p4g_switch_to_BLE();
}

void continus_2g4_txrx_on(void)
{
    continus_2g4 = 1;
}

void continus_2g4_txrx_off(void)
{
    continus_2g4 = 0;
}
// ================================================================================
static void ble_switch_to_ble_trigger(void){
    ing2p4g_work_state_t state;
    if (ing2p4g_get_state(&state) == ING2P4G_SUCCESS){
        if (state == ING2P4G_STATE_IDLE){
            // do switch.
            platform_printf("DO SWITCH BLE\n");
            ing24g_test_do_switch_to_BLE();
        } else {
            // 2.4G not idle, re-trigger switch to ble mode.
            ing24g_test_switch_mode_trigger(MODE_BLE);
        }
    } else {
        // is already BLE mode.
        platform_printf("Already BLE mode.\n");
    }
}

// ================================================================================

void ing24g_test_switch_mode_callback(void *data, uint16_t usr_val){
    comm_mode_t mode = (comm_mode_t)usr_val;
    switch (mode)
    {
        case MODE_2G4:
        {
            comm_mode = MODE_2G4;
            ble_switch_to_2p4g_trigger();
            break;
        }
        case MODE_BLE:
        {
            comm_mode = MODE_BLE;
            ble_switch_to_ble_trigger();
            break;
        }
    }
}

void ing24g_test_switch_mode_trigger(comm_mode_t mode)
{
    btstack_push_user_runnable(ing24g_test_switch_mode_callback, NULL, (uint16_t)mode);
}

// ================================================================================
void ing24g_test_switch_mode_handler(void)
{
    static uint8_t operate_flag = 0; 
    static ing2p4g_work_mode_t mode;
    ing2p4g_get_2g4_work_mode(&mode);
    if(operate_flag == 0)
    {
        ing24g_test_switch_mode_trigger(MODE_2G4);
        platform_printf("to 2.4g ...\r\n");
    }
    else
    {
        if(mode == MODE_MASTER)
        {
            platform_printf("Start to TX ...\r\n");
            ing2p4g_start_2p4g_tx(master_tx_len, tx_data);
        }
        else
        {
            platform_printf("Start to RX ...\r\n");
            ing2p4g_start_2p4g_rx(slave_tx_len, tx_data);
        }

    }
    operate_flag++;
}

static void percent_cnt(uint16_t T_CNT, ing2p4g_status_t status, int8_t rssi)
{
    static uint16_t test_cnt = 0;
    static uint16_t ack_cnt = 0;
    static uint16_t miss_cnt = 0;
    static uint32_t tick_start, tick_end;

    test_cnt++;
    if(status == ING2P4G_SUCCESS){
        ack_cnt++;
    }else{
        miss_cnt++;
    }

    if(test_cnt >= T_CNT)
    {
        tick_end = platform_get_us_time();
        double rate = 1000*ack_cnt/(float)(tick_end - tick_start);
        //platform_printf("tick_interval:%d us\n", (tick_end - tick_start));
        platform_printf("Test %d packet! miss: %d,rev: %d, rate: %.3fK pack/s, rssi:%d\r\n", T_CNT, miss_cnt, ack_cnt, rate, rssi);
        ack_cnt = 0;
        miss_cnt = 0;
        test_cnt = 0;
        tick_start = platform_get_us_time();
    }
}

ADDITIONAL_ATTRIBUTE static void EventIrqCallBack(void)
{
    static ing2p4g_work_mode_t mode;

    ing2p4g_clear_event_int();
    ing2p4g_get_2g4_work_mode(&mode);
    ing2p4g_status_t status = ing2p4g_get_rx_data(&RxPkt111);

    tx_data[0]++;
    gpio_pluse_num(1);
    if(continus_2g4 == 1)
    {
        if(mode == MODE_MASTER)
        {
            percent_cnt(1000, status, RxPkt111.RSSI);
            ing2p4g_start_2p4g_tx(master_tx_len, tx_data);
        }
        else
        {
            ing2p4g_start_2p4g_rx(slave_tx_len, tx_data);
        }
    }
}

static void RxPktIrqCallBack(void)
{
    //ing2p4g_err_bit_pos_t status = ing2p4g_get_rx_data(&RxPkt111);
    ing2p4g_clear_rx_int();
    gpio_pluse_num(1);
}

ADDITIONAL_ATTRIBUTE static void TxPktIrqCallBack(void)
{
    //ing2p4g_err_bit_pos_t status = ing2p4g_get_rx_data(&RxPkt111);
    ing2p4g_clear_tx_int();
    gpio_pluse_num(2);
}

void ing24g_test_init(void){
    ing2p4g_set_irq_callback(ING2P4G_CB_EVENT, EventIrqCallBack);
    ing2p4g_set_irq_callback(ING2P4G_CB_RX, RxPktIrqCallBack);
    ing2p4g_set_irq_callback(ING2P4G_CB_TX, TxPktIrqCallBack);
    ing_2p4g_config_init();
}

