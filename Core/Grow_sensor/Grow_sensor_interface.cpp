#include "Grow_sensor_interface.h"
#include "LoRa_main_file.h"

Grow_sensor_interface grow_sensor_interface;

extern const uint16_t LORA_ADDRESS_BRANCH;
extern uint8_t id_mas_sensors[COUNT_TYPE_SENSOR];
static std::array<LoRa_packet, CONTACT_DATA_MAX_PACKET> all_packets;
static uint8_t all_packets_len = 0; 

uint8_t data[50];

// --- Сохранение в энергонезависимую память ---

void Grow_sensor_interface::load_data(Grow_sensor &grow_sensor, LoRa_contact_data& contact_data, uint32_t adr, uint32_t channel) {
	LoRa_address address(adr);
    contact_data.set_my_adr(address);
    address.branch = 0;
    grow_sensor.set_address_control_module(address);
    contact_data.set_channel(channel);
    grow_sensor.set_active(2);
}
bool Grow_sensor_interface::save_data(const Grow_sensor &grow_sensor, const LoRa_contact_data& contact_data, uint32_t &adr, uint32_t &channel) {
	if(grow_sensor.get_active() != 2)
		return true;
	adr = (contact_data.get_my_adr().group << 16 | contact_data.get_my_adr().branch);
	//adr =
	channel = contact_data.get_channel();
	return false;
}

// --- Обмен с телефоном ---

// --- LoRa-соединение ---
void Grow_sensor_interface::send_registration_packet(const Grow_sensor &grow_sensor, LoRa_contact_data& contact_data) {
    LoRa_packet packet;
    packet_system.set_dest_adr(packet, LORA_GLOBAL_ADDRESS);
    packet_system.set_sour_adr(packet, LORA_GLOBAL_ADDRESS);
    packet_system.set_packet_type(packet, Packet_Type::SYSTEM);

    uint8_t com = 0;
    // uint8_t sensor_type = 0;
    uint8_t len = grow_sensor.get_count_component();
    uint8_t num_byte = 0;
    //uint8_t* data = new uint8_t[len + 6]; // ID, Type, Length
//    uint8_t data[AMT_COMPONENT + 2 + AMT_BYTES_SYSTEM_ID] = {0};

    for(int i = 0; i < AMT_BYTES_SYSTEM_ID; ++i)
    	data[num_byte++] = grow_sensor.get_system_id()[i];
//    data[num_byte++] = (grow_sensor.get_system_id() >> 24) & 0xFF;
//    data[num_byte++] = (grow_sensor.get_system_id() >> 16) & 0xFF;
//    data[num_byte++] = (grow_sensor.get_system_id() >> 8) & 0xFF;
//    data[num_byte++] = grow_sensor.get_system_id() & 0xFF;

    data[num_byte++] = 0x01; // Type = sensors

    data[num_byte++] = len; // Length = grow_sensor.get_count_component();
    for(int i = 0; i < len; ++i)
    // {
        grow_sensor.get_type(i, data[num_byte++]);
    //     grow_sensor.get_type(i, sensor_type);
    //     data[num_byte++] = sensor_type;
    // }
    packet_system.set_packet_data(packet, &com, data, &len);
    //delete[] data;
    contact_data.add_packet(std::move(packet));
    contact_data.broadcast_send();
}
Grow_sensor Grow_sensor_interface::read_regist_packet(LoRa_packet& packet) {
    // Получение длины
    uint8_t size;
    uint8_t err = 0;
    err = packet_system.get_size_by_packet(packet, size);
    if((err != 0) || (size == 0)) 
        return Grow_sensor();
    //Получение содержимого
    uint8_t com = 0;
    uint8_t len = 0;
    uint8_t* data = nullptr;
    data = new uint8_t[size]; // ID, Type, Length
    err = packet_system.get_packet_data(packet, &com, data, &len);
    if((err != 0) || (com != 0)) {
        return Grow_sensor();
    }
    // Расшифровка содержимого
    uint8_t num_byte = 0;
    std::array<uint8_t, AMT_BYTES_SYSTEM_ID> sensor_id;
    for(int i = 0; i < AMT_BYTES_SYSTEM_ID; ++i)
    	sensor_id[i]= data[num_byte++];
//    uint32_t sensor_id = data[num_byte++];
//    sensor_id = (sensor_id << 8) | data[num_byte++];
//    sensor_id = (sensor_id << 8) | data[num_byte++];
//    sensor_id = (sensor_id << 8) | data[num_byte++];
    // Генерация объекта
    Grow_sensor sensors(len, &(data[num_byte]));
    sensors.set_system_id(sensor_id);
    delete[] data;
    return sensors;
}

