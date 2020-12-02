#include "GrowTimer_LoRa_module.h"

#define SENSOR 0x01
#define DEVICE 0x02

// private
void lora_module_send_packet(struct LoRa_module* module);
bool lora_module_recieve_packet(struct LoRa_module* module);

void lora_module_create_adr(struct LoRa_module* module);
bool lora_module_my_packet(struct LoRa_module* module);
uint8_t lora_module_reciv_packet_connect(struct LoRa_module* module);
void lora_module_send_packet_connect(struct LoRa_module* module, bool send_sensor);
void lora_module_send_packet_read_data(struct LoRa_module* module);
void lora_module_send_regist_packet(struct LoRa_module* module, SensorsDataTypeDef* sData);
bool lora_module_reciv_regist_packet(struct LoRa_module* module);
bool lora_module_reciv_packet_use_device(struct LoRa_module* module);


void lora_module_send_packet(struct LoRa_module* module) {
	if(module->led)
		lora_led_struct_set_OUT(module->packet._len);
	LoRa_sender_packet(module->packet._data, module->packet._len, 0);
//	LoRa_sender_packet(module->packet._data, module->packet._len, 2000);
    ++(module->num_packet);
}
// ----------------------------------------------------------------------------------------------------------
bool lora_module_recieve_packet(struct LoRa_module* module) {
	packet_delete(&(module->packet));
//	module->packet = LoRa_receiver_packet(1, 0, false, false);
	module->packet = LoRa_receiver_packet(1, 1000, false, false);
	if(module->packet._len != 0) {
		if(module->led)
			lora_led_struct_set_IN(module->packet._len);
		return true;
	}
	else
		return false;

}

void lora_module_create_adr(struct LoRa_module* module) {
	// Создание адреса
    uint16_t ran = ( *((uint32_t *)0x1FFFF7E8) + HAL_GetTick()) & 0x7FFF;
    while((ran == 0x0000) || (ran == 0x7FFF))
        ran = HAL_GetTick() & 0x7FFF;
    module->my_adr[0] = 0;
    module->my_adr[1] = (ran >> 8) & 0x7F;
    module->my_adr[2] = ran & 0xFF;
}

bool lora_module_my_packet(struct LoRa_module* module) {
    // пакет отправлен на этоустройство
	if(module->packet._len > 9) {
		if((module->packet._data[0] == module->my_adr[0]) &&
				(module->packet._data[1] == module->my_adr[1]) &&
				(module->packet._data[2] == module->my_adr[2])) {
			if(!(module->state_regist)) {
                // устройство не зарегестрировано (нет управляющего модуля)
				return true;
			}
			else {
                // устройство зарегестрировано, проверяем адрес управляющего модуля
				if((module->packet._data[3] == module->esp_adr[0]) &&
						(module->packet._data[4] == module->esp_adr[1]) &&
						(module->packet._data[5] == module->esp_adr[2])) {
					return true;
				}
			}
		}
	}
    return false;
}

uint8_t lora_module_reciv_packet_connect(struct LoRa_module* module) {
    if(lora_module_my_packet(module) && (module->state_regist)) {
        // если пакет типа запрос/ответ
        // если пакет на установку соединения
        // если размер пакета 10 байт
        if((module->packet._data[6] == 0) && (module->packet._data[9] == 0) && (module->packet._len > 10)) {
            if(module->packet._data[10] == 0xFF) {
                // если запрос на 0xFF отправляем данные с датчика
                return SENSOR;
            }
            else {
                // иначе - ждём пакетов с ESP-модуля
                return DEVICE;
            }
        }
    }
    return 0;
}

