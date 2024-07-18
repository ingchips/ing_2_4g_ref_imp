#ifndef __TEST_2P4G_H
#define __TEST_2P4G_H

#include "stdint.h"
#include "ing_2p4g.h"

#define APP_2G4_HOP_CHANNEL_NUM     5
#define APP_2G4_HOP_BEGIN_NUM       1
#define APP_2G4_HOP_STOP_NUM        8

#define APP_2G4_DATA_CONNECT 			    0xA0
#define APP_2G4_DATA_COMMUNICATE			0xA2
#define APP_2G4_DATA_FRE_HOP 			    0xA5

#define SWITCH_KEY_GPIO     GIO_GPIO_10
#define PULSE_TEST_GPIO     GIO_GPIO_20

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

#endif