bool Grow_sensor_interface::check_regist_packet(Grow_sensor &grow_sensor, LoRa_contact_data& contact_data) {
    all_packets = contact_data.get_all_packet(all_packets_len);
    // проверить на то является ли пакет подтверждением регистрации, если да, то вернуть его индекс (?) -----
    for(int i = 0; i < all_packets_len; ++i) {
        if(packet_analyzer.get_packet_type(all_packets[i]) == Packet_Type::SYSTEM) {
        	uint8_t err = 0;
            uint8_t size = 0;
            err = packet_system.get_size_by_packet(all_packets[i], size);
            if((err != 0) || (size != (3+AMT_BYTES_SYSTEM_ID)))
            	continue;
            uint8_t com = 0x00;
            uint8_t len = 0;
//            uint8_t data[3 + AMT_BYTES_SYSTEM_ID];
            packet_system.get_packet_data(all_packets[i], &com, data, &len);
            if(com != 0x01)
            	continue;
            // static_cast<Packet_System*>(packet.packet)->get_packet_data(&com, data, &len);
            uint8_t num_byte = 0;
            std::array<uint8_t, AMT_BYTES_SYSTEM_ID> sensor_id;
            for(int i = 0; i < AMT_BYTES_SYSTEM_ID; ++i)
            	sensor_id[i]= data[num_byte++];
//            uint32_t sensor_id = data[num_byte++];
//            sensor_id = (sensor_id << 8) | data[num_byte++];
//            sensor_id = (sensor_id << 8) | data[num_byte++];
//            sensor_id = (sensor_id << 8) | data[num_byte++];
            if(sensor_id != grow_sensor.get_system_id())
                continue;
            grow_sensor.set_address_control_module(packet_system.get_sour_adr(all_packets[i]));
            contact_data.set_my_adr(LoRa_address(&data[num_byte]));
            num_byte += 3;
            grow_sensor.set_active(2);
            build_data_packet(grow_sensor, contact_data);
            return true;
        }
    }
    return false;
}

uint8_t Grow_sensor_interface::build_data_packet(Grow_sensor &grow_sensor, LoRa_contact_data& contact_data) {
//    if(contact_data.get_signal_start_connect())
//        return 0;
//    LoRa_packet packet;
//    uint8_t err = 0;
//    uint8_t amt = grow_sensor.get_count_component();
//    uint8_t param, id;
//    uint32_t value;
//    packet_sensor.set_setting(grow_sensor.get_setting());
//    contact_data.end_contact();
//    contact_data.clear_send_packet();
//    int i;
//    for(i = 0; i < amt; ++i) {
//    // last_send_packet_.packet->set_dest_adr(connect_adr_);
//    // last_send_packet_.packet->set_sour_adr(my_adr_);
//        packet_sensor.set_dest_adr(packet, contact_data.get_connect_adr()); // адреса задаются при передаче в LoRa_contact_data LORA_GLOBAL_ADDRESS
//        packet_sensor.set_sour_adr(packet, contact_data.get_my_adr()); // адреса задаются при передаче в LoRa_contact_data LORA_GLOBAL_ADDRESS
//        err = grow_sensor.get_type(i, param);
//        if(err) break;
//        err = grow_sensor.get_id(i, id);
//        if(err) break;
//        err = grow_sensor.get_value(i, *reinterpret_cast<float*>(&value));
//        if(err) break;
//        packet_sensor.set_packet_type(packet, Packet_Type::SENSOR);
//        err = packet_sensor.set_packet_data(packet, nullptr, &param, &id, &value);
//        if(err) break;
//        contact_data.add_packet(std::move(packet));
//    }
//    contact_data.wait_recipient();
//    return i;
	if(grow_sensor.get_active() == 0)
		return 0;
																					extern uint8_t STADY_CONACT_NUMBER;
																					STADY_CONACT_NUMBER = 1;
    if(contact_data.get_signal_start_connect())
        return 0;
																					STADY_CONACT_NUMBER = 2;
//															HAL_Delay(1000000);
    contact_data.end_contact();
    contact_data.clear_send_packet();
																					STADY_CONACT_NUMBER = 3;
    LoRa_packet packet;
    uint8_t err = 0;
    uint8_t amt = grow_sensor.get_count_component();
    uint8_t param, id;
    uint32_t value;
    packet_sensor.set_setting(grow_sensor.get_setting());
																					STADY_CONACT_NUMBER = 4;
    int i;
    for(i = 0; i < amt; ++i) {
    // last_send_packet_.packet->set_dest_adr(connect_adr_);
    // last_send_packet_.packet->set_sour_adr(my_adr_);
																					STADY_CONACT_NUMBER = 5;
        packet_sensor.set_dest_adr(packet, grow_sensor.get_address_control_module()); // адреса задаются при передаче в LoRa_contact_data LORA_GLOBAL_ADDRESS
        packet_sensor.set_sour_adr(packet, contact_data.get_my_adr()); // адреса задаются при передаче в LoRa_contact_data LORA_GLOBAL_ADDRESS
																					STADY_CONACT_NUMBER = 6;
        err = grow_sensor.get_type(i, param);
        if(err) break;
        err = grow_sensor.get_id(i, id);
        if(err) break;
        err = grow_sensor.get_value(i, *reinterpret_cast<float*>(&value));
        if(err) break;
        packet_sensor.set_packet_type(packet, Packet_Type::SENSOR);
																					STADY_CONACT_NUMBER = 7;
        err = packet_sensor.set_packet_data(packet, nullptr, &param, &id, &value);
        if(err) break;
																					STADY_CONACT_NUMBER = 8;
        contact_data.add_packet(std::move(packet));
    }
																					STADY_CONACT_NUMBER = 9;
    contact_data.wait_recipient(grow_sensor.get_address_control_module());
																					STADY_CONACT_NUMBER = 0;
    return i;
}
uint8_t Grow_sensor_interface::read_send_data_packet(Grow_sensor &grow_sensor, LoRa_packet* packet, uint8_t amt) {
    return 0; // (-) ----- (!) -----
}

