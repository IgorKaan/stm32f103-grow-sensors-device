#ifndef __GROWTIMER_LORA_MODULE_H__
#define __GROWTIMER_LORA_MODULE_H__
#include <stm32f1xx_hal.h>
#include <LoRa_module/LoRa_main_file.h>
#include <LoRa_module/LoRa_led_control.h>

#include <stdbool.h>
#include <GrowTimer/GrowTimer_sensor.h>
#include <GrowTimer/GrowTimer_device.h>

struct LoRa_module {
	uint8_t my_adr[3];
	uint8_t esp_adr[3];
	bool state_regist;
	uint16_t num_packet;

	bool led;

	uint8_t setting;
	uint8_t setting_sensors;
	uint8_t setting_devices;

	struct LoRa_sensor* sensors;
	uint8_t amt_sensors;
	struct LoRa_device* devices;
	uint8_t amt_devices;

	struct lora_packet packet;
};

struct LoRa_module lora_module_init(struct LoRa_sensor* sensors, uint8_t amt_sensors,
		struct LoRa_device* devices, uint8_t amt_devices, GPIO_TypeDef* ledIN_port,
		uint16_t ledIN_pin, GPIO_TypeDef* ledOUT_port, uint16_t ledOUT_pin,
		GPIO_TypeDef* ledREG_port, uint16_t ledREG_pin);

void lora_module_introduce(struct LoRa_module* module);

//void lora_module_send_data_sensors(struct LoRa_module* module);
//void lora_module_send_data_devices(struct LoRa_module* module);
//void lora_module_reciv_data_devices(struct LoRa_module* module);

bool lora_module_work(struct LoRa_module* module);

#endif // __GROWTIMER_LORA_MODULE_H__
