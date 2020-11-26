#include "Sensor_DHT.h"

#define TIME_OUT ((uint32_t)(0x7FFFFFFF))

void DHT_pin_pull_up(struct DHT_t *dht);
void DHT_pin_output(struct DHT_t *dht, GPIO_PinState state);
int8_t DHT_check_pin(struct DHT_t *dht);
uint32_t DHT_check_pulse(struct DHT_t *dht, GPIO_PinState state);

struct DHT_t DHT_init(GPIO_TypeDef* port, uint16_t pin, enum DHT_type type) {
    int8_t i = 0;
    struct DHT_t dht;
    for (; i < DHT_DATA; ++i)
        dht.data[i] = 0;
    dht.port = port;
    dht.pin = pin;
    dht.type = type;
    dht.max_cycles = 1000;  // 2 секунды
    dht.last_read_time = HAL_GetTick() - 2000;
    dht.result = -1;
    dht.pull_time = 55;
    DWT_Init();
    return dht;
}


int8_t DHT_begin(struct DHT_t *dht) {
//    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    DHT_pin_pull_up(dht);
//    // установка
//    dht.max_cycles = 1000;  // секунда
//    dht->last_read_time = HAL_GetTick() - dht.max_cycles;
//    // dht->max_cycles = 0x7FFFFFFF; // ~3сек при 72МГц
//    dht->max_cycles = 0x0FFFFFFF; // ~3сек при 8МГц
    return 0;
}

// команда считывания данных, возврат - корректность
int8_t DHT_check_sensor(struct DHT_t *dht) {
    // проверка времени, прошло ли считывание
    if(HAL_GetTick() - dht->last_read_time < 2000) {
        dht->result = -1;
        return dht->result;
    }
    // обнуление выходов data[i]
    int8_t i;
    for (i = 0; i < DHT_DATA; ++i)
        dht->data[i] = 0;

    // Подтягивание к HIGH, сообщая о контакте
    DHT_pin_pull_up(dht);
    HAL_Delay(1);
    // + delay(1); // ожидание 1мс

    // Установка низкого уровня (по времени в соответствии с типом датчика)
    DHT_pin_output(dht, GPIO_PIN_RESET);
    switch (dht->type) {
    case DHT22:
    case DHT21:
    	HAL_Delay(2);
        // + delayMicroseconds(1100); // ожидание минимум  ~1мс
        break;
    case DHT11:
    case DHT12:
    default:
    	HAL_Delay(20);
        // + delay(20); // ожидание минимум 18мс
        break;
    }

    uint32_t cycles[80];

    // Завершение сигнала запуска, установкой высокого уровеня на 40 микросекунд.
    DHT_pin_pull_up(dht);
    // Задержка pullTime, стандартно 55, чтобы датчик успел потянуть линию данных на низкое значение.

    DWT_Delay_us(dht->pull_time);

//    uint32_t count = 0;
//    while (count < 28) {
//    	++count;
//        if (HAL_GetTick() - 1 >= dht->max_cycles);
//        DHT_check_pin(dht);
//    }

    //mks_delay(dht->pull_time);
    // + delayMicroseconds(pullTime);

    // Ожидание сигналов от DHT

    // Блокировка прерываний, булут мешать корректному считыванию
    // - InterruptLock lock;

    // Сначала идёт низкий сигнал ~80мс, потом высокий ~80 мс
    uint32_t time1 = DHT_check_pulse(dht, GPIO_PIN_RESET);
    if (DHT_check_pulse(dht, GPIO_PIN_RESET) == TIME_OUT) {
        dht->result = -1;
        return dht->result;
    }
    uint32_t time2 = DHT_check_pulse(dht, GPIO_PIN_SET);
    if (DHT_check_pulse(dht, GPIO_PIN_SET) == TIME_OUT) {
        dht->result = -1;
        return dht->result;
    }

    // DHT отправляет 40 бит информации следующим образом:
    // ~50мс низкий сигнал, потом ~28мс высокий => 0
    // ~50мс низкий сигнал, потом ~70мс высокий => 1
    // В буфер сохраняются длительность каждой волны (=> 80 значений)
    // Их обработка происходит после.
    for (i = 0; i < 80; i += 2) {
        cycles[i] = DHT_check_pulse(dht, GPIO_PIN_RESET);
        cycles[i + 1] = DHT_check_pulse(dht, GPIO_PIN_SET);
    }

    // Расшифровка полученных значений
    for (int i = 0; i < 40; ++i) {
        uint32_t low_cycles = cycles[2 * i];
        uint32_t high_cycles = cycles[2 * i + 1];
        if ((low_cycles == TIME_OUT) || (high_cycles == TIME_OUT)) {
            dht->result = -1;
            return dht->result;
        }
        dht->data[i / 8] <<= 1;
        // Проверка пришедшего сигнала (0 или 1)
        if (high_cycles > low_cycles) {
            dht->data[i / 8] |= 1;
        }
    }

    // Проверка контрольной суммы пришедшего пакета
    uint8_t check = dht->data[0] + dht->data[1] + dht->data[2] + dht->data[3];
    if (dht->data[4] == (check & 0xFF)) {
        dht->result = 0;
    } else {
        dht->result = -1;
    }
    return dht->result;
}

