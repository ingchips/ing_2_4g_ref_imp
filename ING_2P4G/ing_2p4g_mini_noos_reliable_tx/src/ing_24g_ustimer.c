#include <stdio.h>
#include <string.h>
#include "ing_2p4g.h"
#include "ing_24g.h"
#include "platform_api.h"
#include "btstack_event.h"
#include "profile.h"

#if (ING24G_PRINTF == 1)
    #define ing24g_printf(...)
#else
    #define ing24g_printf(...) platform_printf(__VA_ARGS__)
#endif

static ING2P4G_RxPacket RxPkt111;
static ING2P4G_Config_t ing_2p4g_config;

/*
 *  header
 *  bit7:bit3 reserve, bit2 : NESN, bit1: SN, bit0: MD
 */
static volatile uint8_t header_sn = 0;

static uint8_t tx_data[PACKET_DATA_SIZE]; 
static uint8_t tx_len = 0;

static ing_24g_ch_hot_t ing24g_hop = {
	.channel_hop = {2405, 2417, 2430, 2445, 2460, 2469},
	.current_channel = 0,// 0-ING24G_HOP_CHANNEL_NUM
	.hop_cnt = 0,
    .error_cnt = 0,
};

static ing24g_observed_t ing24g_obs ={
	.state = ING24G_STATE_IDLE,
    .interval = 10000,
    .active_send_time = 0,
    .event_callback = NULL,
    .hop_begin_cnt = ING24G_HOP_BEGIN_CNT_MIN, // 24G 连接上，待机通信失败 ING24G_HOP_BEGIN_CNT_MIN 次开始跳频
};

static void ing24g_event_put(uint8_t event, uint8_t *data, uint8_t len)
{
	if(ing24g_obs.event_callback)
	{
		ing24g_obs.event_callback(event, data, len);
	}
}

// ================================================================================ FIFO_FUNCS
static ing24g_packet_fifo_t packet_fifo;
// Initialize the packet FIFO
static void ing24g_packet_fifo_init(void)
{
    packet_fifo.head = 0;
    packet_fifo.tail = 0;
}

// Add a packet to the FIFO
static int ing24g_packet_fifo_add(uint8_t *data, uint8_t len)
{
    // if(data == NULL || len == 0)
    // {
    //     ing24g_printf("[ing24g_packet_fifo_add] : Data is NULL or length is 0!\n");
    //     return 1;
    // }
    if(len > PACKET_DATA_SIZE - 1)
    {
        ing24g_printf("[ing24g_packet_fifo_add] : Data length exceeds maximum size!\n");
        return 1;
    }
    if ((packet_fifo.tail + 1) % PACKET_FIFO_SIZE == packet_fifo.head)
    {
        ing24g_printf("[ing24g_packet_fifo_push] : FIFO Overflow\n");
        return 1;
    }
    packet_fifo.packet[packet_fifo.tail].len = len;
    memcpy(packet_fifo.packet[packet_fifo.tail].data, data, len);
    packet_fifo.tail = (packet_fifo.tail + 1) % PACKET_FIFO_SIZE;
    return 0;
}

static ing24g_packet_ele_t* ing24g_packet_fifo_get(void)
{
    if (packet_fifo.head == packet_fifo.tail)
    {
        return NULL;
    }
    return &packet_fifo.packet[packet_fifo.head];
}

static void ing24g_packet_fifo_del(void)
{
    if (packet_fifo.head == packet_fifo.tail)
    {
        ing24g_printf("[ing24g_packet_fifo_del] : FIFO is empty!\n");
        return;
    }
    packet_fifo.head = (packet_fifo.head + 1) % PACKET_FIFO_SIZE;
}

// ================================================================================

// ================================================================================ SEND_FUNCS

/*
 *  Send an packet to trigger the 2.4G communication
 *  if data is NULL or len is 0, send an empty packet
 */
static uint8_t ing24g_raw_send_data(uint8_t *data, uint8_t len)
{
    tx_data[0] = header_sn << PACKET_HEADER_SN_BIT_POS;
    tx_len = 1; // Set length to 1 for an empty packet
    if(data != NULL && len > 0)
    {
        memcpy(&tx_data[1], data, len);
        tx_len += len;
    }
    return ing2p4g_start_2p4g_tx(tx_len, tx_data);
}

