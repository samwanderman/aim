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
	printf("Test01 ");

	Serial::Config config;
	config.name		= name;
	config.baudrate = baudrate;
	Serial serial(config);
	assert(serial.open() == 0);

	uint8_t sendMessage[] = { 0x02, 'A', 'V', 'R' };
	assert(serial.write(sendMessage, sizeof(sendMessage)) == sizeof(sendMessage));

	uint8_t recvMessage[10];

	int res = serial.read(recvMessage, sizeof(recvMessage));
	printf("read %i bytes\r\n", res);
	for (int i = 0; i < res; i++) {
		printf("%02X ", recvMessage[i]);
	}
	printf("\r\n");

	res = serial.read(recvMessage, sizeof(recvMessage), 200);
	printf("res is %i", res);

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

	return 0;
}