void lora_module_send_packet_connect(struct LoRa_module* module, bool send_sensor) {
    if(send_sensor) {
    	packet_set_len(&(module->packet), 12);
    	// отправка количества датчиков
    	module->packet._data[11] = module->amt_sensors;
    }
    else {
    	packet_set_len(&(module->packet), 11);
    }
    // отправка адреса управляющего модуля
    for(int i = 0; i < 3; ++i) {
    	packet_data_add(&(module->packet), module->esp_adr[i]);
    }
    // отправка своего адреса
    for(int i = 0; i < 3; ++i) {
    	packet_data_add(&(module->packet), module->my_adr[i]);
    }
    // отправка типа пакета
	packet_data_add(&(module->packet), 0x00);
    // отправка номера пакета
	packet_data_add(&(module->packet), ((module->num_packet >> 8) & 0xFF));
	packet_data_add(&(module->packet), ((module->num_packet) & 0xFF));
    // отправка пакета о подключении
	packet_data_add(&(module->packet), 0x01);
    // отправка статуса подключения
	packet_data_add(&(module->packet), 0x00);
    // отправка пакета
    lora_module_send_packet(module);
}

void lora_module_send_packet_read_data(struct LoRa_module* module) {
    for(int i = 0; i < module->amt_sensors; ++i) {
		packet_set_len(&(module->packet), 14);
	    // отправка адреса управляющего модуля
	    for(int i = 0; i < 3; ++i) {
	    	packet_data_add(&(module->packet), module->esp_adr[i]);
	    }
	    // отправка своего адреса
	    for(int i = 0; i < 3; ++i) {
	    	packet_data_add(&(module->packet), module->my_adr[i]);
	    }
	    // отправка типа пакета
		packet_data_add(&(module->packet), 0x01);
	    // отправка номера пакета
		packet_data_add(&(module->packet), ((module->num_packet >> 8) & 0xFF));
		packet_data_add(&(module->packet), ((module->num_packet) & 0xFF));
        // отправка типа устройства
		packet_data_add(&(module->packet), (uint8_t)(module->sensors[i].type));
        // отправка данных
        uint32_t data = module->sensors[i].data;
    	packet_data_add(&(module->packet), ((data >> 24) & 0xFF));
    	packet_data_add(&(module->packet), ((data >> 16) & 0xFF));
    	packet_data_add(&(module->packet), ((data >> 8) & 0xFF));
    	packet_data_add(&(module->packet), (data & 0xFF));
        // отправка пакета
        lora_module_send_packet(module);
    }
}

void lora_module_send_regist_packet(struct LoRa_module* module, SensorsDataTypeDef* sData) {
	uint8_t amt_module = module->amt_sensors + module->amt_devices;
	packet_set_len(&(module->packet), (11 + 4 + 2 * amt_module));
    for(int i = 0; i < 3; ++i) {
        // отправка 255.255.255 адреса приёмника, т.е. общий вызов
		packet_data_add(&(module->packet), 0xFF);
    }
    for(int i = 0; i < 3; ++i) {
        // отправка своего адреса
    	packet_data_add(&(module->packet), module->my_adr[i]);
    }
    // отправка типа пакета
	packet_data_add(&(module->packet), 0x03);
    // отправка номера пакета
	packet_data_add(&(module->packet), ((module->num_packet >> 8) & 0xFF));
	packet_data_add(&(module->packet), ((module->num_packet) & 0xFF));
    // отправка команды представления
	packet_data_add(&(module->packet), 0x00);
    // отправка id
//	packet_data_add(&(module->packet), 0x1);
//	packet_data_add(&(module->packet), 0x2);
//	packet_data_add(&(module->packet), 0x4);
//	packet_data_add(&(module->packet), 0x4);
		packet_data_add(&(module->packet), (uint8_t)sData->lux);
		packet_data_add(&(module->packet), 0x2);
		packet_data_add(&(module->packet), 0x4);
		packet_data_add(&(module->packet), 0x4);
    // отправка отправка количества модулей
	packet_data_add(&(module->packet), amt_module);
    // отправка данных каждого модуля
	packet_data_add(&(module->packet), SENSOR);
    for(int i = 0; i < module->amt_sensors; ++i) {
        // отправка данных каждого модуля
    	packet_data_add(&(module->packet), (uint8_t)(module->sensors[i].type));
    }
//    for(int i = 0; i < module->amt_devices; ++i) {
//        // отправка данных каждого модуля
//    	packet_data_add(&(module->packet), DEVICE);
//    	packet_data_add(&(module->packet), (uint8_t)(module->devices[i].type));
//    }
    // отправка пакета
    lora_module_send_packet(module);
}

