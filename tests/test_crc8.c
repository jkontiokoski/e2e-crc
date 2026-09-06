/*
 * Copyright (c) 2026 Joona Kontiokoski
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "unity/unity.h"
#include "crc8.h"

static crc8_t config = { 0 };

void setUp(void) {}
void tearDown(void) {}

void test_crc8_single_byte(void) {
	uint8_t data = 0x82;
	crc8_init(&config, 0x7, 0, 0, false, false);
	uint8_t result = crc8_calculate(&config, &data, 1);

	TEST_ASSERT_EQUAL(result, 0x87);
}

void test_crc8_multi_byte(void) {
	uint8_t data[] =  { 0x82, 0x07, 0xAE, 0x10 };
	crc8_init(&config, 0x7, 0, 0, false, false);
	uint8_t result = crc8_calculate(&config, data, 4);

	TEST_ASSERT_EQUAL(result, 0xB5);
}

void test_crc8_saej1850(void) {
	uint8_t data[] =  { 0x82, 0x07, 0xAE, 0x10 };
	crc8_init_saej1850(&config);
	uint8_t result = crc8_calculate(&config, data, 4);

	TEST_ASSERT_EQUAL(result, 0x5F);
}

void test_crc8_saej1850zero(void) {
	uint8_t data[] =  { 0x82, 0x07, 0xAE, 0x10 };
	crc8_init_saej1850zero(&config);
	uint8_t result = crc8_calculate(&config, data, 4);

	TEST_ASSERT_EQUAL(result, 0x06);
}

void test_crc8_8h2f(void) {
	uint8_t data[] =  { 0x82, 0x07, 0xAE, 0x10 };
	crc8_init_8h2f(&config);
	uint8_t result = crc8_calculate(&config, data, 4);

	TEST_ASSERT_EQUAL(result, 0xF2);
}

int main(void) {
	UNITY_BEGIN();

	RUN_TEST(test_crc8_single_byte, 19);
	RUN_TEST(test_crc8_multi_byte, 27);
	RUN_TEST(test_crc8_saej1850, 35);
	RUN_TEST(test_crc8_saej1850zero, 43);
	RUN_TEST(test_crc8_8h2f, 51);

	UNITY_END();
}
