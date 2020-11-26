#ifndef __LORA_MAIN_FILE_H__
#define __LORA_MAIN_FILE_H__

#include <main.h>
#include <LoRa_module/LoRa_packet_data.h>

extern void LoRa_init(SPI_HandleTypeDef *spi);
extern uint8_t LoRa_begin(uint64_t frequency, bool paboost, uint8_t signal_power, uint8_t SF, uint64_t SBW, uint8_t sync_word);
extern void LoRa_end();
extern uint8_t LoRa_set_mode(uint8_t mode);
extern uint8_t LoRa_mode_sleep();
extern uint8_t LoRa_mode_STDBY();
extern uint8_t LoRa_mode_TX(bool set_dio);
extern uint8_t LoRa_mode_RX_continuous(bool set_dio);
extern uint8_t LoRa_mode_RX_single(bool set_dio);
extern uint8_t LoRa_mode_CAD(bool set_dio);
extern uint8_t LoRa_set_TX_power(uint8_t power, bool paboost, uint8_t max_power);
extern uint8_t LoRa_set_frequency(uint64_t frequency);
extern uint8_t LoRa_set_spreading_factor(uint8_t SF);
extern uint8_t LoRa_set_signal_bandwidth(uint64_t sbw);
extern uint8_t LoRa_set_preamble_length(unsigned int length);
extern uint8_t LoRa_set_sync_word(uint8_t SW);
extern uint8_t LoRa_crc_enable();
extern uint8_t LoRa_crc_disable();
extern struct lora_packet LoRa_receiver_packet(uint8_t count, uint32_t wait, bool rssi, bool snr);
extern struct lora_packet LoRa_read_packet_data(bool crc_err, bool rssi, bool snr);
extern uint8_t LoRa_packet_rssi();
extern float LoRa_packet_snr();
extern bool LoRa_sender_packet(uint8_t* packet, uint8_t len, uint32_t wait);
extern bool LoRa_packet_begin();
extern bool LoRa_packet_write(uint8_t* packet, uint8_t len);
extern bool LoRa_packet_end(uint32_t wait, bool sleep);
extern void packet_delete(struct lora_packet* packet);
extern void packet_init(struct lora_packet* packet);
extern void packet_set_len(struct lora_packet* packet, uint8_t len);
extern void packet_set_data(struct lora_packet* packet, uint8_t* data, uint8_t len);
extern void packet_data_add(struct lora_packet* packet,uint8_t data_byte);


#endif // __LORA_MAIN_FILE_H__
