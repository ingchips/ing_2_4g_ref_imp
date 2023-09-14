#include "stdio.h"
#include "TEST_2P4G.h"
#include "platform_api.h"
#include "btstack_event.h"
#include "profile.h"
// ================================================================================

void ing2p4g_clear_rx_int(void){
    clear_rx_int();
}

void ing2p4g_clear_event_int(void){
    clear_event_int();
}

uint8_t ing2p4g_get_rx_data(ING2P4G_RxPacket *rx_packet){
    return GetRxData(rx_packet);
}

uint8_t ing2p4g_start_2p4g_rx(uint8_t len, uint8_t *data){
    return start_2p4g_RX(len, data);
}

uint8_t ing2p4g_start_2p4g_tx(uint8_t len, uint8_t *data){
    return start_2p4g_TX(len, data);
}

uint8_t ing2p4g_set_channel(uint16_t channel){
    return ing_2p4g_set_channel(channel);
}

uint8_t ing2p4g_set_tx_power(uint8_t tx_power){
    return ing_2p4g_set_tx_power(tx_power);
}

uint8_t ing2p4g_set_access_address(uint32_t access_addr){
    return ing_2p4g_set_access_address(access_addr);
}

uint8_t ing2p4g_set_phy(uint8_t phy){
    return ing_2p4g_set_phy(phy);
}

uint8_t ing2p4g_get_state(void){
    return ing_2p4g_get_state();
}

void ing2p4g_init_dual_mode(void){
    init_dual_mode();
}

void ing2p4g_switch_to_2G4(ING2P4G_Config_t *config){
    switch_to_2G4(config);
}

uint8_t ing2p4g_switch_to_BLE(void){
    return switch_to_BLE();
}


// ================================================================================
static uint16_t miss_cnt = 0;
static uint16_t miss_time = 0;
static uint16_t ack_cnt = 0;

static uint16_t gpio_cnt = 0;

static comm_mode_t comm_mode = MODE_BLE;

static uint8_t len = 30;
static uint8_t tx_data[]={0,5,4,2,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31}; 
static uint8_t rx_data[256];
ING2P4G_RxPacket   RxPkt111;
static ING2P4G_Config_t ing_2p4g_config;

// ================================================================================

void ing_2p4g_config_init(void)
{
    #if DEF_MASTER
    ing_2p4g_config.Mode          = MODE_MASTER;
    #else
    ing_2p4g_config.Mode          = MODE_SLAVE;
    #endif
    ing_2p4g_config.AccAddr       = 0x12345678;
    ing_2p4g_config.PHY           = LLE_PHY_2M;
    ing_2p4g_config.Channel       = 2400;
    ing_2p4g_config.TXPOW         = 63;
    ing_2p4g_config.WhiteEn       = 0x1;
    ing_2p4g_config.WhiteIdx      = 0x0;
    ing_2p4g_config.CRCInit       = 0x123456;
    ing_2p4g_config.TimeOut       = 1600;//10000;//6.25s
    ing_2p4g_config.RxPktIntEn    = 1;
    ing_2p4g_config.RxPktIntThres = 1;
}

void ing24g_test_do_switch_to_2p4g(void){
    platform_printf("DO SWITCH 2.4G\n");
    ing2p4g_switch_to_2G4(&ing_2p4g_config);
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
            ing2p4g_switch_to_BLE();
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
    // platform_printf("key\n");
    // extern void ble_test_handler(void);
    // ble_test_handler();
    // return ;

    static uint8_t gpio_isr_cnt = 0;    
    if(gpio_isr_cnt == 0)
    {
        ing24g_test_switch_mode_trigger(MODE_2G4);
        platform_printf("to 2.4g\r\n");
    }
    else
    {
#if DEF_MASTER
        ing2p4g_start_2p4g_tx(len, tx_data);
#else
        ing2p4g_start_2p4g_rx(len, tx_data);
#endif
    }
    gpio_isr_cnt++;
}

#if DEF_MASTER
static void pacent_cnt(uint16_t count, uint8_t rev_flg)
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
#else
static void print_data(uint8_t len, uint8_t *data)
{
    uint8_t i = 0;
    platform_printf("%d data:", len);
    for(i=0; i<len; i++)
    {
        platform_printf("%d ", data[i]);
    }
    platform_printf("\r\n");
}
#endif


static void EventIrqCallBack(void)
{
    uint8_t i;
    uint8_t flag;
    clear_event_int();
    flag = ing2p4g_get_rx_data(&RxPkt111);

    tx_data[0]++;

#if DEF_MASTER
        pacent_cnt(1000, flag);
        ing2p4g_start_2p4g_tx(len, tx_data);
#else
        ing2p4g_start_2p4g_rx(len, tx_data);
        print_data(RxPkt111.DataLen, RxPkt111.Data);
#endif

}

static void RxPktIrqCallBack(void)
{
    //uint8_t flag = ing2p4g_get_rx_data(rx_data, &len);
    clear_rx_int();
}

void ing24g_test_init(void){
    ing2p4g_set_irq_callback(ING2P4G_CB_EVENT, EventIrqCallBack);
    ing2p4g_set_irq_callback(ING2P4G_CB_RX, RxPktIrqCallBack);
    ing_2p4g_config_init();
}

