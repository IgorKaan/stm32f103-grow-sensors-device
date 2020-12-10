#include "../LoRa_main_cpp/LoRa_main_file.h"
#include <LoRa_contact_data.h>
#include <Grow_sensor_component.h>
#include <Grow_sensor.h>
#include <Grow_sensor_interface.h>
#include <array>

constexpr std::array<uint8_t, AMT_BYTES_SYSTEM_ID> MODULE_ID =
		{0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x06, 0x05, 0x04, 0x03, 0x02, 0x03};
//constexpr uint8_t CONTACT_DATA_MAX_PACKET = 10;

const uint8_t AMT_COMPONENT = 1;

Type_sensor sensor_array[AMT_COMPONENT] = { Illumination_level };

LoRa_contact_data contact_data;
Grow_sensor grow_sensor(AMT_COMPONENT, sensor_array);

extern uint32_t contact_status;


enum {
    REGISTRATION_MODE = 0,
    WORKING_MODE
} current_mode;


extern "C" {

bool Init_lora_module(SPI_HandleTypeDef *spi) {
	return contact_data.init_lora_module(spi);
}
uint8_t Begin_lora_module(uint64_t frequency, bool paboost, uint8_t signal_power, uint8_t SF, uint64_t SBW, uint8_t sync_word) {
	current_mode = REGISTRATION_MODE;
	grow_sensor.set_system_id(MODULE_ID);
	return contact_data.begin_lora_module(frequency, paboost, signal_power, SF, SBW, sync_word);
}

void Main_cpp(SensorsDataTypeDef* sensors_data) {
	grow_sensor.set_value(0, sensors_data->lux);
	grow_sensor_interface.build_data_packet(grow_sensor, contact_data);
//	sensors_data.lux
}

void Send_registration_packet() {
	grow_sensor_interface.send_registration_packet(grow_sensor, contact_data);
	//contact_data.broadcast_receive();
}

void Contact_group_control_module() {
	contact_status = contact_data.work_contact_system();
	switch (current_mode) {
		case (REGISTRATION_MODE): {
			if(contact_data.get_signal_complete()) {
				contact_data.broadcast_receive(); // Ожидаем ответа на запрос или ошибку запроса
			}
			if(contact_data.get_state_contact() == SC_PACKET_ACCEPTED) {
				if(grow_sensor_interface.check_regist_packet(grow_sensor, contact_data)) {
					current_mode = WORKING_MODE;
					contact_data.wait_recipient(grow_sensor.get_address_control_module()); // Начинаем слушать на наличие управляющих пакетов
					break;
				}
			}
	        break;
		}
		case (WORKING_MODE): {
	        if(contact_status != 0) {
	            contact_data.wait_recipient(grow_sensor.get_address_control_module());
	        }
	        if(contact_data.get_signal_complete()) {
	            contact_data.wait_recipient(grow_sensor.get_address_control_module());
	        }
		}
	}
}

} // extern "C"
