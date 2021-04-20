#ifndef __GROW_SENSOR_INTERFACE_H__
#define __GROW_SENSOR_INTERFACE_H__

#include <Grow_sensor.h>
#include <Packet_analyzer.h>
#include <LoRa_packet.h>
#include <LoRa_contact_data.h>

#define GROUP_CONTROL_MODULE

class Grow_sensor_interface {
private:
	uint8_t system_package_handler(Grow_sensor &grow_sensor, LoRa_contact_data& contact_data, LoRa_packet& packet);
	uint8_t contact_package_handler(Grow_sensor &grow_sensor, LoRa_contact_data& contact_data, LoRa_packet& packet);
public:
    Grow_sensor_interface() = default;
    ~Grow_sensor_interface() = default;

    /// --- Сохранение в энергонезависимую память ---
    // заполнение классов, загруженными значениями
    void load_data(Grow_sensor &grow_sensor, LoRa_contact_data& contact_data, uint32_t adr, uint32_t channel);
    // получение значений для сохранения классов
    bool save_data(const Grow_sensor &grow_sensor, const LoRa_contact_data& contact_data, uint32_t &adr, uint32_t &channel);

    /// --- LoRa-соединение ---
    // Регистрация (представиться) кодирование и декодирование
    void send_registration_packet(const Grow_sensor &grow_sensor, LoRa_contact_data& contact_data);
    bool check_contact_error(Grow_sensor &grow_sensor, LoRa_contact_data& contact_data);
    bool check_regist_packet(Grow_sensor &grow_sensor, LoRa_contact_data& contact_data);
    // Отправка и приём данных
    uint8_t build_data_packet(Grow_sensor &grow_sensor, LoRa_contact_data& contact_data);
    uint8_t read_received_data_packets(Grow_sensor &grow_sensor, LoRa_contact_data& contact_data);

};

extern Grow_sensor_interface grow_sensor_interface;

#endif // __GROW_SENSOR_INTERFACE_H__
