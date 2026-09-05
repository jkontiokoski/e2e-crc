#include "crc8.h"
#include <stdio.h>

static crc8_opts_t opts = {
	.polynomial = 0x1D,
	.in_reflected = false,
	.out_reflected = false,
	.init_value = 0,
};

int main(void) {
	uint8_t data = 0xC2;
	printf("1-byte CRC: %#010x\n", crc8_calculate(&opts, &data, 1));
}
