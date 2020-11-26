#include "GrowTimer_device.h"

//struct LoRa_device {
//	enum Type_device_t type;
//	uint8_t id;
//	uint16_t data;
//	bool set_data;
//};

struct LoRa_device_type_data lora_device_type_data[] = {
		{.command_data = {0, 2}}, // Signal_PWM
		{.command_data = {0, 1}}, // Signal_digital
		{.command_data = {0, 2}}, // Fan_PWM
		{.command_data = {0, 1}}, // Pumping_system
		{.command_data = {0, 1}}, // Phytolamp_digital
		{.command_data = {0, 2}}  // Phytolamp_PWM
	};

void lora_device_init(struct LoRa_device* device, enum Type_device_t type, uint8_t id) {
	device->type = type;
	device->id = 0;
	device->data = 0;
	device->set_data = false;
}

void lora_device_set_data(struct LoRa_device* device, uint16_t data) {
	device->data = data;
	device->set_data = true;
}

uint16_t lora_device_get_data(struct LoRa_device* device) {
	device->set_data = false;
	return device->data;
}
