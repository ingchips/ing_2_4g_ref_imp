#ifndef _PROFILESTASK_H_
#define _PROFILESTASK_H_

#include <stdint.h>

#define PULSE_TEST_GPIO1     GIO_GPIO_19
#define PULSE_TEST_GPIO2     GIO_GPIO_20
#define PULSE_TEST_GPIO3     GIO_GPIO_21
#define PULSE_TEST_GPIO4     GIO_GPIO_22

void gpio_pluse_num1(uint16_t num);
void gpio_pluse_num2(uint16_t num);
void gpio_pluse_num3(uint16_t num);
void gpio_pluse_num4(uint16_t num);
uint32_t setup_profile(void *data, void *user_data);

void ble_switch_to_2p4g_trigger(void);
void ing2p4g_switch_to_ble_mode_start(void);
#endif