static uint8_t ing24g_check_fifo_send_data(void)
{
    int ret = 0;
    ing24g_packet_ele_t *packet = ing24g_packet_fifo_get();
    if (packet != NULL)
    {
        ret = ing24g_raw_send_data(packet->data, packet->len);
        if(ret == ING2P4G_SUCCESS)
        {
            packet_fifo.isr_send_packet = packet; // Set the packet to be sent in ISR
            packet_fifo.is_send = 1;
            ing24g_obs.hop_begin_cnt = ING24G_HOP_BEGIN_CNT_MAX; // 有数据主动发送时，通信失败 ING24G_HOP_BEGIN_CNT_MAX 次开始跳频
            ing24g_obs.active_send_time = platform_get_us_time(); // Update the last successful send time
            return 0;
        }
    }
    return 1; // Return 1 if no packet to send or send failed
}

uint8_t ing24g_send_data(uint8_t *data, uint8_t len)
{
    int ret = 0;
    if(!(ing24g_obs.state >= ING24G_STATE_COMMNUICATING && ing24g_obs.state <= ING24G_STATE_FRE_HOPPING))
    {
        ing24g_printf("[ing24g_send_data] : Not in communicating state!\n");
        return 1;
    }

    ret = ing24g_packet_fifo_add(data, len);
    if (ret != 0)
    {
        return ret;
    }

    ing24g_packet_ele_t *packet = ing24g_packet_fifo_get();
    // fifo 里面的数据在 2.4g 中断里面没有发送，才允许在这里发送，否者会造成原子性问题。
    // 如果没有此判断，在 ing24g_send_data 到 ing2p4g_start_2p4g_tx 中间如果被 2.4g 中断打断（重传包文发送完毕），恢复现场，
    // 会导致发送同一包文两次，从而删除了下一个的包文，下次再进来发送数据相当于跳了一包。
    if (packet_fifo.isr_send_packet != packet)
    {
        ret = ing24g_raw_send_data(packet->data, packet->len);
        if(ret == ING2P4G_SUCCESS)
        {
            packet_fifo.is_send = 1;
            packet_fifo.isr_send_packet = NULL; // Clear the ISR send packet
            ing24g_obs.hop_begin_cnt = ING24G_HOP_BEGIN_CNT_MAX; // 有数据主动发送时，通信失败 ING24G_HOP_BEGIN_CNT_MAX 次开始跳频
            ing24g_obs.active_send_time = platform_get_us_time(); // Update the last successful send time
        }
    }
    return 0;
}

// ================================================================================

// ================================================================================ CHANNEL_HOP_FUNCS
void ing24g_channel_hop(void) {
	ing24g_hop.hop_cnt++;
	ing24g_hop.current_channel++;
	if(ing24g_hop.current_channel >= ING24G_HOP_CHANNEL_NUM) {
		ing24g_hop.current_channel = 0;
	}
	ing_2p4g_config.Channel = ing24g_hop.channel_hop[ing24g_hop.current_channel];
	ing2p4g_status_t state =  ing2p4g_set_channel(ing24g_hop.channel_hop[ing24g_hop.current_channel]);
	if(ING2P4G_SUCCESS != state){
        ing24g_printf("[2G4]Hop tx fail\n");
    }
}

void ing24g_channel_init(void) {
	ing24g_hop.hop_cnt = 0;
	ing24g_hop.current_channel = 0;
	ing_2p4g_config.Channel = ing24g_hop.channel_hop[ing24g_hop.current_channel];
	ing2p4g_status_t state =  ing2p4g_set_channel(ing24g_hop.channel_hop[ing24g_hop.current_channel]);
	if(ING2P4G_SUCCESS != state){
        ing24g_printf("[2G4]Hop tx fail\n");
    }
}

void ing24g_channel_hop_begin(void) {
    ing24g_printf("[2G4]hop begin\n");
    ing24g_hop.hop_cnt = 0;
	ing24g_obs.state = ING24G_STATE_FRE_HOPPING;
	ing24g_channel_hop();
    ing24g_raw_send_data(NULL, 0);
}