// возврат - корректность
int8_t DHT_check_result(struct DHT_t *dht) {
    return dht->result;
}

// C
float DHT_get_temperature(struct DHT_t *dht, bool ignore_error) {
    float temp = -273.15;
     if((dht->result == 0) || ignore_error) {
        switch (dht->type) {
        case DHT11:
            temp = dht->data[2];
            if (dht->data[3] & 0x80) {
                temp = -1 - temp;
            }
            temp += (dht->data[3] & 0x0F) * 0.1;
            break;
        case DHT12:
        temp = dht->data[2];
        temp += (dht->data[3] & 0x0F) * 0.1;
        if (dht->data[2] & 0x80) {
            temp *= -1;
        }
        break;
        case DHT22:
        case DHT21:
        temp = ((uint16_t)(dht->data[2] & 0x7F)) << 8 | dht->data[3];
        temp *= 0.1;
        if (dht->data[2] & 0x80) {
            temp *= -1;
        }
        break;
        }
    }
    return temp;
}
// %
float DHT_get_humidity(struct DHT_t *dht, bool ignore_error) {
    float hum = -100;
    if((dht->result == 0) || ignore_error) {
        switch (dht->type) {
        case DHT11:
        case DHT12:
            hum = dht->data[0] + dht->data[1] * 0.1;
            break;
        case DHT22:
        case DHT21:
            hum = ((uint16_t)dht->data[0]) << 8 | dht->data[1];
            hum *= 0.1;
        break;
        }
    }
    return hum;
}

void DHT_pin_pull_up(struct DHT_t *dht) {
	// настройка пина DHT на вход с подтяжкой вверх
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = dht->pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(dht->port, &GPIO_InitStruct);
//    // настройка пина DHT на вход с подтяжкой вверх (CNF = 10, MODE = 00, ODR = 1)
//    if (dht->pin < 8) {
//        // обнуляем текущее значение выхода, CNF = MODE = 00
//        dht->port->CRL &= ~((GPIO_CRL_MODE0 | GPIO_CRL_CNF0) << (dht->pin * 4));
//        // устанавливаем CNF = 10, MODE = 00
//        dht->port->CRL |= GPIO_CRL_CNF0_1 << (dht->pin * 4);
//    }
//    else {
//        // обнуляем текущее значение выхода, CNF = MODE = 00
//        dht->port->CRH &= ~((GPIO_CRH_MODE8 | GPIO_CRH_CNF8) << ((dht->pin - 8) * 4));
//        // устанавливаем CNF = 10, MODE = 00
//        dht->port->CRL |= GPIO_CRH_CNF8_1 << ((dht->pin - 8) * 4);
//    }
//    // устанавливаем ODR = 1
//    dht->port->ODR |= GPIO_ODR_ODR0 << dht->pin;
}

void DHT_pin_output(struct DHT_t *dht, GPIO_PinState state) {
	// настройка пина DHT на выход
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = dht->pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(dht->port, &GPIO_InitStruct);
	// установка значения выхода
	HAL_GPIO_WritePin(dht->port, dht->pin, state);
//    // настройка пина DHT на выход со значением level (CNF = 01, MODE = 01, ODR = level)
//    if (dht->pin < 8) {
//        // обнуляем текущее значение выхода, CNF = MODE = 00
//        dht->port->CRL &= ~((GPIO_CRL_MODE0 | GPIO_CRL_CNF0) << (dht->pin * 4));
//        // устанавливаем CNF = 01, MODE = 01
//        dht->port->CRL |= GPIO_CRL_CNF0_0 << (dht->pin * 4);
//        dht->port->CRL |= GPIO_CRL_MODE0_0 << (dht->pin * 4);
//    }
//    else {
//        // обнуляем текущее значение выхода, CNF = MODE = 00
//        dht->port->CRH &= ~((GPIO_CRH_MODE8 | GPIO_CRH_CNF8) << ((dht->pin - 8) * 4));
//        // устанавливаем CNF = 01, MODE = 01
//        dht->port->CRL |= GPIO_CRH_CNF8_0 << ((dht->pin - 8) * 4);
//        dht->port->CRL |= GPIO_CRH_MODE8_0 << ((dht->pin - 8) * 4);
//    }
//    // устанавливаем ODR = level
//    if (level == GPIO_PIN_RESET) {
//        // = 0
//        dht->port->ODR &= ~(GPIO_ODR_ODR0 << dht->pin);
//    }
//    else {
//        // = 1
//        dht->port->ODR |= GPIO_ODR_ODR0 << dht->pin;
//    }
}

int8_t DHT_check_pin(struct DHT_t *dht) {
//    uint32_t level = dht->port->IDR & (GPIO_IDR_IDR0 << dht->pin);
    GPIO_PinState state = HAL_GPIO_ReadPin(dht->port, dht->pin);
    if (state == GPIO_PIN_RESET) {
        return GPIO_PIN_RESET; // = 0
    }
    return GPIO_PIN_SET; // = 1
}

uint32_t DHT_check_pulse(struct DHT_t *dht, GPIO_PinState state) {
    uint32_t time = HAL_GetTick();
    uint32_t count = 0;
    while (DHT_check_pin(dht) == state) {
    	++count;
        if (HAL_GetTick() - time >= dht->max_cycles)
            return TIME_OUT;
    }
    return count;
}
