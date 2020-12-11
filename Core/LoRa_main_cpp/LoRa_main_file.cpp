#include "../LoRa_main_cpp/LoRa_main_file.h"
#include <LoRa_contact_data.h>
#include <Grow_sensor_component.h>
#include <Grow_sensor.h>
#include <Grow_sensor_interface.h>
#include <array>
extern "C" {
#include <FlashPROM.h>
}

constexpr std::array<uint8_t, AMT_BYTES_SYSTEM_ID> MODULE_ID =
		{0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x06, 0x05, 0x04, 0x03, 0x02, 0x03};

const uint8_t AMT_COMPONENT = 1;

Type_sensor sensor_array[AMT_COMPONENT] = { Illumination_level };

LoRa_contact_data contact_data;
Grow_sensor grow_sensor(AMT_COMPONENT, sensor_array);

extern uint32_t contact_status;

uint32_t lora_network_address = 0;
uint32_t lora_network_channel = 0;

uint32_t contact_count = 0;

enum {
    REGISTRATION_MODE = 0,
    WORKING_MODE
} current_mode;


extern "C" {

void Get_control_module_info_from_main(uint32_t* id_main) {
	lora_network_address = id_main[0];
	lora_network_channel = id_main[1];
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
	if (lora_network_address == 0x00000000) {
		current_mode = REGISTRATION_MODE;
		Send_registration_packet();
	}
	else {
		grow_sensor_interface.load_data(grow_sensor, contact_data, lora_network_address, lora_network_channel);
		current_mode = WORKING_MODE;
		contact_data.wait_recipient(grow_sensor.get_address_control_module());
	}
	return 0;
}

void Main_cpp(SensorsDataTypeDef* sensors_data) {
	grow_sensor.set_value(0, sensors_data->lux);
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
					uint32_t save_adr, save_channel;
					current_mode = WORKING_MODE;
					grow_sensor_interface.save_data(grow_sensor, contact_data, save_adr, save_channel);
					//сохранение в ЭНП save_adr и save_channel
					uint32_t control_module_id_and_channel[BUFFSIZE] = {save_adr, save_channel};
					Write_to_flash(control_module_id_and_channel);
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
	        	contact_count++;
	            contact_data.wait_recipient(grow_sensor.get_address_control_module());
	        }
		}
	}
}

} // extern "C"
