#include "Address_field.h"

uint32_t value_range(uint32_t value, uint32_t min_value, uint32_t max_value) {
    if (value < min_value)
        return min_value;
    if (value > max_value)
        return max_value;
    return value;
}
uint16_t value_range(uint16_t value, uint16_t min_value, uint16_t max_value) {
    if (value < min_value)
        return min_value;
    if (value > max_value)
        return max_value;
    return value;
}
uint8_t  value_range(uint8_t  value, uint8_t  min_value, uint8_t  max_value) {
    if (value < min_value)
        return min_value;
    if (value > max_value)
        return max_value;
    return value;
}

Register::Register(uint16_t address, uint8_t bit_count, uint8_t bit_bias) {
    uint8_t bit_in_reg = 8;
    bit_count = value_range(bit_count, 1, bit_in_reg);
    bit_bias = value_range(bit_bias, 0, (bit_in_reg - bit_count));
    uint32_t mask = 0x00;
    for (uint8_t i = 0; i < bit_in_reg; ++i) {
        if (i < bit_count)
            mask = (mask << 1) + 1;
        else
            if (i < (bit_count + bit_bias))
                mask <<= 1;
    }
    _address = address;
    _bit_count = bit_count;
    _bit_bias = bit_bias;
    _mask = mask;
}

uint16_t Register::address() {
    return _address;
}
uint8_t Register::bit_count() {
    return _bit_count;
}
uint8_t Register::bit_bias() {
    return _bit_bias;
}
uint32_t Register::mask() {
    return _mask;
}

bool operator==(const Register& left, const Register& right) {
    if(left._address != right._address)
        return false;
    if(left._bit_count != right._bit_count)
        return false;
    if(left._bit_bias != right._bit_bias)
        return false;
    if(left._mask != right._mask)
        return false;
    return true;
}
bool operator!=(const Register& left, const Register& right) {
    return !(left == right);
}



Address_field::Address_field(Register *registers, uint8_t reg_count, bool reg_revers, char mode, uint32_t min_value,
                             uint32_t max_value, uint32_t *reserved_value, uint32_t reserv_count) {
    init_address_field(registers, reg_count, reg_revers, mode, min_value, max_value, reserved_value, reserv_count);
}

bool Address_field::init_address_field(Register *registers, uint8_t reg_count, bool reg_revers, char mode, uint32_t min_value,
                                       uint32_t max_value, uint32_t *reserved_value, uint32_t reserv_count) {
    if ((mode != 'r') && (mode != 'w') && (mode != 'c'))
        return true;
    uint8_t bit_count = 0;
    uint32_t value = 0;
    _mode = mode;
    _registers = registers;
    _reg_count = reg_count;
    _reg_revers = reg_revers;
    _reserved_value = reserved_value;
    _reserv_count = reserv_count;
    _max_address = 0;
    for (int i = 0; i < _reg_count; ++i) {
        bit_count += _registers[i].bit_count();
        if (_max_address < _registers[i].address())
            _max_address = _registers[i].address();
    }
    for (int i = 0; i < bit_count; ++i)
        value = (value << 1) + 1;
    _min_value = value_range(min_value, 0, value);
    _max_value = value_range(max_value, min_value, value);
    return false;
}

uint32_t Address_field::get_value(uint8_t *register_value, int register_count) {
    if (register_count < (_max_address + 1))
        return -1;
    uint32_t value = 0;
    if(_reg_revers) {
        for (int i = 0; i < _reg_count; ++i) {
            value <<= _registers[i].bit_count();
            value |= (register_value[_registers[i].address()] & _registers[i].mask()) >> _registers[i].bit_bias();
        }
    }
    else {
        for (int i = (_reg_count - 1); i >= 0; --i) {
            value <<= _registers[i].bit_count();
            value |= (register_value[_registers[i].address()] & _registers[i].mask()) >> _registers[i].bit_bias();
        }
    }
    return value;
}
bool Address_field::set_value(uint32_t value, uint8_t *register_value, int register_count) {
    if ((register_count < (_max_address + 1)) || (_mode == 'r') ||
                (value < _min_value) || (value > _max_value))
        return true;
    for (int i = 0; i < (int)_reserv_count; ++i)
        if (value == _reserved_value[i])
            return true;
    if(_reg_revers) {
        for (int i = (_reg_count - 1); i >= 0; --i) {
            register_value[_registers[i].address()] &= ~_registers[i].mask();
            register_value[_registers[i].address()] |= (value & (_registers[i].mask() >> _registers[i].bit_bias())) << _registers[i].bit_bias();
            value >>= _registers[i].bit_count();
        }
    }
    else {
        for (int i = 0; i < _reg_count; ++i) {
            register_value[_registers[i].address()] &= ~_registers[i].mask();
            register_value[_registers[i].address()] |= (value & (_registers[i].mask() >> _registers[i].bit_bias())) << _registers[i].bit_bias();
            value >>= _registers[i].bit_count();
        }
    }
    return false;
}

Register *Address_field::get_registers() {
    return _registers;
}
uint8_t Address_field::get_reg_count() {
    return _reg_count;
}
uint16_t Address_field::get_max_address() {
    return _max_address;
}
uint32_t Address_field::get_min_value() {
    return _min_value;
}
uint32_t Address_field::get_max_value() {
    return _max_value;
}
uint32_t *Address_field::get_reserved_value() {
    return _reserved_value;
}
uint32_t Address_field::get_reserv_count() {
    return _reserv_count;
}
char Address_field::get_mode() {
    return _mode;
}

bool operator==(const Address_field& left, const Address_field& right) {
    if(left._reg_count != right._reg_count)
        return false;
    if(left._max_address != right._max_address)
        return false;
    if(left._min_value != right._min_value)
        return false;
    if(left._max_value != right._max_value)
        return false;
    if(left._reserv_count != right._reserv_count)
        return false;
    if(left._mode != right._mode)
        return false;
    for(int i = 0; i < left._reg_count; ++i) {
        if(left._registers[i] != right._registers[i])
            return false;
    }
    for(int i = 0; i < (int)left._reserv_count; ++i) {
        if(left._reserved_value[i] != right._reserved_value[i])
            return false;
    }
    return true;
}
bool operator!=(const Address_field& left, const Address_field& right) {
    return !(left == right);
}