void ing24g_channel_hop_stop(void) {
    ing24g_printf("[2G4]hop fail and stop\n");
    ing24g_hop.hop_cnt = 0;
	ing24g_obs.state = ING24G_STATE_CONNECT;
	ing24g_channel_init();
	ing24g_raw_send_data(NULL, 0);
}
// ================================================================================

// ================================================================================

static void ing24g_param_init(void)
{
    ing24g_obs.state = ING24G_STATE_IDLE;
    ing24g_hop.current_channel = 0;
    ing24g_hop.hop_cnt = 0;
    ing24g_hop.error_cnt = 0;
}

static void ing_2p4g_config_init(void)
{
    ing_2p4g_config.Mode          = MODE_MASTER;
    ing_2p4g_config.AccAddr       = 0x3234567A;
    ing_2p4g_config.PHY           = LLE_PHY_1M;
    ing_2p4g_config.Channel       = 2391;
    ing_2p4g_config.TXPOW         = 63;
    ing_2p4g_config.WhiteEn       = 0x1;
    ing_2p4g_config.WhiteIdx      = 0x0;
    ing_2p4g_config.CRCInit       = 0x123456;
    ing_2p4g_config.TimeOut       = 60; // *6.25us
    ing_2p4g_config.RxPktIntEn    = 0;
    ing_2p4g_config.TxPktIntEn    = 0;
}

static void *ing24g_interval_timer_cb(platform_us_timer_handle_t timer_handle, uint64_t time_us, void *param)
{
    uint64_t timer_counter = platform_get_us_time();
    if(ing24g_obs.state == ING24G_STATE_COMMNUICATING)
    {
        if(ing24g_obs.active_send_time < timer_counter - ing24g_obs.interval) // 周期内没有数据收发成功，则发送心跳包
        {
            platform_create_us_timer(timer_counter + ing24g_obs.interval, ing24g_interval_timer_cb, NULL);
            ing24g_raw_send_data(NULL, 0);
            ing24g_obs.hop_begin_cnt = ING24G_HOP_BEGIN_CNT_MIN;
        }
        else // 周期内有数据收发成功，拿上次成功的时间重新开启周期
        {
            platform_create_us_timer(ing24g_obs.active_send_time + ing24g_obs.interval, ing24g_interval_timer_cb, NULL);
        }
    }
    else
    {
        platform_create_us_timer(timer_counter + ing24g_obs.interval, ing24g_interval_timer_cb, NULL);
    }
    return 0;
}

void ing24g_do_switch_to_2p4g(void)
{
    if(ing_2p4g_config.Mode == MODE_MASTER){
        ing24g_printf("DO SWITCH 2.4G: MASTER.\n");
    } else {
        ing24g_printf("DO SWITCH 2.4G: SLAVE.\n");
    }
    platform_config(PLATFORM_CFG_LL_DBG_FLAGS, 32);
    ing2p4g_switch_to_2G4(&ing_2p4g_config);
    ing24g_param_init();
    ing24g_channel_init();
    ing24g_obs.state = ING24G_STATE_CONNECT;
    ing24g_raw_send_data(NULL, 0);
    platform_create_us_timer(platform_get_us_time() + ing24g_obs.interval, ing24g_interval_timer_cb, NULL);
}

void ing24g_connect(void)
{

    ing24g_raw_send_data(NULL, 0);

}

void ing24g_disconnect(void)
{
    ing24g_printf("[2G4]Disconnect\n");
    ing24g_param_init();
    ing24g_channel_init();
    ing24g_packet_fifo_init();
}

