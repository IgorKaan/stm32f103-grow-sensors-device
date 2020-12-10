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
//	uint16_t lux;
//	uint16_t temperature;
//	uint16_t humidity;
//	uint16_t pressure;
//	uint16_t CO2;
//	uint16_t TVOC;
} SensorsDataTypeDef;

#endif // __LORA_MAIN_FILE_H__
