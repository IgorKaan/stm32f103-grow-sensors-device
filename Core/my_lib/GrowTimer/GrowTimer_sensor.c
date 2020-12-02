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
	*data = (((*data >> 24) & 0xFF)) | (((*data >> 16) & 0xFF) << 8 ) | (((*data >> 8) & 0xFF) << 16) | (((*data) & 0xFF) << 24 );
	sensor->data = *data;
}
