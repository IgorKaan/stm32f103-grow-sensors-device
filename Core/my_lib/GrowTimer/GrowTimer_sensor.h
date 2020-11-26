#ifndef __GROWTIMER_SENSOR_H__
#define __GROWTIMER_SENSOR_H__
#include <stm32f1xx_hal.h>

#include <stdbool.h>

enum Type_sensor_t {
	Analog_signal = 0,
	Discrete_signal,
	Battery_charge,
	Air_humidity,
	Air_temperature,
	Water_temperature,
	Illumination_level,
	Lamp_power,
	Pump_power,
	Indicator_pH,
	Indicator_EC,
	Indicator_eCO2,
	Indicator_nYVOC
};

typedef struct {
	enum Type_sensor_t type;
	uint8_t id;
	uint32_t data;
	float idata;
} LoRa_sensor;

void lora_sensor_init(LoRa_sensor* sensor, enum Type_sensor_t type, uint8_t id);
void lora_sensor_set_data(LoRa_sensor* sensor, float value);

#endif // __GROWTIMER_SENSOR_H__