// --- Отчётность ---
uint16_t Grow_sensor_interface::report_to_server(Grow_sensor &grow_sensor, uint8_t *buf, uint16_t size) {
//    uint16_t save_size = 0;
//    if(size < 5 + (6 * grow_sensor.get_count_component()))
//        return save_size;
//    uint8_t save_byte = 0;
//    float save_value = 0;
//    uint32_t save_component = grow_sensor.get_system_id();
//    // ID
//    buf[save_size++] = (save_component >> 24) & 0xFF;
//    buf[save_size++] = (save_component >> 16) & 0xFF;
//    buf[save_size++] = (save_component >>  8) & 0xFF;
//    buf[save_size++] =  save_component        & 0xFF;
//    // количество компонентов
//    buf[save_size++] = grow_sensor.get_count_component();
//    // состав компонентов
//    for(int i = 0; i < grow_sensor.get_count_component(); ++i) {
//        // тип
//        grow_sensor.get_type(i, save_byte);
//        buf[save_size++] = save_byte;
//        // номер
//        grow_sensor.get_id(i, save_byte);
//        buf[save_size++] = save_byte;
//        // значение
//        grow_sensor.get_value(i, save_value);
//        save_component = *reinterpret_cast<uint32_t*>(&save_value);
//        buf[save_size++] = (save_component >> 24) & 0xFF;
//        buf[save_size++] = (save_component >> 16) & 0xFF;
//        buf[save_size++] = (save_component >>  8) & 0xFF;
//        buf[save_size++] =  save_component        & 0xFF;
	    uint16_t save_size = 0;
	    if(size < 5 + (6 * grow_sensor.get_count_component()))
	        return save_size;
	    uint8_t save_byte = 0;
	    float save_value = 0;
	    unsigned char* pchar;
	    // ID
	    std::array<uint8_t, AMT_BYTES_SYSTEM_ID> sensor_id;
	    for(int i = 0; i < AMT_BYTES_SYSTEM_ID; ++i)
	        buf[save_size++] = sensor_id[i];
//	    uint32_t save_component = grow_sensor.get_system_id();
//	    buf[save_size++] = (save_component >> 24) & 0xFF;
//	    buf[save_size++] = (save_component >> 16) & 0xFF;
//	    buf[save_size++] = (save_component >>  8) & 0xFF;
//	    buf[save_size++] =  save_component        & 0xFF;
	    // количество компонентов
	    buf[save_size++] = grow_sensor.get_count_component();
	    // состав компонентов
	    for(int i = 0; i < grow_sensor.get_count_component(); ++i) {
	        // тип
	        grow_sensor.get_type(i, save_byte);
	        buf[save_size++] = save_byte;
	        // номер
	        grow_sensor.get_id(i, save_byte);
	        buf[save_size++] = save_byte;
	        // значение
	        grow_sensor.get_value(i, save_value);
	        pchar = reinterpret_cast<unsigned char*>(&save_value);
	        buf[save_size++] = (*(pchar++)) & 0xFF;
	        buf[save_size++] = (*(pchar++)) & 0xFF;
	        buf[save_size++] = (*(pchar++)) & 0xFF;
	        buf[save_size++] = (*(pchar++)) & 0xFF;
    }
    return save_size;
}
