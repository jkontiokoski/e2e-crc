/*
 * Copyright (c) 2026 Joona Kontiokoski
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */
#ifndef __CRC_8__
#define __CRC_8__

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct crc8_t {
	uint8_t init_value;
	uint8_t xor_value;
	uint8_t table[256];
} crc8_t;

void crc8_init(crc8_t *config,
		const uint8_t polynomial,
		const uint8_t init_value,
		const uint8_t xor_value,
		const bool in_reflected,
		const bool out_reflected);

uint8_t crc8_calculate(const crc8_t *config, const uint8_t *data, size_t len);

static inline void crc8_init_saej1850(crc8_t *config) {
	crc8_init(config, 0x1D, 0xFF, 0xFF, false, false);
}

static inline void crc8_init_saej1850zero(crc8_t *config) {
	crc8_init(config, 0x1D, 0x00, 0x00, false, false);
}

static inline void crc8_init_8h2f(crc8_t *config) {
	crc8_init(config, 0x2F, 0xFF, 0xFF, false, false);
}

#ifdef __cplusplus
}
#endif

#endif
