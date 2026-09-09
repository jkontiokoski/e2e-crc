/*
 * Copyright (c) 2026 Joona Kontiokoski
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

#include "crc8.h"

static inline uint8_t crc8_generate_input_normal(uint8_t crc, uint8_t polynomial);
static inline uint8_t crc8_generate_input_reflected(uint8_t crc, uint8_t polynomial);
static inline uint8_t crc8_bit_reflection(uint8_t value);

uint8_t crc8_calculate(const crc8_t *config, const uint8_t *data, size_t len) {
	if (!data || !config) {
		return 0;
	}

	uint8_t crc = config->init_value;

	for (uint8_t i = 0; i < len; i++) {
		uint8_t byte = (uint8_t)(data[i] ^ crc);
		crc = config->table[byte];
	}

	if (config->reflect_output) {
		crc = crc8_bit_reflection(crc);
	}

	return crc ^ config->xor_value;
}

void crc8_init(crc8_t *config,
		const uint8_t polynomial,
		const uint8_t init_value,
		const uint8_t xor_value,
		const bool in_reflected,
		const bool out_reflected) {
	if (!config) {
		return;
	}

	config->init_value = init_value;
	config->xor_value = xor_value;
	config->reflect_output = (out_reflected != in_reflected);

	for (uint16_t i = 0; i < 256; i++) {
		uint8_t byte = i;

		for (uint8_t j = 0; j < 8; j++) {
			if (in_reflected) {
				byte = crc8_generate_input_reflected(byte, polynomial);
			}
			else {
				byte = crc8_generate_input_normal(byte, polynomial);
			}
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
	if (crc & 0x01) {
		crc = (crc >> 1) ^ crc8_bit_reflection(polynomial);
	}
	else {
		crc >>= 1;
	}

	return crc;
}

static inline uint8_t crc8_bit_reflection(uint8_t value) {
	value = (((value & 0x55) << 1) | ((value & 0xAA) >> 1));
	value = (((value & 0x33) << 2) | ((value & 0xCC) >> 2));
	value = (((value & 0x0F) << 4) | ((value & 0xF0) >> 4));

	return value;
}
