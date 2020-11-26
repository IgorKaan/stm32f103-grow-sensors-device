#ifndef __LORA_LED_CONTROL_H__
#define __LORA_LED_CONTROL_H__

#include <stm32f1xx_hal.h>
#include <stdbool.h>

struct LoRa_led_data {
    uint16_t pin;
    GPIO_TypeDef* port;
    uint8_t amt_signal;
    uint32_t time;
    uint8_t stage;
};

struct {
	struct LoRa_led_data ledIN;
	struct LoRa_led_data ledOUT;
	struct LoRa_led_data ledREG;

	uint8_t reg_count;

    uint32_t wait_time;
    uint32_t signal_time;
} LoRa_led_struct;

bool lora_led_struct_init(GPIO_TypeDef* ledIN_port, uint16_t ledIN_pin, GPIO_TypeDef* ledOUT_port, uint16_t ledOUT_pin,
		GPIO_TypeDef* ledREG_port, uint16_t ledREG_pin, uint32_t wait_time, uint32_t signal_time);
void lora_led_struct_set_IN(uint8_t signalIN);
void lora_led_struct_set_OUT(uint8_t signalOUT);
void lora_led_struct_set_REG(bool signalREG);
void lora_led_struct_time_work();

#endif // __LORA_LED_CONTROL_H__
