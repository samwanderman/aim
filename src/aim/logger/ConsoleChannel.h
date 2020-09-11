/*
 * ConsoleChannel.h
 *
 *  Created on: 11.09.2020
 *      Author: Potapov Sergei
 *       Email: samwanderman@yandex.ru
 */

#ifndef SRC_AIM_LOGGER_CONSOLECHANNEL_H_
#define SRC_AIM_LOGGER_CONSOLECHANNEL_H_

#include <cstdarg>
#include "IChannel.h"
#include "LogLevel.h"

namespace Aim {

/**
 * Console channel
 */
class ConsoleChannel : public IChannel {
public:
	/**
	 * Constructor
	 */
	ConsoleChannel();

	/**
	 * Destructor
	 */
	virtual ~ConsoleChannel();

	/**
	 * Log error message
	 */
	void log(LogLevel level, const char* format, va_list args);
};

} /* namespace Aim */

#endif /* SRC_AIM_LOGGER_CONSOLECHANNEL_H_ */
