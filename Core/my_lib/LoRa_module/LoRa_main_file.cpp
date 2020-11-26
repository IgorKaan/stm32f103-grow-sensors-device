#include "LoRa.h"
extern class LoRa_class LoRa;

extern "C" {

void LoRa_init(SPI_HandleTypeDef *spi) {
	return LoRa.init(spi);
}
uint8_t LoRa_field_set_one(Address_field field, uint32_t value, bool write) {
	return LoRa.field_set(field, value, write);
}
uint8_t LoRa_field_set(Address_field* fields, uint32_t* values, uint8_t amt, bool write) {
	return LoRa.field_set(fields, values, amt, write);
}
uint8_t LoRa_field_get_one(Address_field field, uint32_t* value, bool read) {
	return LoRa.field_get(field, value, read);
}
uint8_t LoRa_field_get(Address_field* fields, uint32_t* values, uint8_t amt, bool read) {
	return LoRa.field_get(fields, values, amt, read);
}
uint8_t LoRa_begin(uint64_t frequency, bool paboost, uint8_t signal_power, uint8_t SF, uint64_t SBW, uint8_t sync_word) {
	return LoRa.begin(frequency, paboost, signal_power, SF, SBW, sync_word);
}
void LoRa_end() {
	LoRa.end();
}
uint8_t LoRa_set_mode(uint8_t mode) {
	return LoRa.set_mode(mode);
}
uint8_t LoRa_mode_sleep() {
	return LoRa.mode_sleep();
}
uint8_t LoRa_mode_STDBY() {
	return LoRa.mode_STDBY();
}
uint8_t LoRa_mode_TX(bool set_dio) {
	return LoRa.mode_TX(set_dio);
}
uint8_t LoRa_mode_RX_continuous(bool set_dio) {
	return LoRa.mode_RX_continuous(set_dio);
}
uint8_t LoRa_mode_RX_single(bool set_dio) {
	return LoRa.mode_RX_single(set_dio);
}
uint8_t LoRa_mode_CAD(bool set_dio) {
	return LoRa.mode_CAD(set_dio);
}
uint8_t LoRa_set_TX_power(uint8_t power, bool paboost, uint8_t max_power) {
	return LoRa.set_TX_power(power, paboost, max_power);
}
uint8_t LoRa_set_frequency(uint64_t frequency) {
	return LoRa.set_frequency(frequency);
}
uint8_t LoRa_set_spreading_factor(uint8_t SF) {
	return LoRa.set_spreading_factor(SF);
}
uint8_t LoRa_set_signal_bandwidth(uint64_t sbw) {
	return LoRa.set_signal_bandwidth(sbw);
}
uint8_t LoRa_set_preamble_length(unsigned int length) {
	return LoRa.set_preamble_length(length);
}
uint8_t LoRa_set_sync_word(uint8_t SW) {
	return LoRa.set_sync_word(SW);
}
uint8_t LoRa_crc_enable() {
	return LoRa.crc_enable();
}
uint8_t LoRa_crc_disable() {
	return LoRa.crc_disable();
}
struct lora_packet LoRa_receiver_packet(uint8_t count, uint32_t wait, bool rssi, bool snr) {
	return LoRa.receiver_packet(count, wait, rssi, snr).get_strust();
}
struct lora_packet LoRa_read_packet_data(bool crc_err, bool rssi, bool snr) {
	return LoRa.read_packet_data(crc_err, rssi, snr).get_strust();
}
uint8_t LoRa_packet_rssi() {
	return LoRa.packet_rssi();
}
float LoRa_packet_snr() {
	return LoRa.packet_snr();
}
bool LoRa_sender_packet(uint8_t* packet, uint8_t len, uint32_t wait) {
	return LoRa.sender_packet(packet, len, wait);
}
bool LoRa_packet_begin() {
	return LoRa.packet_begin();
}
bool LoRa_packet_write(uint8_t* packet, uint8_t len) {
	return LoRa.packet_write(packet, len);
}
bool LoRa_packet_end(uint32_t wait, bool sleep) {
	return LoRa.packet_end(wait, sleep);
}

void packet_delete(struct lora_packet* packet) {
	if(packet->_data != nullptr) {
		delete[] packet->_data;
//		free(packet->_data);
		packet->_data = nullptr;
		packet->_len = 0;
	}
	packet->_rssi = 0;
	packet->_snr = 0;
	packet->_num = 0;
	packet->_crc_error = false;
}

void packet_init(struct lora_packet* packet) {
//	packet_delete(packet);
	packet->_data = nullptr;
	packet->_len = 0;
	packet->_rssi = 0;
	packet->_snr = 0;
	packet->_num = 0;
	packet->_crc_error = false;
}

void packet_set_len(struct lora_packet* packet, uint8_t len) {
	packet_delete(packet);
	packet->_len = len;
	if(len != 0) {
		packet->_data = new uint8_t[len];
	}
}

void packet_set_data(struct lora_packet* packet, uint8_t* data, uint8_t len) {
	packet_set_len(packet, len);
	for(int i = 0; i < len; ++i)
		packet->_data[i] = data[i];
}

void packet_data_add(struct lora_packet* packet, uint8_t data_byte) {
	packet->_data[packet->_num] = data_byte;
	++(packet->_num);
}

} // extern "C"
