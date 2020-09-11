/*
 * Log.h
 *
 *  Created on: 28.08.2020
 *      Author: Potapov Sergei
 *       Email: samwanderman@yandex.ru
 */

#ifndef SRC_AIM_LOGGER_LOGGER_H_
#define SRC_AIM_LOGGER_LOGGER_H_

#include <atomic>
#include <cstdarg>
#include <cstdio>
#include <list>
#include <memory>
#include <string>

#include "IChannel.h"
#include "LogLevel.h"

namespace Aim {

/**
 * Logger class
 */
class Logger {
private:
	std::list<std::shared_ptr<IChannel*>> channels;

	/**
	 * Log error message
	 */
	void print(LogLevel level, const char* format, ...) {
		auto it = channels.begin();
		while (it != channels.end()) {
			std::shared_ptr<IChannel*> p = (*it);
			va_list args;
			va_start(args, format);
			(*p)->log(level, format, args);
			va_end(args);
			it++;
		}
	}

public:
	/**
	 * Add channel
	 *
	 * \param[in] channel - log channel
	 */
	void addChannel(IChannel* channel) {
		std::shared_ptr<IChannel*> ptr = std::make_shared<IChannel*>(std::move(channel));
		channels.push_back(ptr);
	}

	/**
	 * Log info message
	 */
	template<typename... Args>
	void info(const char* format, Args... args) {
		print(LogLevel::Info, format, args...);
	}

	/**
	 * Log debug message
	 */
	template<typename... Args>
	void debug(const char* format, Args... args) {
		print(LogLevel::Debug, format, args...);
	}

	/**
	 * Log warn message
	 */
	template<typename... Args>
	void warn(const char* format, Args... args) {
		print(LogLevel::Warn, format, args...);
	}

	/**
	 * Log error message
	 */
	template<typename... Args>
	void error(const char* format, Args... args) {
		print(LogLevel::Error, format, args...);
	}
};

} /* namespace Aim */

#endif /* SRC_AIM_LOGGER_LOGGER_H_ */
