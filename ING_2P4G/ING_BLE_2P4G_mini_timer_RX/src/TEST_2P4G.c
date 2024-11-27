#include "stdio.h"
#include "TEST_2P4G.h"
#include "platform_api.h"
#include "btstack_event.h"
#include "profile.h"
#include "ing_2p4g.h"

//#define TIMER_RELOAD_TIME   5940
// #define TIMER_RELOAD_TIME   7940
#define TIMER_RELOAD_TIME   3600
static comm_mode_t comm_mode = MODE_BLE;

static uint8_t master_tx_len = MASTER_COM_DATA_LEN;
static uint8_t slave_tx_len = 10;
static uint8_t tx_data[]={0,5,4,2,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31}; 
static uint8_t tx_data1[]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; 
static uint8_t rx_data[256];
static ING2P4G_RxPacket RxPkt111;
static ING2P4G_Config_t ing_2p4g_config;
static uint8_t continus_2g4 = 0;
void ing24g_test_switch_mode_trigger(comm_mode_t mode);
    
static  volatile uint8_t app_2g4_rf_going = 0;

// static uint8_t app_2g4_timer_enable = 0; //0:tx at event cb; 1-tx at timer2 cb

static app_2g4_ch_hop_t app_2g4_hop = {
	.channel_hop = {2391, 2417, 2430, 2445, 2460},
	.current_channel = 0,// 0-APP_2G4_HOP_CHANNEL_NUM
	.hop_cnt = 0,
    .error_cnt = 0,
};

static app_2g4_state_t app_2g4_state ={
	.state = APP_2G4_STATE_IDLE,
};

void app_2g4_init(void)
{
    app_2g4_state.state = APP_2G4_STATE_IDLE;
    app_2g4_hop.current_channel = 0;
    app_2g4_hop.hop_cnt = 0;
    app_2g4_hop.error_cnt = 0;
}

uint8_t app_2g4_rf_state(void)
{
    return app_2g4_rf_going;
}

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
    ing_2p4g_config.PHY           = LLE_PHY_2M;
    ing_2p4g_config.Channel       = 2391;
    ing_2p4g_config.TXPOW         = 0x3f;
    ing_2p4g_config.WhiteEn       = 0x1;
    ing_2p4g_config.WhiteIdx      = 0x0;
    ing_2p4g_config.CRCInit       = 0x123456;
    ing_2p4g_config.TimeOut       = 500;//*6.25us
    ing_2p4g_config.RxPktIntEn    = 1;
    ing_2p4g_config.TxPktIntEn    = 0;
}

static uint32_t IRQHandler_TIMER2_INT(void* user_data)
{
    ing2p4g_work_state_t state_2p4g;
    TMR_IntClr(APB_TMR2, 0, 0x1);
    static int8_t cnt = 0;
    
//    platform_printf("timer2\n");
    TMR_Enable(APB_TMR2, 0, 0);
    TMR_SetReload(APB_TMR2, 0, TIMER_RELOAD_TIME);   // 1ms 
    TMR_Enable(APB_TMR2, 0, 1);
    // ing2p4g_get_state(&state_2p4g);
    // if((state_2p4g == ING2P4G_STATE_IDLE))
    // {
    //     gpio_pluse_num3(1);
    // }
    // else{
    //     ing24g_rf_stop();
    //     gpio_pluse_num4(1);
    // }
    gpio_pluse_num1(1);
    ing24g_rf_stop();
    ing2p4g_start_2p4g_rx_with_timeout(slave_tx_len, tx_data, 0, ing_2p4g_config.TimeOut);

    return 0;
}


void test_2p4g_timer_init(void)
{
    SYSCTRL_ClearClkGateMulti( (1 << SYSCTRL_ITEM_APB_SysCtrl)
                              |(1 << SYSCTRL_ITEM_APB_PinCtrl)
                              |(1 << SYSCTRL_ITEM_APB_TMR2));
    TMR_SetOpMode(APB_TMR2, 0, TMR_CTL_OP_MODE_32BIT_TIMER_x1, TMR_CLK_MODE_EXTERNAL, 0);//timer mode set
    TMR_IntEnable(APB_TMR2, 0, 0x01);
    uint32_t timer_clk_fre = TMR_GetClk(APB_TMR2, 0);
    platform_set_irq_callback(PLATFORM_CB_IRQ_TIMER2, IRQHandler_TIMER2_INT, 0);

    return;
}
void app_2g4_channel_init(void);

