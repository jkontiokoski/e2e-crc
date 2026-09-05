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

int crc8_init(crc8_t *config,
		const uint8_t polynomial,
		const uint8_t init_value,
		const uint8_t xor_value,
		const bool in_reflected,
		const bool out_reflected);

uint8_t crc8_calculate(const crc8_t *config, const uint8_t *data, size_t len);

#ifdef __cplusplus
}
#endif

#endif
