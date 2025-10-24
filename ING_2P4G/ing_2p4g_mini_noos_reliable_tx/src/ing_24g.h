#ifndef _ING_24G_H_
#define _ING_24G_H_

#include "stdint.h"
#include "ing_2p4g.h"

#define USE_TIMER_INTERVAL 0 //  0: use loop for interval, 1: Use timer interval for heartbeat. It can only be used after SDK 8.5.4. Otherwise, there will be bugs.

#define PACKET_HEADER_MD_BIT_POS   0x00
#define PACKET_HEADER_SN_BIT_POS   0x01
#define PACKET_HEADER_NESN_BIT_POS 0x02

#define ING24G_SLAVE_TIMEOUT_US    50000
#define ING24G_MASTER_INTERVAL_US  10000

#define ING24G_HOP_CHANNEL_NUM     6
#define ING24G_HOP_BEGIN_CNT_MIN   (ING24G_SLAVE_TIMEOUT_US / ING24G_MASTER_INTERVAL_US)
#define ING24G_HOP_BEGIN_CNT_MAX   (ING24G_SLAVE_TIMEOUT_US / 625)
#define ING24G_HOP_STOP_CNT        4200 

#define PACKET_DATA_SIZE  40
#define PACKET_FIFO_SIZE  40

typedef void (*ing24g_event_cb)(uint8_t event, uint8_t *data, uint8_t len);

typedef enum
{
    ING24G_EVENT_CONNECTING = 0,
    ING24G_EVENT_CONNECTED,
    ING24G_EVENT_DISCONNECT,
    ING24G_EVENT_TX_DONE,
    ING24G_EVENT_RECEIVE,
} ing24g_event_e;

typedef struct 
{
    uint8_t len;
    uint8_t data[PACKET_DATA_SIZE - 1];
} ing24g_packet_ele_t;

typedef struct
{
    ing24g_packet_ele_t packet[PACKET_FIFO_SIZE];
    uint8_t head;
    uint8_t tail;
    uint8_t is_send;
    ing24g_packet_ele_t *isr_send_packet;
} ing24g_packet_fifo_t;

typedef struct
{
    uint16_t     channel_hop[ING24G_HOP_CHANNEL_NUM];
    uint16_t     current_channel;
    uint16_t     hop_cnt;
    uint8_t      error_cnt;
} ing_24g_ch_hot_t;

typedef enum
{
    ING24G_STATE_IDLE,
    ING24G_STATE_CONNECT,
    ING24G_STATE_COMMNUICATING,
    ING24G_STATE_FRE_HOPPING,
    ING24G_STATE_MAX
} ing24g_state_e;

typedef struct __attribute__((packed)) {
    ing24g_state_e state;
    uint64_t interval;
    uint64_t active_send_time; // 上次主动发送数据的时间
    uint16_t hop_begin_cnt; // 24G 连接上，待机通信失败 hop_begin_cnt 次开始跳频
    ing24g_event_cb event_callback;
} ing24g_observed_t;


uint8_t ing24g_send_data(uint8_t *data, uint8_t len);
void ing24g_do_switch_to_2p4g(void);
#if(USE_TIMER_INTERVAL == 0)
void ing24g_process(void);
#endif
void ing24g_init(ing24g_event_cb event_cb);

#endif
