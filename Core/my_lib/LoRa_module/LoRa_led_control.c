#include "LoRa_led_control.h"

bool lora_led_struct_init(GPIO_TypeDef* ledIN_port, uint16_t ledIN_pin, GPIO_TypeDef* ledOUT_port, uint16_t ledOUT_pin,
		GPIO_TypeDef* ledREG_port, uint16_t ledREG_pin, uint32_t wait_time, uint32_t signal_time) {
	bool first_init = false;
	if((ledIN_port == 0) && (ledIN_pin == 0) && (ledOUT_port == 0) && (ledOUT_pin == 0) && (ledREG_port == 0) && (ledREG_pin == 0)) {
		first_init = true;
	}

	if((ledIN_port != 0) || (first_init)) {
		LoRa_led_struct.ledIN.port = ledIN_port;
		LoRa_led_struct.ledIN.pin  = ledIN_pin;
		LoRa_led_struct.ledIN.amt_signal = 0;
	}
	if((ledOUT_port != 0) || (first_init)) {
		LoRa_led_struct.ledOUT.port = ledOUT_port;
		LoRa_led_struct.ledOUT.pin  = ledOUT_pin;
		LoRa_led_struct.ledOUT.amt_signal = 0;
	}
	if((ledREG_port != 0) || (first_init)) {
		LoRa_led_struct.ledREG.port = ledREG_port;
		LoRa_led_struct.ledREG.pin  = ledREG_pin;
		LoRa_led_struct.ledREG.amt_signal = 0;
		LoRa_led_struct.ledREG.time = HAL_GetTick();
		LoRa_led_struct.reg_count = 0;
	}

	if(wait_time != 0) {
		LoRa_led_struct.wait_time = wait_time;
	}
	if(signal_time != 0) {
		LoRa_led_struct.signal_time = signal_time;
	}
	return first_init;
}

void lora_led_struct_set_IN(uint8_t signalIN) {
	LoRa_led_struct.ledIN.time = HAL_GetTick() - LoRa_led_struct.wait_time;
	LoRa_led_struct.ledIN.amt_signal = signalIN;
}
void lora_led_struct_set_OUT(uint8_t signalOUT) {
	LoRa_led_struct.ledOUT.time = HAL_GetTick() - LoRa_led_struct.wait_time;
	LoRa_led_struct.ledOUT.amt_signal = signalOUT;
}
void lora_led_struct_set_REG(bool signalREG) {
	LoRa_led_struct.ledREG.amt_signal = signalREG;
}
void lora_led_struct_time_work() {
	if(LoRa_led_struct.ledIN.stage == 0) {
		if(HAL_GetTick() - LoRa_led_struct.ledIN.time > LoRa_led_struct.signal_time){
			LoRa_led_struct.ledIN.time += LoRa_led_struct.signal_time;
			HAL_GPIO_WritePin(LoRa_led_struct.ledIN.port, LoRa_led_struct.ledIN.pin, GPIO_PIN_RESET);
			LoRa_led_struct.ledIN.stage = 1;
		}
	}
	else {
		if(LoRa_led_struct.ledIN.amt_signal > 0) {
			if(HAL_GetTick() - LoRa_led_struct.ledIN.time > LoRa_led_struct.wait_time){
				LoRa_led_struct.ledIN.time += LoRa_led_struct.wait_time;
				HAL_GPIO_WritePin(LoRa_led_struct.ledIN.port, LoRa_led_struct.ledIN.pin, GPIO_PIN_SET);
				--LoRa_led_struct.ledIN.amt_signal;
				LoRa_led_struct.ledIN.stage = 0;
			}
		}
	}

	if(LoRa_led_struct.ledOUT.stage == 0) {
		if(HAL_GetTick() - LoRa_led_struct.ledOUT.time > LoRa_led_struct.signal_time){
			LoRa_led_struct.ledOUT.time += LoRa_led_struct.signal_time;
			HAL_GPIO_WritePin(LoRa_led_struct.ledOUT.port, LoRa_led_struct.ledOUT.pin, GPIO_PIN_RESET);
			LoRa_led_struct.ledOUT.stage = 1;
		}
	}
	else {
		if(LoRa_led_struct.ledOUT.amt_signal > 0) {
			if(HAL_GetTick() - LoRa_led_struct.ledOUT.time > LoRa_led_struct.wait_time){
				LoRa_led_struct.ledOUT.time += LoRa_led_struct.wait_time;
				HAL_GPIO_WritePin(LoRa_led_struct.ledOUT.port, LoRa_led_struct.ledOUT.pin, GPIO_PIN_SET);
				--LoRa_led_struct.ledOUT.amt_signal;
				LoRa_led_struct.ledOUT.stage = 0;
			}
		}
	}

	if(LoRa_led_struct.ledREG.stage == 0) {
		if(HAL_GetTick() - LoRa_led_struct.ledREG.time > LoRa_led_struct.signal_time){
			if(LoRa_led_struct.reg_count == 0) {
				LoRa_led_struct.reg_count = 30;
				LoRa_led_struct.ledREG.time += LoRa_led_struct.signal_time;
				HAL_GPIO_WritePin(LoRa_led_struct.ledREG.port, LoRa_led_struct.ledREG.pin, (LoRa_led_struct.ledREG.amt_signal == 1));
				LoRa_led_struct.ledREG.stage = 1;
			}
			else {
				--LoRa_led_struct.reg_count;
				LoRa_led_struct.ledREG.time += LoRa_led_struct.signal_time;
			}
		}
	}
	else {
		if(HAL_GetTick() - LoRa_led_struct.ledREG.time > LoRa_led_struct.wait_time){
			if(LoRa_led_struct.reg_count == 0) {
				LoRa_led_struct.reg_count = 10;
				LoRa_led_struct.ledREG.time += LoRa_led_struct.wait_time;
				HAL_GPIO_WritePin(LoRa_led_struct.ledREG.port, LoRa_led_struct.ledREG.pin, (LoRa_led_struct.ledREG.amt_signal == 0));
				LoRa_led_struct.ledREG.stage = 0;
			}
			else {
				--LoRa_led_struct.reg_count;
				LoRa_led_struct.ledREG.time += LoRa_led_struct.signal_time;
			}
		}
	}
}

// use in stm32f1xx_it.c

// ----- str ~53 -----
// Private user code ---------------------------------------------------------
// USER CODE BEGIN 0
// -> extern void lora_led_struct_time_work();
// USER CODE END 0

// ----- str ~182 -----
// USER CODE BEGIN SysTick_IRQn 1
// -> lora_led_struct_time_work();
// USER CODE END SysTick_IRQn 1
