#ifndef __SENSOR_DHT_H__
#define __SENSOR_DHT_H__

//#include <stm32f1xx.h>
//#include <main.h>
#include <stm32f1xx_hal.h>
#include <DelayDWT/DelayDWT.h>
#include <stdbool.h>

#define DHT_DATA 5
enum DHT_type {
    DHT11 = 0,
    DHT12,
    DHT21,
    DHT22
};

struct DHT_t {
  uint8_t  data[DHT_DATA];  // принимаемые пакеты
  GPIO_TypeDef*  port;      // порт выхода
  uint16_t  pin;             // номер выхода
  enum DHT_type  type;      // тип DHT
  uint32_t last_read_time;  // время последнего считывания (период в 2000 мс)
  uint32_t max_cycles;      // максимальная длина сигнала с DHT
  int8_t   result;          // корректность последнего считывания
  uint8_t  pull_time;       // время подготовки данных на DHT мс
};

struct DHT_t DHT_init(GPIO_TypeDef*  port, uint16_t pin, enum DHT_type type);

int8_t DHT_begin(struct DHT_t *dht); // (0 - нет ошибки)

int8_t DHT_check_sensor(struct DHT_t *dht); // команда считывания данных, возврат - корректность (0 - нет ошибки)
int8_t DHT_check_result(struct DHT_t *dht); // возврат - корректность (0 - нет ошибки)

float DHT_get_temperature(struct DHT_t *dht, bool ignore_error); // C
float DHT_get_humidity(struct DHT_t *dht, bool ignore_error);    // %

#endif // __SENSOR_DHT_H__
