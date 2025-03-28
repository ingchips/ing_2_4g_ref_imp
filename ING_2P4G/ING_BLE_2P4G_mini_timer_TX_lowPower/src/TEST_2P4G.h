#ifndef __TEST_2P4G_H
#define __TEST_2P4G_H

#include "stdint.h"
#include "ing_2p4g.h"

#define APP_2G4_HOP_CHANNEL_NUM     5
#define APP_2G4_HOP_BEGIN_NUM       10
#define APP_2G4_HOP_STOP_NUM        100

#define APP_2G4_DATA_CONNECT 			    0xA0
#define APP_2G4_DATA_COMMUNICATE			0xA2
#define APP_2G4_DATA_FRE_HOP 			    0xA5

#define MASTER_HOP_DATA_LEN       1
#define MASTER_COM_DATA_LEN       2

#define TEST_TX_INTERVAL          400
#define TEST_RSSI_PRINT_INTERVAL  60000


typedef struct
{
    uint16_t     channel_hop[APP_2G4_HOP_CHANNEL_NUM];
    uint16_t     current_channel;
    uint16_t     hop_cnt;
    uint8_t      error_cnt;
} app_2g4_ch_hop_t;

typedef struct __attribute__((packed)) {
    uint8_t state;
} app_2g4_state_t;

typedef enum
{
    APP_2G4_STATE_IDLE,			    //
    APP_2G4_STATE_CONNECT,          //
    APP_2G4_STATE_COMMNUICATING,    //
    APP_2G4_STATE_FRE_HOPPING,      //
    APP_2G4_STATE_MAX               //
} app_2g4_state_e;

void ing24g_test_do_switch_to_2p4g(void);
void ing24g_test_switch_mode_handler(void);
void ing24g_test_init(void);

void ing24g_test_switch_mode_trigger(comm_mode_t mode);
void continus_2g4_txrx_on(void);
void continus_2g4_txrx_off(void);

void test_2p4g_timer_init(void);

uint8_t app_2g4_rf_state(void);

#endif
