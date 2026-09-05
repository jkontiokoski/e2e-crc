/*
 * Copyright (c) 2026 Joona Kontiokoski
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "crc8.h"

static inline uint8_t crc8_generate_input_normal(uint8_t crc, uint8_t polynomial);
static inline uint8_t crc8_generate_input_reflected(uint8_t crc, uint8_t polynomial);

uint8_t crc8_calculate(const crc8_t *config, const uint8_t *data, size_t len) {
	uint8_t crc = config->init_value;

	if (!data) { return crc; }

	for (uint8_t i = 0; i < len; i++) {
		uint8_t byte = (uint8_t)(data[i] ^ crc);
		crc = config->table[byte];
	}

	return crc ^ config->xor_value;
}

void crc8_init(crc8_t *config,
		const uint8_t polynomial,
		const uint8_t init_value,
		const uint8_t xor_value,
		const bool in_reflected,
		const bool out_reflected) {
	config->init_value = init_value;
	config->xor_value = xor_value;

	for (size_t i = 0; i < 256; i++) {
		uint8_t byte = i;

		for (uint8_t j = 0; j < 8; j++) {
			if (in_reflected) {
				byte = crc8_generate_input_reflected(byte, polynomial);
			}
			else {
				byte = crc8_generate_input_normal(byte, polynomial);
			}
		}

		if (out_reflected) {
			byte ^= 0xFF;
		}

		config->table[i] = byte;
	}
}

static inline uint8_t crc8_generate_input_normal(uint8_t crc, uint8_t polynomial) {
	if (crc & 0x80) {
		crc = (crc << 1) ^ polynomial;
	}
	else {
		crc <<= 1;
	}

	return crc;
}

static inline uint8_t crc8_generate_input_reflected(uint8_t crc, uint8_t polynomial) {
	polynomial ^= 0xFF;

	if (crc & 0x01) {
		crc = (crc >> 1) ^ polynomial;
	}
	else {
		crc >>= 1;
	}

	return crc;
}
