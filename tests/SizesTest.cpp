/*
 * Sizes.cpp
 *
 *  Created on: 16.10.2020
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include <cstdint>
#include <cinttypes>
#include <cstdio>

int main() {
	printf("Size of uint8_t\t\t: %" PRIu64 "\r\n", sizeof(uint8_t));
	printf("Size of int8_t\t\t: %" PRIu64 "\r\n", sizeof(int8_t));
	printf("Size of uint16_t\t: %" PRIu64 "\r\n", sizeof(uint16_t));
	printf("Size of int16_t\t\t: %" PRIu64 "\r\n", sizeof(int16_t));
	printf("Size of uint32_t\t: %" PRIu64 "\r\n", sizeof(uint32_t));
	printf("Size of int32_t\t\t: %" PRIu64 "\r\n", sizeof(int32_t));
	printf("Size of uint64_t\t: %" PRIu64 "\r\n", sizeof(uint64_t));
	printf("Size of int64_t\t\t: %" PRIu64 "\r\n", sizeof(int64_t));
	printf("Size of float\t\t: %" PRIu64 "\r\n", sizeof(float));
	printf("Size of double\t\t: %" PRIu64 "\r\n", sizeof(double));
	printf("Size of bool\t\t: %" PRIu64 "\r\n", sizeof(bool));

	return 0;
}
