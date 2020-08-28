/*
 * Serial.cpp
 *
 *  Created on: 17.08.2020
 *      Author: Potapov Sergei
 *       Email: samwanderman@yandex.ru
 */

#include "Serial.h"

#ifdef _WIN32
#define READ_MIN_TIMEOUT 20
#else
#include <sys/select.h>
#include <unistd.h>
#include <termios.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdio>
#include <algorithm>

namespace Aim {

Serial::Serial(Config config) {
	this->config	= config;

#ifdef _WIN32
	this->fd		= nullptr;
#else
	this->fd		= -1;
#endif
}

Serial::Serial(Serial&& other) {
	this->config	= other.config;
	this->fd		= other.fd;

#ifdef _WIN32
	this->fd		= nullptr;
#else
	this->fd		= -1;
#endif
}

Serial::~Serial() {}

Serial& Serial::operator=(Serial&& other) {
	this->config	= other.config;
	this->fd		= other.fd;

#ifdef _WIN32
	this->fd		= nullptr;
#else
	this->fd		= -1;
#endif

	return *this;
}

int Serial::open() {
#ifdef _WIN32
	if (fd != nullptr) {
		return -1;
	}

	fd = CreateFile(config.name, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, config.nonBlock ? FILE_FLAG_OVERLAPPED : 0, 0);
	if (fd == INVALID_HANDLE_VALUE) {
		return -1;
	}
#else
	if (fd != -1) {
		return -1;
	}

	fd = ::open(config.name, O_RDWR);
	if (fd < 0) {
		return -1;
	}

#endif
	if (setParams() == -1) {
		return -1;
	}

	if (setBaudrate(config.baudrate) == -1) {
		close();

		return -1;
	}

	return 0;
}

int Serial::close() {
#ifdef _WIN32
	if (fd == nullptr) {
		return -1;
	}

	int res = CloseHandle(fd) ? 0 : -1;
	fd = nullptr;

	return res;
#else
	if (fd == -1) {
		return -1;
	}

	return ::close(fd);
#endif
}

int Serial::read(uint8_t buffer[], uint32_t bufferSize) {
	return read(buffer, bufferSize, -1);
}

int Serial::read(uint8_t buffer[], uint32_t bufferSize, int64_t timeout) {
	int res = -1;

#ifdef _WIN32
	if (config.nonBlock) {
		OVERLAPPED ov = { 0 };
		ov.hEvent = CreateEvent(nullptr, true, false, nullptr);
		if (ov.hEvent == nullptr) {
			return -1;
		}

		DWORD readBytes = -1;
		bool result = false;

		if (!ReadFile(fd, reinterpret_cast<LPVOID>(buffer), static_cast<DWORD>(bufferSize), &readBytes, &ov)) {
			DWORD lastError = GetLastError();
			switch (lastError) {
			case ERROR_IO_PENDING:
				if (WaitForSingleObject(ov.hEvent, static_cast<DWORD>(timeout)) == WAIT_OBJECT_0) {
					result = GetOverlappedResult(fd, &ov, &readBytes, false);
				}

				break;

			case 0:
				result = true;
			}
		} else {
			result = true;
		}

		CloseHandle(ov.hEvent);

		if (!result) {
			return -1;
		}

		res = static_cast<int>(readBytes);
	} else {
		if (timeout != config.timeout) {
			setTimeout(timeout);
		}

		DWORD readBytes = -1;

		bool result = ReadFile(fd, reinterpret_cast<LPVOID>(buffer), static_cast<DWORD>(bufferSize), &readBytes, nullptr);
		if (timeout != config.timeout) {
			setTimeout(config.timeout);
		}

		if (!result) {
			return -1;
		}

		res = static_cast<int>(readBytes);
	}
#else
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

	res = ::read(fd, buffer, bufferSize);
#endif

	return res;
}

int Serial::write(const uint8_t buffer[], uint32_t bufferSize) {
	int res = -1;

#ifdef _WIN32
	if (config.nonBlock) {
		bool result = false;

		OVERLAPPED ov = { 0 };
		ov.hEvent = CreateEvent(nullptr, true, false, nullptr);
		if (ov.hEvent == nullptr) {
			return -1;
		}

		DWORD bytesWritten = -1;
		if (!WriteFile(fd, reinterpret_cast<LPVOID>(const_cast<uint8_t*>(buffer)), static_cast<DWORD>(bufferSize), &bytesWritten, &ov)) {
			if (GetLastError() == ERROR_IO_PENDING) {
				if (WaitForSingleObject(ov.hEvent, INFINITE) == WAIT_OBJECT_0) {
					result = GetOverlappedResult(fd, &ov, &bytesWritten, false);
				}
			}
		}

		CloseHandle(ov.hEvent);

		if (result) {
			res = static_cast<int>(bytesWritten);
		} else {
			return -1;
		}
	} else {
		DWORD bytesWritten = -1;

		if (!WriteFile(fd, reinterpret_cast<LPVOID>(const_cast<uint8_t*>(buffer)), static_cast<DWORD>(bufferSize), &bytesWritten, nullptr)) {
			return -1;
		}

		res = static_cast<int>(bytesWritten);
	}
#else
	return ::write(fd, buffer, bufferSize);
#endif

	return res;
}

int Serial::setBaudrate(uint32_t baudrate) {
	config.baudrate = baudrate;
#ifdef _WIN32
	DWORD convertedBaudrate = 0;
	switch (baudrate) {
	case 9600:
		convertedBaudrate = CBR_9600;

		break;

	case 19200:
		convertedBaudrate = CBR_19200;

		break;

	case 38400:
		convertedBaudrate = CBR_38400;

		break;

	case 57600:
		convertedBaudrate = CBR_57600;

		break;

	case 115200:
		convertedBaudrate = CBR_115200;

		break;
	}

	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

	if (!GetCommState(fd, &dcbSerialParams)) {
		return -1;
	}

	dcbSerialParams.BaudRate = convertedBaudrate;

	if(!SetCommState(fd, &dcbSerialParams)) {
		return -1;
	}

#else
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
#endif

	return 0;
}

int Serial::setParams() {
	if (!config.nonBlock) {
#ifdef _WIN32

		COMMTIMEOUTS timeouts;
		if (!GetCommTimeouts(fd, &timeouts)) {
			return -1;
		}
//
//		printf("ReadIntervalTimeout: %i\r\n"
//				"ReadTotalTimeoutConstant: %i\r\n"
//				"ReadTotalTimeoutMutlitplier: %i\r\n"
//				"WriteTotalTimeoutConstant: %i\r\n"
//				"WriteTotalTimeoutMultiplier: %i\r\n", timeouts.ReadIntervalTimeout, timeouts.ReadTotalTimeoutConstant, timeouts.ReadTotalTimeoutMultiplier, timeouts.WriteTotalTimeoutConstant, timeouts.WriteTotalTimeoutMultiplier);

		timeouts.ReadIntervalTimeout = READ_MIN_TIMEOUT;

		if (!SetCommTimeouts(fd, &timeouts)) {
			return -1;
		}
#endif
	} else {
		setTimeout(config.timeout);
	}

	return 0;
}

int Serial::setTimeout(int64_t timeout) {
	if (timeout <= 0) {
		return -1;
	}

#ifdef _WIN32
	COMMTIMEOUTS commTimeout;

	if(!GetCommTimeouts(fd, &commTimeout)) {
		return -1;
	}

	if (timeout > 0) {
	    commTimeout.ReadIntervalTimeout			= -1;
	    commTimeout.ReadTotalTimeoutMultiplier	= 0;
	    commTimeout.ReadTotalTimeoutConstant	= static_cast<DWORD>(timeout);
	    commTimeout.WriteTotalTimeoutMultiplier	= 0;
	    commTimeout.WriteTotalTimeoutConstant	= static_cast<DWORD>(timeout);
	}

	if(!SetCommTimeouts(fd, &commTimeout)) {
		return -1;
	}
#else
	struct termios tty{0};

	if (tcgetattr(fd, &tty) != 0) {
		return -1;
	}

	tty.c_cc[VMIN] = 0;
	tty.c_cc[VTIME] = std::min(0, static_cast<int>(config.timeout / 100));

	if (tcsetattr(fd, TCSANOW, &tty) != 0) {
		return -1;
	}
#endif

	return 0;
}

} /* namespace Aim */
