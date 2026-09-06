/*
 * Copyright (c) 2026 Joona Kontiokoski
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "crc8.h"

static crc8_t conf = { 0 };

int main(int argc, char *argv[]) {
	if (argc <= 1) {
		printf("Usage:\n	Give: Polynomial(hex), Initial value(hex), xor value(hex), input reflection (0, 1), output reflection (0, 1), input data byte(hex), in this order.\n");
		return 0;
	};

	if (argc > 7) {
		printf("Too many arguments!\n");
		return 1;
	}

	uint8_t poly = (uint8_t)strtol(argv[1], NULL, 16);
	uint8_t init = (uint8_t)strtol(argv[2], NULL, 16);
	uint8_t xor = (uint8_t)strtol(argv[3], NULL, 16);
	uint8_t in_refl = (uint8_t)strtol(argv[4], NULL, 16);
	uint8_t out_refl = (uint8_t)strtol(argv[5], NULL, 16);
	uint8_t data = (uint8_t)strtol(argv[6], NULL, 16);

	crc8_init(&conf, poly, init, xor, (bool)in_refl, (bool)out_refl);
	printf("1-byte CRC: %#010x\n\n", crc8_calculate(&conf, &data, 1));
	
	printf("Look-up table:\n");

	for (size_t i = 0; i < 256; i++) {
		printf("%x ", conf.table[i]);

		if ((i + 1) % 8 == 0) {
			printf("\n");
		};
	}
}
