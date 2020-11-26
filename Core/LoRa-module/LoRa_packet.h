#ifndef __LORA_PACKET_H__
#define __LORA_PACKET_H__

#include <main.h>
#include <LoRa_module/LoRa_packet_data.h>


class LoRa_packet {
private:
    uint8_t* _data = nullptr;
    uint8_t _len = 0;
    uint8_t _rssi = 0;
    float _snr = 0;
    bool _crc_error = false;
public:
    LoRa_packet();
    LoRa_packet(uint8_t* data, uint8_t len, bool crc_err=false, uint8_t rssi=0, float snr=0);
    ~LoRa_packet();
    void set_packet(uint8_t* data, uint8_t len, bool crc_err=false, uint8_t rssi=0, float snr=0);

    uint8_t get_data(int num);
    uint8_t get_len();
    bool get_crc_error();
    uint8_t get_rssi();
    float get_snr();
    uint8_t& operator[] (const int index);
    class LoRa_packet& operator=(const class LoRa_packet& right);

    lora_packet get_strust();
};


#endif // __LORA_PACKET_H__
