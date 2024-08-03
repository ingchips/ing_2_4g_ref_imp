#include "stdio.h"
#include "TEST_2P4G.h"
#include "platform_api.h"
#include "btstack_event.h"
#include "profile.h"
#include "ing_2p4g.h"

static comm_mode_t comm_mode = MODE_BLE;

static uint8_t slave_tx_len = 1;
static uint8_t tx_data[]={APP_2G4_DATA_CONNECT,5,4,2,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31}; 
static uint8_t rx_data[256];
static ING2P4G_RxPacket RxPkt111;
static ING2P4G_Config_t ing_2p4g_config;
static uint8_t continus_2g4 = 0;
void ing24g_test_switch_mode_trigger(comm_mode_t mode);

static app_2g4_ch_hop_t app_2g4_hop = {
	.channel_hop = {2391, 2417, 2430, 2445, 2460},
	.current_channel = 0,// 0-APP_2G4_HOP_CHANNEL_NUM
	.hop_cnt = 0,
    .error_cnt = 0,
};

static app_2g4_state_t app_2g4_state ={
	.state = APP_2G4_STATE_IDLE,
};

// ================================================================================

void gpio_pluse_num1(uint16_t num)
{
    uint16_t i = 0;
    for(i=0; i<num; i++)
    {
        GIO_WriteValue(PULSE_TEST_GPIO1, 1);
        GIO_WriteValue(PULSE_TEST_GPIO1, 0);
    }
}

void gpio_pluse_num2(uint16_t num)
{
    uint16_t i = 0;
    for(i=0; i<num; i++)
    {
        GIO_WriteValue(PULSE_TEST_GPIO2, 1);
        GIO_WriteValue(PULSE_TEST_GPIO2, 0);
    }
}

void gpio_pluse_num3(uint16_t num)
{
    uint16_t i = 0;
    for(i=0; i<num; i++)
    {
        GIO_WriteValue(PULSE_TEST_GPIO3, 1);
        GIO_WriteValue(PULSE_TEST_GPIO3, 0);
    }
}

void gpio_pluse_num4(uint16_t num)
{
    uint16_t i = 0;
    for(i=0; i<num; i++)
    {
        GIO_WriteValue(PULSE_TEST_GPIO4, 1);
        GIO_WriteValue(PULSE_TEST_GPIO4, 0);
    }
}

void ing_2p4g_config_init(void)
{
    ing_2p4g_config.Mode          = MODE_SLAVE;
    ing_2p4g_config.AccAddr       = 0x3234567A;
    ing_2p4g_config.PHY           = LLE_PHY_1M;
    ing_2p4g_config.Channel       = 2391;
    ing_2p4g_config.TXPOW         = 63;
    ing_2p4g_config.WhiteEn       = 0x1;
    ing_2p4g_config.WhiteIdx      = 0x0;
    ing_2p4g_config.CRCInit       = 0x123456;
    ing_2p4g_config.TimeOut       = 20;//*6.25us
    ing_2p4g_config.RxPktIntEn    = 0;
    ing_2p4g_config.TxPktIntEn    = 0;
}

void ing24g_test_do_switch_to_2p4g(void){
    if(ing_2p4g_config.Mode == MODE_MASTER){
        platform_printf("DO SWITCH 2.4G: MASTER.\n");
    } else {
        platform_printf("DO SWITCH 2.4G: SLAVE.\n");
    }
    platform_config(PLATFORM_CFG_LL_DBG_FLAGS, 32);
    ing2p4g_switch_to_2G4(&ing_2p4g_config);
    continus_2g4_txrx_on();
    app_2g4_state.state = APP_2G4_STATE_CONNECT;
    // ing2p4g_start_2p4g_rx(slave_tx_len, tx_data);
}

void ing24g_test_do_switch_to_BLE(void){
    platform_config(PLATFORM_CFG_LL_DBG_FLAGS, 0x10);
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
            ing2p4g_start_2p4g_tx(slave_tx_len, tx_data);
        }
        else
        {
            platform_printf("Start to RX ...\r\n");
//            ing2p4g_start_2p4g_rx(slave_tx_len, tx_data);
            ing2p4g_start_2p4g_rx_with_timeout(slave_tx_len, tx_data, 1, ing_2p4g_config.TimeOut);
        }

    }
    operate_flag++;
}

void app_2g4_channel_hop() {
	app_2g4_hop.hop_cnt++;
	app_2g4_hop.current_channel++;
	if(app_2g4_hop.current_channel >= APP_2G4_HOP_CHANNEL_NUM) {
		app_2g4_hop.current_channel = 0;
	}
	ing_2p4g_config.Channel = app_2g4_hop.channel_hop[app_2g4_hop.current_channel];
	ing2p4g_status_t state =  ing2p4g_set_channel(app_2g4_hop.channel_hop[app_2g4_hop.current_channel]);
	if(ING2P4G_SUCCESS != state){
        platform_printf("[2G4]Hop tx fail\n");
    }
}