void ing24g_test_do_switch_to_2p4g(void){
    if(ing_2p4g_config.Mode == MODE_MASTER){
        platform_printf("DO SWITCH 2.4G: MASTER.\n");
    } else {
        platform_printf("DO SWITCH 2.4G: SLAVE.\n");
    }
    platform_config(PLATFORM_CFG_LL_DBG_FLAGS, 32);
    ing2p4g_switch_to_2G4(&ing_2p4g_config);
    app_2g4_init();
    // app_2g4_channel_init();
    continus_2g4_txrx_on();
}

void ing24g_test_do_switch_to_BLE(void){
    platform_config(PLATFORM_CFG_LL_DBG_FLAGS, 0x10);
    ing2p4g_switch_to_ble_mode_start();
    ing2p4g_switch_to_BLE();
}

static void *master_2g4_tx_ustimer_cb(platform_us_timer_handle_t timer_handle, uint64_t time_us, void *param) {

	platform_create_us_timer((platform_get_us_time() + TEST_TX_INTERVAL), master_2g4_tx_ustimer_cb, NULL);
//    gpio_pluse_num1(4);
    ing2p4g_lle_init();
    ing2p4g_start_2p4g_rx_with_timeout(slave_tx_len, tx_data, 0, ing_2p4g_config.TimeOut);
    app_2g4_rf_going = 1;
//    platform_printf("[2G4]:timer tx:%d\n", status);
    return 0;
}

void continus_2g4_txrx_on(void)
{
    continus_2g4 = 1;

    // app_2g4_timer_enable = 1;
//    app_2g4_state.state = APP_2G4_STATE_CONNECT;
//    app_2g4_channel_init();

    #if (TX_USE_TIMER == 1)
    platform_create_us_timer((platform_get_us_time() + TEST_TX_INTERVAL), master_2g4_tx_ustimer_cb, NULL);
    #elif(TX_USE_TIMER == 2)
//    TMR_SetReload(APB_TMR2, 0, TIMER_RELOAD_TIME*100);   // 100ms 
//    TMR_Enable(APB_TMR2, 0, 1);
    ing2p4g_start_2p4g_rx_with_timeout(slave_tx_len, tx_data, 0, ing_2p4g_config.TimeOut);
    #else
    ing2p4g_start_2p4g_rx_with_timeout(slave_tx_len, tx_data, 0, ing_2p4g_config.TimeOut);
    #endif
}

void continus_2g4_txrx_off(void)
{
    continus_2g4 = 0;
    TMR_Enable(APB_TMR2, 0, 0);
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
//            ing2p4g_start_2p4g_rx(slave_tx_len, tx_data);
            ing2p4g_start_2p4g_rx_with_timeout(slave_tx_len, tx_data, 1, ing_2p4g_config.TimeOut);
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
//        gpio_pluse_num(3);
        tick_end = platform_get_us_time();
        double rate = 1000*ack_cnt/(float)(tick_end - tick_start);
//        platform_printf("tick_interval:%d us\n", (tick_end - tick_start));
        platform_printf("Test %d packet! miss: %d,rev: %d, rate: %.3fK pack/s, rssi:%d\r\n", T_CNT, miss_cnt, ack_cnt, rate, rssi);
//        platform_printf("rate: %.3fK pack/s\r\n",rate);
        ack_cnt = 0;
        miss_cnt = 0;
        test_cnt = 0;
        tick_start = platform_get_us_time();
    }
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

void app_2g4_channel_init(void) {
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
	master_tx_len = MASTER_HOP_DATA_LEN;
	tx_data[0]= APP_2G4_DATA_FRE_HOP;
}

void app_2g4_channel_hop_stop(void) {
    platform_printf("[2G4]hop fail and stop\n");
    app_2g4_hop.hop_cnt = 0;
	app_2g4_state.state = APP_2G4_STATE_CONNECT;
	app_2g4_channel_init();
	master_tx_len = MASTER_HOP_DATA_LEN;
	tx_data[0]= APP_2G4_DATA_FRE_HOP;
}

static void tx_ack_data_handle(ING2P4G_RxPacket *rx_packet) {
    switch(app_2g4_state.state){
		case APP_2G4_STATE_IDLE: {
			platform_printf("[2G4]Error line:%d\n", __LINE__);
			break;
		}
        case APP_2G4_STATE_CONNECT:{
            app_2g4_state.state = APP_2G4_STATE_COMMNUICATING;
            tx_data[0] = APP_2G4_DATA_COMMUNICATE;
            master_tx_len = MASTER_COM_DATA_LEN;
            break;
        }
		case APP_2G4_STATE_COMMNUICATING:{
            app_2g4_hop.error_cnt = 0;
			tx_data[0] = APP_2G4_DATA_COMMUNICATE;
            master_tx_len = MASTER_COM_DATA_LEN;
			break;
		}
		case APP_2G4_STATE_FRE_HOPPING:{
			app_2g4_hop.error_cnt = 0;
            app_2g4_hop.hop_cnt = 0;
            app_2g4_state.state = APP_2G4_STATE_COMMNUICATING;
            tx_data[0] = APP_2G4_DATA_COMMUNICATE;
            master_tx_len = MASTER_COM_DATA_LEN;
            platform_printf("[2G4]hop success ch:%d\n", app_2g4_hop.current_channel);
			break;
		}
        default:{
            platform_printf("[2G4]Error mode\n");
            break;
        }
    }
}

