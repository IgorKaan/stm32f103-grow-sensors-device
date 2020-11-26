#ifndef __ADDRESS_FIELD_H__
#define __ADDRESS_FIELD_H__

#include <main.h>

uint32_t value_range(uint32_t value, uint32_t min_value=0, uint32_t max_value=0xFFFFFFFF);
uint16_t value_range(uint16_t value, uint16_t min_value=0, uint16_t max_value=0xFFFF);
uint8_t  value_range(uint8_t  value, uint8_t  min_value=0, uint8_t  max_value=0xFF);

class Register {
private:
    uint16_t _address;
    uint8_t _bit_count;
    uint8_t _bit_bias;
    uint32_t _mask;
public:
    Register(uint16_t address = 0, uint8_t bit_count = 8, uint8_t bit_bias = 0);
    ~Register() = default;
    uint16_t address();
    uint8_t bit_count();
    uint8_t bit_bias();
    uint32_t mask();

    friend bool operator==(const Register& left, const Register& right);
    friend bool operator!=(const Register& left, const Register& right);
} typedef Register;

class Address_field {
private:
    Register *_registers;
    uint8_t _reg_count;
    bool _reg_revers;
    uint16_t _max_address;
    uint32_t _min_value;
    uint32_t _max_value;
    uint32_t *_reserved_value;
    uint32_t _reserv_count;
    char _mode;
public:
    Address_field() = default;
    Address_field(Register *registers, uint8_t reg_count=1, bool reg_revers=false, char mode='w', uint32_t min_value=0,
                  uint32_t max_value=(-1), uint32_t *reserved_value=nullptr, uint32_t reserv_count=0);
    ~Address_field() = default;
    bool init_address_field(class Register *registers, uint8_t reg_count=1, bool reg_revers=false, char mode='w', uint32_t min_value=0,
                  uint32_t max_value=(-1), uint32_t *reserved_value=nullptr, uint32_t reserv_count=0);

    uint32_t get_value(uint8_t *register_value, int register_count=(uint16_t(-1)));
    bool set_value(uint32_t value, uint8_t *register_value, int register_count=(uint16_t(-1)));

    Register *get_registers();
    uint8_t get_reg_count();
    uint16_t get_max_address();
    uint32_t get_min_value();
    uint32_t get_max_value();
    uint32_t *get_reserved_value();
    uint32_t get_reserv_count();
    char get_mode();

    friend bool operator==(const Address_field& left, const Address_field& right);
    friend bool operator!=(const Address_field& left, const Address_field& right);
} typedef Address_field;

#endif // __ADDRESS_FIELD_H__
