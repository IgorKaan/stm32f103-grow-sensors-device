#include "../LoRa_main_cpp/LoRa_main_file.h"
#include <LoRa_contact_data.h>
#include <Grow_sensor_component.h>
#include <Grow_sensor.h>
#include <Grow_sensor_interface.h>
#include <array>

constexpr std::array<uint8_t, AMT_BYTES_SYSTEM_ID> MODULE_ID =
        {0x5f, 0xdc, 0xbe, 0xda, 0x5f, 0x25, 0x97, 0x30, 0x86, 0x17, 0x08, 0xa1};
//		{0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x06, 0x06, 0x06, 0x01, 0x01, 0x01};
//        {0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x06, 0x06, 0x06};
//        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
//		  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

//const uint8_t AMT_COMPONENT = 1;
//Type_sensor sensor_array[AMT_COMPONENT] = { Illumination_level };

const uint8_t AMT_COMPONENT = 3;
//Type_sensor sensor_array[AMT_COMPONENT] = { Air_humidity, Air_temperature, Illumination_level };
Type_sensor sensor_array[AMT_COMPONENT] = { Air_humidity, Air_temperature, Indicator_eCO2 };


LoRa_contact_data contact_data;
Grow_sensor grow_sensor(AMT_COMPONENT, sensor_array);

uint32_t contact_status;

uint32_t control_module_adr = 0;
uint32_t control_module_channel = 0;


enum {
    REGISTRATION_MODE = 0,
    WORKING_MODE
} current_mode;


extern "C" {

void Get_control_module_info_from_main(uint32_t* id_main) {
	control_module_adr = id_main[0];
	control_module_channel = id_main[1];
}

void Send_registration_packet() {
	grow_sensor_interface.send_registration_packet(grow_sensor, contact_data);
}

bool Init_lora_module(SPI_HandleTypeDef *spi) {
	return contact_data.init_lora_module(spi);
}
uint8_t Begin_lora_module(uint64_t frequency, bool paboost, uint8_t signal_power, uint8_t SF, uint64_t SBW, uint8_t sync_word) {
	grow_sensor.set_system_id(MODULE_ID);
	contact_data.begin_lora_module(frequency, paboost, signal_power, SF, SBW, sync_word);
	if (control_module_adr == 0x00000000) {
		current_mode = REGISTRATION_MODE;
		Send_registration_packet();
	}
	else {
		grow_sensor_interface.load_data(grow_sensor, contact_data, control_module_adr, control_module_channel);
		current_mode = WORKING_MODE;
		contact_data.wait_recipient(grow_sensor.get_address_control_module());
	}
	return 0;
}

void Main_cpp(SensorsDataTypeDef* sensors_data) {
//	grow_sensor.set_value(0, sensors_data->lux);
	grow_sensor.set_value(0, sensors_data->humidity);
	grow_sensor.set_value(1, sensors_data->temperature);
	grow_sensor.set_value(2, sensors_data->CO2);
	grow_sensor_interface.build_data_packet(grow_sensor, contact_data);
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
	        	if(grow_sensor_interface.check_contact_error(grow_sensor, contact_data)) {
					current_mode = REGISTRATION_MODE;
	        		contact_data.broadcast_receive();
	        	}
	        	else {
	        		contact_data.wait_recipient(grow_sensor.get_address_control_module());
	        	}
	        }
	        if(contact_data.get_signal_complete()) {
	        	grow_sensor_interface.read_received_data_packets(grow_sensor, contact_data);
	            contact_data.wait_recipient(grow_sensor.get_address_control_module());
	        }
		}
	}
}

} // extern "C"
