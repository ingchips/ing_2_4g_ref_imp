#ifndef _PROFILESTASK_H_
#define _PROFILESTASK_H_

#include <stdint.h>
#include "../2P4G/BLE_2p4g_Switch.h"

uint32_t setup_profile(void *data, void *user_data);

void ble_switch_to_2p4g_trigger(void);
#endif