bool lora_module_reciv_regist_packet(struct LoRa_module* module) {
	if(lora_module_my_packet(module) && (!(module->state_regist))) {
        // если пакет системного типа
		if(module->packet._data[6] == 0x03) {
            // если пакет на регистрацию
            if((module->packet._data[9] == 0x03) && (module->packet._len > 12)) {
                for(int i = 0; i < 3; ++i) {
                	module->esp_adr[i] = module->packet._data[i + 3];
                	module->my_adr[i] = module->packet._data[i + 10];
                }
                module->state_regist = true;
                return true;
            }
            else if(module->packet._data[9] == 0x01) {
            	lora_module_create_adr(module);
            	HAL_Delay(((uint32_t)(HAL_GetTick()) & 0x1FFF) + 1000); // ожидание от 1 до ~9 секунд
            	//lora_module_send_regist_packet(module);
                return true;
            }
        }
    }
    return false;
}
// ----------------------------------------------------------------------------------------------------------
bool lora_module_reciv_packet_use_device(struct LoRa_module* module) {
    bool result = false;
    if(lora_module_my_packet(module) && (module->state_regist)) {
        // если пакет типа управления устройствами
        if((module->packet._data[6] == 0x02) && (module->packet._len > 10)) {
            for(int i = 0; i < module->amt_devices; ++i) {
                if(module->packet._data[9] == module->devices[i].type) {
                	uint8_t command = module->packet._data[10];
                    // if по номеру id
                    if(command == 0x01) {
						if(lora_device_type_data[module->packet._data[9]].command_data[command] == 0x01) { // ON/OFF
							lora_device_set_data(&(module->devices[i]), (uint16_t)(module->packet._data[11]));
						}
						else if (lora_device_type_data[module->packet._data[9]].command_data[command] == 0x02) { // PWM
							uint16_t data = ((uint16_t)module->packet._data[11]) << 8;
							data |= module->packet._data[12];
							lora_device_set_data(&(module->devices[i]), data);
						}
						result = true;
                    }
                }
            }

        }
    }
    return result;
}

// public
struct LoRa_module lora_module_init(LoRa_sensor* sensors, uint8_t amt_sensors,
		struct LoRa_device* devices, uint8_t amt_devices, GPIO_TypeDef* ledIN_port,
		uint16_t ledIN_pin, GPIO_TypeDef* ledOUT_port, uint16_t ledOUT_pin,
		GPIO_TypeDef* ledREG_port, uint16_t ledREG_pin) {
	struct LoRa_module module;
	lora_module_create_adr(&module);
	module.esp_adr[0] = module.esp_adr[1] = module.esp_adr[2] = 0;

	module.state_regist = false;
	module.num_packet = 0;
	module.setting = 0;
	module.setting_sensors = 0;
	module.setting_devices = 0;

	module.amt_sensors = amt_sensors;
	module.amt_devices = amt_devices;
	module.sensors = sensors;
	module.devices = devices;

	module.led = !lora_led_struct_init(ledIN_port, ledIN_pin, ledOUT_port, ledOUT_pin, ledREG_port, ledREG_pin, 50, 25);

	packet_init(&(module.packet));
	return module;
}

void lora_module_introduce(struct LoRa_module* module, SensorsDataTypeDef* sData) {
	lora_module_send_regist_packet(module, sData);
}

bool lora_module_work(struct LoRa_module* module) {
	bool recieve_packet = lora_module_recieve_packet(module);
	if(recieve_packet) {
		// приём пакета
		switch (lora_module_reciv_packet_connect(module)) {
		case SENSOR:
			// ответ установки соединения
			lora_module_send_packet_connect(module, true);
			lora_module_send_packet_read_data(module);
			break;
		case DEVICE:
			// ответ установки соединения
			lora_module_send_packet_connect(module, false);
			break;
		default:
			// проверка на пакет ренистрации
			lora_module_reciv_regist_packet(module);
			// проверка на пакет управления устройствами
			lora_module_reciv_packet_use_device(module);
			break;
		}
		// удаление пакета
		packet_delete(&(module->packet));
	}
	return recieve_packet;
}

