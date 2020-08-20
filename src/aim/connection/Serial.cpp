/*
 * Serial.cpp
 *
 *  Created on: 17.08.2020
 *      Author: Potapov Sergei
 *       Email: samwanderman@yandex.ru
 */

#include "Serial.h"

#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <cstdio>

namespace Aim {

Serial::Serial(Config config) {
	this->config	= config;
	this->fd		= -1;
}

Serial::Serial(Serial&& other) {
	this->config	= other.config;
	this->fd		= other.fd;
	other.fd		= -1;
}

Serial::~Serial() {}

Serial& Serial::operator=(Serial&& other) {
	this->config	= other.config;
	this->fd		= other.fd;
	other.fd		= -1;

	return *this;
}

int Serial::open() {
	if (fd != -1) {
		return -1;
	}

	fd = ::open(config.name, O_RDWR);
	if (fd < 0) {
		return -1;
	}

	if (setBaudrate(config.baudrate) == -1) {
		close();

		return -1;
	}

	return 0;
}

int Serial::close() {
	if (fd == -1) {
		return -1;
	}

	return ::close(fd);
}

int Serial::read(uint8_t buffer[], uint32_t bufferSize) {
	return read(buffer, bufferSize, -1);
}

int Serial::read(uint8_t buffer[], uint32_t bufferSize, int64_t timeout) {
	if (timeout > 0) {
		fd_set set;
		struct timeval timeoutVal;

		FD_ZERO(&set);
		FD_SET(fd, &set);

		uint64_t t			= timeout * 1000;
		timeoutVal.tv_sec	= t / 1000000;
		timeoutVal.tv_usec	= t % 1000000;

		int rv = select(fd + 1, &set, nullptr, nullptr, &timeoutVal);
		if (rv == -1) {
			return -1;
		} else if (rv == 0) {
			return -1;
		}
	}

	return ::read(fd, buffer, bufferSize);
}

int Serial::write(const uint8_t buffer[], uint32_t bufferSize) {
	return ::write(fd, buffer, bufferSize);
}

int Serial::setBaudrate(uint32_t baudrate) {
	config.baudrate = baudrate;

	uint32_t convertedBaudrate = 0;
	switch (baudrate) {
	case 9600:
		convertedBaudrate = B9600;

		break;

	case 19200:
		convertedBaudrate = B19200;

		break;

	case 38400:
		convertedBaudrate = B38400;

		break;

	case 57600:
		convertedBaudrate = B57600;

		break;

	case 115200:
		convertedBaudrate = B115200;

		break;
	}

	struct termios tty{0};

	if (tcgetattr(fd, &tty) != 0) {
		return -1;
	}

	if (convertedBaudrate != 0) {
		if (cfsetospeed(&tty, convertedBaudrate) == -1) {
			return -1;
		}

		if (cfsetispeed(&tty, convertedBaudrate) == -1) {
			return -1;
		}
	}

	if (tcsetattr(fd, TCSANOW, &tty) != 0) {
		return -1;
	}

	return 0;
}

} /* namespace Aim */
