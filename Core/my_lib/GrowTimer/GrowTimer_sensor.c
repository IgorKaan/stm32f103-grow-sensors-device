#include "GrowTimer_sensor.h"

//struct LoRa_sensor {
//	enum Type_sensor_t type;
//	uint8_t id;
//	uint32_t data;
//};

void lora_sensor_init(LoRa_sensor* sensor, enum Type_sensor_t type, uint8_t id) {
	sensor->type = type;
	sensor->id = id;
	sensor->data = 0;
	sensor->idata = 0;
}

void lora_sensor_set_data(LoRa_sensor* sensor, float value) {
	sensor->idata = value;
	uint32_t *data = (uint32_t*)(&value);
	sensor->data = *data;
}
