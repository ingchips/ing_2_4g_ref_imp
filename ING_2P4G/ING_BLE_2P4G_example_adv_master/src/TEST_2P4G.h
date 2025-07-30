#ifndef __TEST_2P4G_H
#define __TEST_2P4G_H

#include "stdint.h"
#include "ing_2p4g.h"

void ing24g_test_do_switch_to_2p4g(void);
void ing24g_test_switch_mode_handler(void);
void ing24g_test_init(void);

void ing24g_test_switch_mode_trigger(comm_mode_t mode);
void continus_2g4_txrx_on(void);
void continus_2g4_txrx_off(void);

#endif