void app_2g4_channel_init() {
	app_2g4_hop.hop_cnt = 0;
	app_2g4_hop.current_channel = 0;
	ing_2p4g_config.Channel = app_2g4_hop.channel_hop[app_2g4_hop.current_channel];
	ing2p4g_status_t state =  ing2p4g_set_channel(app_2g4_hop.channel_hop[app_2g4_hop.current_channel]);
	if(ING2P4G_SUCCESS != state){
        platform_printf("[2G4]Hop tx fail\n");
    }
}

void app_2g4_channel_hop_begin(void) {
    platform_printf("[2G4]hop begin\n");
    app_2g4_hop.hop_cnt = 0;
	app_2g4_state.state = APP_2G4_STATE_FRE_HOPPING;
	app_2g4_channel_hop();
	slave_tx_len = 1;
	tx_data[0]= APP_2G4_DATA_FRE_HOP;
}

void app_2g4_channel_hop_stop(void) {
    platform_printf("[2G4]hop fail and stop\n");
    app_2g4_hop.hop_cnt = 0;
	app_2g4_state.state = APP_2G4_STATE_CONNECT;
	app_2g4_channel_init();
	slave_tx_len = 1;
	tx_data[0]= APP_2G4_DATA_FRE_HOP;
}

static void rx_ack_data_handle(ING2P4G_RxPacket *rx_packet) {
    switch(app_2g4_state.state){
		case APP_2G4_STATE_IDLE: {
			platform_printf("[2G4]Error line:%d\n", __LINE__);
			break;
		}
        case APP_2G4_STATE_CONNECT:{
            app_2g4_state.state = APP_2G4_STATE_COMMNUICATING;
            tx_data[0] = APP_2G4_DATA_COMMUNICATE;
            slave_tx_len = 1;
            break;
        }
		case APP_2G4_STATE_COMMNUICATING:{
            app_2g4_hop.error_cnt = 0;
			tx_data[0] = APP_2G4_DATA_COMMUNICATE;
            slave_tx_len = 1;
			break;
		}
		case APP_2G4_STATE_FRE_HOPPING:{
			app_2g4_hop.error_cnt = 0;
            app_2g4_hop.hop_cnt = 0;
            app_2g4_state.state = APP_2G4_STATE_COMMNUICATING;
            tx_data[0] = APP_2G4_DATA_COMMUNICATE;
            slave_tx_len = 1;
            platform_printf("[2G4]hop success ch:%d\n", app_2g4_hop.current_channel);
			break;
		}
        default:{
            platform_printf("[2G4]Error mode\n");
            break;
        }
    }
}

static void rx_noack_data_handle(ING2P4G_RxPacket *rx_packet) {
    switch(app_2g4_state.state){
		case APP_2G4_STATE_IDLE: {
			platform_printf("[2G4]Error line:%d\n", __LINE__);
			break;
		}
        case APP_2G4_STATE_CONNECT:{
            tx_data[0] = APP_2G4_DATA_CONNECT;
            slave_tx_len = 1;
            break;
        }
		case APP_2G4_STATE_COMMNUICATING:{
			app_2g4_hop.error_cnt++;
            if(app_2g4_hop.error_cnt > APP_2G4_HOP_BEGIN_NUM)
            {
                app_2g4_channel_hop_begin();
            }
			break;
		}
		case APP_2G4_STATE_FRE_HOPPING:{
            tx_data[0] = APP_2G4_DATA_FRE_HOP;
            slave_tx_len = 1;
            app_2g4_hop.hop_cnt++;
            if(app_2g4_hop.hop_cnt > APP_2G4_HOP_STOP_NUM)
            {
                app_2g4_channel_hop_stop();
            }
			break;
		}
        default:{
            platform_printf("[2G4]Error mode\n");
            break;
        }
    }
}

ADDITIONAL_ATTRIBUTE static void EventIrqCallBack(void)
{
    static ing2p4g_work_mode_t mode;

    ing2p4g_clear_event_int();
    ing2p4g_get_2g4_work_mode(&mode);
    ing2p4g_status_t status = ing2p4g_get_rx_data(&RxPkt111);

    if(!status) {
		rx_ack_data_handle(&RxPkt111);
//        gpio_pluse_num1(1);
	}
    else {
        rx_noack_data_handle(&RxPkt111);
//        gpio_pluse_num2(1);
    }
    
    
    if(continus_2g4 == 1)
    {
        ing2p4g_start_2p4g_rx(slave_tx_len, tx_data);
    }
}

static void RxPktIrqCallBack(void)
{
    ing2p4g_clear_rx_int();
}

ADDITIONAL_ATTRIBUTE static void TxPktIrqCallBack(void)
{
    ing2p4g_clear_tx_int();
}

void ing24g_test_init(void){
    ing2p4g_set_irq_callback(ING2P4G_CB_EVENT, EventIrqCallBack);
    ing2p4g_set_irq_callback(ING2P4G_CB_RX, RxPktIrqCallBack);
    ing2p4g_set_irq_callback(ING2P4G_CB_TX, TxPktIrqCallBack);
    ing_2p4g_config_init();
}

