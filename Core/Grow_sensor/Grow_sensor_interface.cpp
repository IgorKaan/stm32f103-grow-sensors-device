#include "Grow_sensor_interface.h"
#include "LoRa_main_file.h"

extern "C" {
#include <FlashPROM.h>
}

Grow_sensor_interface grow_sensor_interface;

static std::array<LoRa_packet, CONTACT_DATA_MAX_PACKET> all_packets;
static uint8_t all_packets_len = 0; 

uint8_t data[50];
uint8_t size;

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
    channel = contact_data.get_channel();
    return false;
}

// --- LoRa-соединение ---
void Grow_sensor_interface::send_registration_packet(const Grow_sensor &grow_sensor, LoRa_contact_data& contact_data) {
    LoRa_packet packet;
    uint8_t com = 0;
    uint8_t len = grow_sensor.get_count_component();
    uint8_t num_byte = 0;
    // Формирование данных пакета: ID, Type module, Count component, Type all component
    for(int i = 0; i < AMT_BYTES_SYSTEM_ID; ++i)
        data[num_byte++] = grow_sensor.get_system_id()[i];
    data[num_byte++] = len;  // Length = grow_sensor.get_count_component();
    data[num_byte++] = 0x01; // Type = sensors
    for(int i = 0; i < len; ++i)
        grow_sensor.get_type(i, data[num_byte++]);
    // Формирование пакета
    packet_system.set_dest_adr(packet, LORA_GLOBAL_ADDRESS);
    packet_system.set_sour_adr(packet, LORA_GLOBAL_ADDRESS);
    packet_system.set_packet_type(packet, Packet_Type::SYSTEM);
    packet_system.set_packet_data(packet, &com, data, &len);
    // Отправка пакета
    contact_data.add_packet(std::move(packet));
    contact_data.broadcast_send();
}

bool Grow_sensor_interface::check_contact_error(Grow_sensor &grow_sensor, LoRa_contact_data& contact_data) {
    if(grow_sensor.get_active() != 1)
        return false;
    grow_sensor.set_address_control_module(LORA_GLOBAL_ADDRESS);
    contact_data.set_my_adr(LORA_GLOBAL_ADDRESS);
    grow_sensor.set_active(0);
    return true;
}

bool Grow_sensor_interface::check_regist_packet(Grow_sensor &grow_sensor, LoRa_contact_data& contact_data) {
    all_packets = contact_data.get_all_packet(all_packets_len);
    // (!) ----- сделать сброс в 0 при отсутствии контакта в течении времени
    // проверить на то является ли пакет подтверждением регистрации, если да, то произвести попытку регистрации
    for(int i = 0; i < all_packets_len; ++i) {
        if(packet_analyzer.get_packet_type(all_packets[i]) == Packet_Type::SYSTEM) {
            uint8_t err = 0;
            err = packet_system.get_size_by_packet(all_packets[i], size);
            if((err != 0) || (size != (3+AMT_BYTES_SYSTEM_ID)))
                continue;
            uint8_t com = 0x00;
            uint8_t len = 0;
            packet_system.get_packet_data(all_packets[i], &com, data, &len);
            if(com != 0x01)
                continue;
            uint8_t num_byte = 0;
            std::array<uint8_t, AMT_BYTES_SYSTEM_ID> sensor_id;
            for(int i = 0; i < AMT_BYTES_SYSTEM_ID; ++i)
                sensor_id[i]= data[num_byte++];
            if(sensor_id != grow_sensor.get_system_id())
                continue;
            grow_sensor.set_address_control_module(packet_system.get_sour_adr(all_packets[i]));
            contact_data.set_my_adr(LoRa_address(&data[num_byte]));
            num_byte += 3;
            grow_sensor.set_active(1);
            return true;
        }
    }
    return false;
}

