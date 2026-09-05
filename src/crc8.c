#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "crc8.h"

static inline uint8_t crc8_generate_input_normal(uint8_t crc, uint8_t polynomial);
static inline uint8_t crc8_generate_input_reflected(uint8_t crc, uint8_t polynomial);

uint8_t crc8_calculate(const crc8_opts_t *options, const uint8_t *data, size_t len) {
	uint8_t crc = options->init_val;

	if (!data) { return crc; }

	for (uint8_t i = 0; i < len; i++) {
		crc ^= data[i];

		for (uint8_t j = 0; j < 8; j++) {
			if (options->in_refl) {
				crc = crc8_generate_input_reflected(crc, options->polynomial);
			}
			else {
				crc = crc8_generate_input_normal(crc, options->polynomial);
			}
		}
	}

	if (options->out_refl) {
		crc ^= 0xFF;
	}

	return crc;
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
