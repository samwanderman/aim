/*
 * SerialTest.cpp
 *
 *  Created on: 17.08.2020
 *      Author: Potapov Sergei
 *       Email: samwanderman@yandex.ru
 */

#include "../src/aim/connection/Serial.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cassert>

using namespace Aim;

void test01(const char* name, uint32_t baudrate) {
	printf("Test01\r\n");

	Serial::Config config;
	config.name		= name;
	config.baudrate = baudrate;
	Serial serial(config);
	assert(serial.open() == 0);

	uint8_t sendMessage[] = { 0x02, 'A', 'V', 'R' };
	int res = serial.write(sendMessage, sizeof(sendMessage));
	printf("bytesWritten: %i\r\n", res);
	assert(res == sizeof(sendMessage));

	uint8_t recvMessage[10];

	res = serial.read(recvMessage, sizeof(recvMessage));
	printf("bytesRead: %i\r\n", res);
	for (int i = 0; i < res; i++) {
		printf("%02X ", recvMessage[i]);
	}
	printf("\r\n");

	assert(serial.close() == 0);

	printf("complete\r\n");
}

void test02(const char* name, uint32_t baudrate) {
	printf("Test02\r\n");

	Serial::Config config;
	config.name		= name;
	config.baudrate = baudrate;
	config.nonBlock	= true;
	config.timeout	= 20;

	Serial serial(config);
	assert(serial.open() == 0);

	uint8_t sendMessage[] = { 0x02, 'A', 'V', 'R' };
	int res = serial.write(sendMessage, sizeof(sendMessage));
	printf("bytesWritten: %i\r\n", res);
	assert(res == sizeof(sendMessage));

	uint8_t recvMessage[10];

	int bytesRead = 0;
	while (bytesRead != 4) {
		res = serial.read(recvMessage, sizeof(recvMessage));
		if (res > 0) {
			bytesRead += res;
		}
		printf("bytesRead: %i\r\n", res);
		for (int i = 0; i < res; i++) {
			printf("%02X ", recvMessage[i]);
		}
		printf("\r\n");
	}

	assert(serial.close() == 0);

	printf("complete\r\n");
}

int main(int ac, char** av) {
	if (ac < 3) {
		printf("Usage:\r\n"
				"$ %s {port} {baudrate}\r\n",
				av[0]);
		return 0;
	}

	test01(av[1], atoi(av[2]));
	test02(av[1], atoi(av[2]));

	return 0;
}
