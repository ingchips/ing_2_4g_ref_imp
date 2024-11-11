#ifndef _PROFILESTASK_H_
#define _PROFILESTASK_H_

#include <stdint.h>

#define PULSE_TEST_GPIO1     GIO_GPIO_35
#define PULSE_TEST_GPIO2     GIO_GPIO_36
#define PULSE_TEST_GPIO3     GIO_GPIO_27
#define PULSE_TEST_GPIO4     GIO_GPIO_32
#define PULSE_TEST_GPIO5     GIO_GPIO_35
#define PULSE_TEST_GPIO6     GIO_GPIO_36

void gpio_pluse_num1(uint16_t num);
void gpio_pluse_num2(uint16_t num);
void gpio_pluse_num3(uint16_t num);
void gpio_pluse_num4(uint16_t num);
void gpio_pluse_num5(uint16_t num);
void gpio_pluse_num6(uint16_t num);

uint32_t setup_profile(void *data, void *user_data);

void ble_switch_to_2p4g_trigger(void);
void ing2p4g_switch_to_ble_mode_start(void);
#endif


