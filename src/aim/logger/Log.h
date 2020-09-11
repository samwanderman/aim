/*
 * Log.h
 *
 *  Created on: 11.09.2020
 *      Author: Potapov Sergei
 *       Email: samwanderman@yandex.ru
 */

#ifndef SRC_AIM_LOGGER_LOG_H_
#define SRC_AIM_LOGGER_LOG_H_

#include "Logger.h"

namespace Aim {

class Log {
public:
	/**
	 * Add channel
	 *
	 * \param[in] channel - log channel
	 */
	static void addChannel(IChannel* channel) {
		getLogger().addChannel(channel);
	}

	/**
	 * Log info message
	 */
	template<typename... Args>
	static void info(const char* format, Args... args) {
		getLogger().info(format, args...);
	}

	/**
	 * Log debug message
	 */
	template<typename... Args>
	static void debug(const char* format, Args... args) {
		getLogger().debug(format, args...);
	}

	/**
	 * Log warn message
	 */
	template<typename... Args>
	static void warn(const char* format, Args... args) {
		getLogger().warn(format, args...);
	}

	/**
	 * Log error message
	 */
	template<typename... Args>
	static void error(const char* format, Args... args) {
		getLogger().error(format, args...);
	}

private:
	static Logger& getLogger() {
		static Logger logger;
		return logger;
	}
};

} /* namespace Aim */

#endif /* SRC_AIM_LOGGER_LOG_H_ */
