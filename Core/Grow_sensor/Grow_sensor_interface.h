#ifndef __GROW_SENSOR_INTERFACE_H__
#define __GROW_SENSOR_INTERFACE_H__

#include <Grow_sensor.h>
#include <Packet_analyzer.h>
#include <LoRa_packet.h>
#include <LoRa_contact_data.h>

#define GROUP_CONTROL_MODULE

class Grow_sensor_interface {
private:
public:
    Grow_sensor_interface() = default;
    ~Grow_sensor_interface() = default;

    /// --- Сохранение в энергонезависимую память ---
    // заполнение классов, загруженными значениями
    void load_data(Grow_sensor &grow_sensor, LoRa_contact_data& contact_data, uint32_t adr, uint32_t channel);
    // получение значений для сохранения классов
    bool save_data(const Grow_sensor &grow_sensor, const LoRa_contact_data& contact_data, uint32_t &adr, uint32_t &channel);


    /// --- Обмен с телефоном ---
    // фильтрация
    // кодовое представление (2 вида)

    /// --- LoRa-соединение ---
    // Регистрация (представиться) кодирование и декодирование
    void send_registration_packet(const Grow_sensor &grow_sensor, LoRa_contact_data& contact_data);  //----- ----- ()_-_()
    Grow_sensor read_regist_packet(LoRa_packet& packet);
    bool check_regist_packet(Grow_sensor &grow_sensor, LoRa_contact_data& contact_data);  //----- ----- ()_-_()
    // sitting (period) // device setting work 
    // Отправка и приём данных
    uint8_t build_data_packet(Grow_sensor &grow_sensor, LoRa_contact_data& contact_data);  //----- ----- ()_-_()
    uint8_t read_send_data_packet(Grow_sensor &grow_sensor, LoRa_packet* packet, uint8_t amt);

    /// --- Отчётность ---
    // Регистрация
    // Отправка данных (отчитывающийся объект, адрес массива, в size максимум | возврат - количество байт)
    uint16_t report_to_server(Grow_sensor &grow_sensor, uint8_t *buf, uint16_t size=(uint16_t)0xFFFFFFFF);

};

extern Grow_sensor_interface grow_sensor_interface;

#endif // __GROW_SENSOR_INTERFACE_H__