uint8_t Grow_sensor_interface::build_data_packet(Grow_sensor &grow_sensor, LoRa_contact_data& contact_data) {
    int i = 0;
    NVIC_DisableIRQ(EXTI15_10_IRQn);
    NVIC_DisableIRQ(EXTI2_IRQn);
    // __disable_irq();
    if(grow_sensor.get_active() == 2) {
        if(!contact_data.get_signal_start_connect()) {
            contact_data.end_contact();
            contact_data.clear_send_packet();
            uint8_t err = 0;
            uint8_t amt = grow_sensor.get_count_component();
            uint8_t param, id;
            uint32_t value;
            packet_sensor.set_setting(grow_sensor.get_setting());
            for(i = 0; i < amt; ++i) {
                LoRa_packet packet;
                // адреса задаются при передаче в LoRa_contact_data LORA_GLOBAL_ADDRESS
                packet_sensor.set_dest_adr(packet, grow_sensor.get_address_control_module());
                packet_sensor.set_sour_adr(packet, contact_data.get_my_adr());
                err = grow_sensor.get_type(i, param);
                if(err) break;
                err = grow_sensor.get_id(i, id);
                if(err) break;
                err = grow_sensor.get_value(i, *reinterpret_cast<float*>(&value));
                if(err) break;
                packet_sensor.set_packet_type(packet, Packet_Type::SENSOR);
                err = packet_sensor.set_packet_data(packet, nullptr, &param, &id, &value);
                if(err) break;
                contact_data.add_packet(std::move(packet));
            }
            contact_data.wait_recipient(grow_sensor.get_address_control_module());
        }
    }
    // __enable_irq();
    NVIC_EnableIRQ(EXTI2_IRQn);
    NVIC_EnableIRQ(EXTI15_10_IRQn);
    return i;
}
uint8_t Grow_sensor_interface::read_received_data_packets(Grow_sensor &grow_sensor, LoRa_contact_data& contact_data) {
    uint8_t amt_packets_processed = 0;
    // Модуль не зарегистрирован, контакта быть не должно
    if(grow_sensor.get_active() == 0)
        return amt_packets_processed;
    // обработка всех пришедших пакетов
    all_packets = contact_data.get_all_packet(all_packets_len);
    for(int i = 0; i < all_packets_len; ++i) {
        // Получение типа пакета
        Packet_Type type_packet = packet_analyzer.get_packet_type(all_packets[i]);
        // Получение ...

        // Обработка пакета
        switch (type_packet) {
        case Packet_Type::CONNECTION: {
            uint8_t err = 0;
            err = packet_connection.get_size_by_packet(all_packets[i], size);
            if(err != 0)
                break;
            err = contact_package_handler(grow_sensor, contact_data, all_packets[i]);
            if(err == 0) {
                ++amt_packets_processed;
            }
            break;
        }
        case Packet_Type::SYSTEM: {
            uint8_t err = 0;
            err = packet_system.get_size_by_packet(all_packets[i], size);
            if(err != 0)
                break;
            err = system_package_handler(grow_sensor, contact_data, all_packets[i]);
            if(err == 0) {
                ++amt_packets_processed;
            }
            break;
        }
        default: {
            break;
        }
        }
    }
    return 0;
}



uint8_t Grow_sensor_interface::contact_package_handler(Grow_sensor &grow_sensor, LoRa_contact_data& contact_data, LoRa_packet& packet) {
    uint8_t err = 0;
    uint8_t com = 0;
    uint8_t len = 0;
    err = packet_connection.get_packet_data(packet, &com, data, &len);
    switch(com) {
    case 0x00:
    case 0x01:
    case 0x02:
    case 0x03:
    case 0x04:
    case 0x05:
    case 0x06:
    case 0x07:
    case 0x08:
    case 0x0C: err = 2; break;

    case 0x09: {err = 3; break;} // Дополнительные настройки следующего пакета
    case 0x0A: {err = 3; break;} // Настройки передатчика
    case 0x0B: {err = 3; break;} // Состояние передатчика (З)

    default:
        err = 1;
        break;
    }
    // Error:
    // 0 - нет ошибки, пакет обработан
    // 1 - не распознан тип пакета
    // 2 - неверный тип пакета (пакет не может прийти при контакте)
    // 3 - нереализованна обработка
    return err;
}
uint8_t Grow_sensor_interface::system_package_handler(Grow_sensor &grow_sensor, LoRa_contact_data& contact_data, LoRa_packet& packet) {
    uint8_t err = 0;
    uint8_t com = 0;
    uint8_t len = 0;
    err = packet_system.get_packet_data(packet, &com, data, &len);
    switch(com) {
    case 0x00:
    case 0x01: err = 2; break;
    case 0x02: { // Установка канала связи
        if(len != 2) {
            err = 4;
            break;
        }
        uint16_t channel = data[0];
        channel = (channel << 8) | data[1];
        contact_data.set_channel(channel);
        grow_sensor.set_active(2);
        build_data_packet(grow_sensor, contact_data);

        //сохранение в ЭНП save_adr и save_channel
        uint32_t save_adr, save_channel;
        grow_sensor_interface.save_data(grow_sensor, contact_data, save_adr, save_channel);
        uint32_t control_module_id_and_channel[BUFFSIZE] = {save_adr, save_channel};
        Write_to_flash(control_module_id_and_channel);

        break;
    }
    case 0x03: { // Удаление модуля
        err = 3;
        break;
    }
    case 0x04: { // Перенос модуля
        err = 3;
        break;
    }
    case 0x05: { // Установка периода пробуждения модуля
        err = 3;
        break;
    }
    case 0x06: { // Установка времени пробуждения модуля
        err = 3;
        break;
    }
    case 0x07: { // Установка настройки работы модуля
        err = 3;
        break;
    }
    default:
        err = 1;
        break;
    }
    // Error:
    // 0 - нет ошибки, пакет обработан
    // 1 - не распознан тип пакета
    // 2 - неверный тип пакета (пакет не может прийти при контакте)
    // 3 - нереализованна обработка
    // 4 - ошибка пакета
    return err;
}
