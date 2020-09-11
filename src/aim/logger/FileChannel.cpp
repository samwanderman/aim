/*
 * FileChannel.cpp
 *
 *  Created on: 11.09.2020
 *      Author: Potapov Sergei
 *       Email: samwanderman@yandex.ru
 */

#include "FileChannel.h"

namespace Aim {

FileChannel::FileChannel(Config config) {
	this->config = config;
	fd = fopen(config.path, "a");
}

FileChannel::~FileChannel() {
	if (fd != nullptr) {
		fclose(fd);
	}
}

void FileChannel::log(LogLevel level, const char* format, va_list args) {
	if (fd != nullptr) {
		std::string formatWithEndLine = std::string(format) + "\r\n";
		vprintf((const char*) formatWithEndLine.c_str(), args);
//		vfprintf(fd, formatWithEndLine.c_str(), args);
//
//		if (config.fileMaxSize > 0) {
//			if (fseek(fd, 0, SEEK_END) == 0) {
//				uint32_t size = ftell(fd);
//				if (size > config.fileMaxSize) {
//					int d = fileno(fd);
//					ftruncate(d, config.fileMaxSize);
//				}
//			}
//		}
	}
}

} /* namespace Aim */
