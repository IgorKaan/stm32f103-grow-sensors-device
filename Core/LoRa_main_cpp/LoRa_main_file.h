#ifndef __LORA_MAIN_FILE_H__
#define __LORA_MAIN_FILE_H__

//#define CONTACT_DATA_MAX_PACKET 10
#include <main.h>

typedef struct {
	float lux;
	float temperature;
	float humidity;
	float pressure;
	float CO2;
	float TVOC;
	float water_temperature;
} SensorsDataTypeDef;

#endif // __LORA_MAIN_FILE_H__
