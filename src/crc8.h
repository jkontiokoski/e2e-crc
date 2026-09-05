#ifndef __CRC_8__
#define __CRC_8__

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum crc8_err {
	CRC8_ERR_DATA_NULL = 1,
	CRC8_ERR_INVALID_POLY,
} crc8_err_e;

typedef struct crc8_opts {
	uint8_t polynomial;
	uint8_t init_value;
	bool in_reflected;
	bool out_reflected;
} crc8_opts_t;

uint8_t crc8_calculate(const crc8_opts_t *options, const uint8_t *data, size_t len);

#ifdef __cplusplus
}
#endif

#endif
