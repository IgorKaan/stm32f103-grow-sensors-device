#ifndef __GROWTIMER_DEVICE_H__
#define __GROWTIMER_DEVICE_H__
#include <stm32f1xx_hal.h>

#include <stdbool.h>

enum Type_device_t {
	Signal_PWM = 0,
	Signal_digital,
	Fan_PWM,
	Pumping_system,
	Phytolamp_digital,
	Phytolamp_PWM
};

struct LoRa_device_type_data {
	uint8_t command_data[2];
};

// Где 1 - ON/OFF, 2 - ШИМ(0-4095)
extern struct LoRa_device_type_data lora_device_type_data[];

struct LoRa_device {
	enum Type_device_t type;
	uint8_t id;
	uint16_t data;
	bool set_data;
};

void lora_device_init(struct LoRa_device* device, enum Type_device_t type, uint8_t id);
void lora_device_set_data(struct LoRa_device* device, uint16_t data);
uint16_t lora_device_get_data(struct LoRa_device* device);

#endif // __GROWTIMER_DEVICE_H__
