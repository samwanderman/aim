/*
 * IChannel.h
 *
 *  Created on: 11.09.2020
 *      Author: Potapov Sergei
 *       Email: samwanderman@yandex.ru
 */

#ifndef SRC_AIM_LOGGER_ICHANNEL_H_
#define SRC_AIM_LOGGER_ICHANNEL_H_

#include <cstdio>

#include "LogLevel.h"

namespace Aim {

class IChannel {
public:
	/**
	 * Destructor
	 */
	virtual ~IChannel() { }

	/**
	 * Log message
	 *
	 * \param[in] level		- log level
	 * \param[in] format	- format string
	 * \param[in] args		- arguments
	 */
	virtual void log(LogLevel level, const char* format, va_list args) { };
};

} /* namespace Aim */

#endif /* SRC_AIM_LOGGER_ICHANNEL_H_ */
