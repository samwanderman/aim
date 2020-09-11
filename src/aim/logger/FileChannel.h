/*
 * FileChannel.h
 *
 *  Created on: 11.09.2020
 *      Author: Potapov Sergei
 *		 Email: samwanderman@yandex.ru
 */

#ifndef SRC_AIM_LOGGER_FILECHANNEL_H_
#define SRC_AIM_LOGGER_FILECHANNEL_H_

#include <cstdint>
#include <cstdio>
#include <string>
#include "IChannel.h"

namespace Aim {

/**
 * File channel
 */
class FileChannel : public IChannel {
public:
	/**
	 * Channel config
	 */
	struct Config {
		const char* path		= "";
		uint32_t	fileMaxSize = 0;
	};

	/**
	 * Constructor
	 *
	 * \param[in] config - channel config
	 */
	FileChannel(Config config);

	/**
	 * Destructor
	 */
	virtual ~FileChannel();

	/**
	 * Log message
	 *
	 * \param[in] level		- log level
	 * \param[in] format	- format string
	 * \param[in] args		- arguments
	 */
	void log(LogLevel level, const char* format, va_list args);

private:
	Config	config;
	FILE*	fd		= nullptr;
};

} /* namespace Aim */

#endif /* SRC_AIM_LOGGER_FILECHANNEL_H_ */