static void tx_noack_data_handle(ING2P4G_RxPacket *rx_packet) {
    switch(app_2g4_state.state){
		case APP_2G4_STATE_IDLE: {
			platform_printf("[2G4]Error line:%d\n", __LINE__);
			break;
		}
        case APP_2G4_STATE_CONNECT:{
            tx_data[0] = APP_2G4_DATA_CONNECT;
            master_tx_len = MASTER_COM_DATA_LEN;
            break;
        }
		case APP_2G4_STATE_COMMNUICATING:{
			app_2g4_hop.error_cnt++;
            if(app_2g4_hop.error_cnt > APP_2G4_HOP_BEGIN_NUM)
            {
                app_2g4_hop.error_cnt = 0;
                app_2g4_channel_hop_begin();
            }
			break;
		}
		case APP_2G4_STATE_FRE_HOPPING:{
            tx_data[0] = APP_2G4_DATA_FRE_HOP;
            master_tx_len = MASTER_HOP_DATA_LEN;
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

uint64_t print_time_last = 0;

ADDITIONAL_ATTRIBUTE static void EventIrqCallBack(void)
{
    static ing2p4g_work_mode_t mode;
    ing2p4g_clear_event_int();
    ing2p4g_get_2g4_work_mode(&mode);
    ing2p4g_status_t status = ing2p4g_get_rx_data(&RxPkt111);

    if(status == 0) {
        platform_printf("SLAVE Rx %d data:", RxPkt111.DataLen);
        for(uint16_t i=0; i<RxPkt111.DataLen; i++)
        {
            platform_printf("%d ", RxPkt111.Data[i]);
        }
        platform_printf("\n");
//        app_2g4_channel_hop();
        gpio_pluse_num2(1);
//		tx_ack_data_handle(&RxPkt111);
//        if((platform_get_us_time() - print_time_last) > TEST_RSSI_PRINT_INTERVAL)
//        {
//            platform_printf("TX RSSI:%d, ch:%d\n", RxPkt111.RSSI, app_2g4_hop.current_channel);
////            print_time_last = platform_get_us_time();
//        }
	}
    else if(status == 2){
        gpio_pluse_num3(1);
    }
    else if(status == 3){
        gpio_pluse_num4(1);
    }
    else {
        gpio_pluse_num4(2);
    }


    if(continus_2g4 == 1)
    {
        #if (TX_USE_TIMER == 1)
        #elif(TX_USE_TIMER == 2)
       TMR_Enable(APB_TMR2, 0, 0);
       TMR_SetReload(APB_TMR2, 0, TIMER_RELOAD_TIME);   // 1ms 
       TMR_Enable(APB_TMR2, 0, 1);
        ing2p4g_start_2p4g_rx_with_timeout(slave_tx_len, tx_data, 0, ing_2p4g_config.TimeOut);
        // gpio_pluse_num2(3);
        #else
        ing2p4g_start_2p4g_rx_with_timeout(slave_tx_len, tx_data, 1, ing_2p4g_config.TimeOut);
        #endif
//        percent_cnt(1000, status, RxPkt111.RSSI);
    }
}

static void RxPktIrqCallBack(void)
{
    ing2p4g_status_t status = ing2p4g_get_rx_data(&RxPkt111);
    ing2p4g_clear_rx_int();
    if(RxPkt111.Data[0]%2)
    {
        SetCont_rx_int(tx_data1, 16);
    }
    
}

ADDITIONAL_ATTRIBUTE static void TxPktIrqCallBack(void)
{
    //ing2p4g_err_bit_pos_t status = ing2p4g_get_rx_data(&RxPkt111);
    ing2p4g_clear_tx_int();
}

void ing24g_test_init(void){
    ing2p4g_set_irq_callback(ING2P4G_CB_EVENT, EventIrqCallBack);
    ing2p4g_set_irq_callback(ING2P4G_CB_RX, RxPktIrqCallBack);
    ing2p4g_set_irq_callback(ING2P4G_CB_TX, TxPktIrqCallBack);
    ing_2p4g_config_init();
}