static void tx_ack_data_handle(ING2P4G_RxPacket *rx_packet)
{
    static uint8_t continue_transfer;
    header_sn = !header_sn;
    switch(ing24g_obs.state) {
		case ING24G_STATE_IDLE: {
			ing24g_printf("[2G4]Error line:%d\n", __LINE__);
			break;
		}
        case ING24G_STATE_CONNECT: {
            ing24g_obs.state = ING24G_STATE_COMMNUICATING;
			ing24g_event_put(ING24G_EVENT_CONNECTED, NULL, 0);
            break;
        }
		case ING24G_STATE_COMMNUICATING: {
            ing24g_hop.error_cnt = 0;
            if(packet_fifo.is_send == 1) // 收到ACK，之前发送的包文成功到达对方，可以删除
            {
                packet_fifo.is_send = 0;
                ing24g_packet_fifo_del();
            }

            if(rx_packet->DataLen > 1)
            {
                ing24g_event_put(ING24G_EVENT_RECEIVE, rx_packet->Data, rx_packet->DataLen);
                continue_transfer = 1;
            }
            if(ing24g_check_fifo_send_data() != 0 && continue_transfer)
            {
                if(ing24g_raw_send_data(NULL, 0) == 0)
                {
                    ing24g_obs.hop_begin_cnt = ING24G_HOP_BEGIN_CNT_MAX; // 通信失败 ING24G_HOP_BEGIN_CNT_MIN 次开始跳频
                    ing24g_obs.active_send_time = platform_get_us_time(); // Update the last successful send time
                }
            }
			break;
		}
		case ING24G_STATE_FRE_HOPPING: {
			ing24g_hop.error_cnt = 0;
            ing24g_hop.hop_cnt = 0;
            ing24g_obs.state = ING24G_STATE_COMMNUICATING;
            ing24g_check_fifo_send_data();
            ing24g_printf("[2G4]hop success ch:%d\n", ing24g_hop.current_channel);
			break;
		}
        default: {
            ing24g_printf("[2G4]Error mode\n");
            break;
        }
    }
}

static void tx_noack_data_handle(ING2P4G_RxPacket *rx_packet)
{
    switch(ing24g_obs.state) {
		case ING24G_STATE_IDLE: {
			ing24g_printf("[2G4]Error line:%d\n", __LINE__);
			break;
		}
        case ING24G_STATE_CONNECT:{
            ing24g_raw_send_data(NULL, 0);
            break;
        }
		case ING24G_STATE_COMMNUICATING:{
			ing24g_hop.error_cnt++;
            if(ing24g_hop.error_cnt > ing24g_obs.hop_begin_cnt)
            {
                ing24g_hop.error_cnt = 0;
                ing24g_channel_hop_begin();
            }
			break;
		}
		case ING24G_STATE_FRE_HOPPING:{
            if(ing24g_hop.hop_cnt > ING24G_HOP_STOP_CNT)
            {
                ing24g_channel_hop_stop();
                ing24g_event_put(ING24G_EVENT_DISCONNECT, NULL, 0);
                header_sn = 0; // Reset header SN
            }
            else
            {
                ing24g_channel_hop();
                ing24g_raw_send_data(NULL, 0);
            }
			break;
		}
        default:{
            ing24g_printf("[2G4]Error mode\n");
            break;
        }
    }
}

ADDITIONAL_ATTRIBUTE static void EventIrqCallBack(void)
{
    ing2p4g_clear_event_int();
    ing2p4g_status_t status = ing2p4g_get_rx_data(&RxPkt111);

    if(!status)
    {
		tx_ack_data_handle(&RxPkt111);
	}
    else
    {
        tx_noack_data_handle(&RxPkt111);
    }

    // percent_cnt(1000, status, RxPkt111.RSSI);

}

static void RxPktIrqCallBack(void)
{
    //ing2p4g_err_bit_pos_t status = ing2p4g_get_rx_data(&RxPkt111);
    ing2p4g_clear_rx_int();
}

ADDITIONAL_ATTRIBUTE static void TxPktIrqCallBack(void)
{
    //ing2p4g_err_bit_pos_t status = ing2p4g_get_rx_data(&RxPkt111);
    ing2p4g_clear_tx_int();
}

void ing24g_init(ing24g_event_cb event_cb)
{
    ing2p4g_set_irq_callback(ING2P4G_CB_EVENT, EventIrqCallBack);
    ing2p4g_set_irq_callback(ING2P4G_CB_RX, RxPktIrqCallBack);
    ing2p4g_set_irq_callback(ING2P4G_CB_TX, TxPktIrqCallBack);
    ing_2p4g_config_init();

    if(event_cb != NULL) {
        ing24g_obs.event_callback = event_cb;
    }
}