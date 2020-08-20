/*
 * Serial.h
 *
 *  Created on: 17.08.2020
 *      Author: Potapov Sergei
 *       Email: samwanderman@yandex.ru
 */

#ifndef SRC_AIM_CONNECTION_SERIAL_H_
#define SRC_AIM_CONNECTION_SERIAL_H_

#include <cstdint>

namespace Aim {

/**
 * Serial port class
 */
class Serial {
public:
	/**
	 * Configuration struct
	 */
	struct Config {
		const char*	name		= nullptr;
		uint32_t	baudrate	= 0;
		bool		nonBlock	= false;
		int64_t		timeout		= -1;
	};

	/**
	 * Constructor
	 *
	 * \param[in] config - configuration
	 */
	Serial(Config config);

	/**
	 * Forbid copy-constructor
	 */
	Serial(const Serial& other) = delete;

	/**
	 * Move-constructor
	 *
	 * \param[in] other - other
	 */
	Serial(Serial&& other);

	/**
	 * Destructor
	 */
	virtual ~Serial();

	/**
	 * Forbid copying
	 */
	Serial& operator=(const Serial& other) = delete;

	/**
	 * Move operator
	 *
	 * \param[in] other - other
	 */
	Serial& operator=(Serial&& other);

	/**
	 * Open port
	 *
	 * \return
	 * 		- 0 if success
	 * 		- -1 if error
	 */
	int open();

	/**
	 * Close port
	 *
	 * \return
	 * 		- 0 if success
	 * 		- -1 if error
	 */
	int close();

	/**
	 * Read bufferSize bytes into buffer
	 *
	 * \param[out]	buffer		- pointer to buffer array
	 * \param[in]	bufferSize	- buffer size
	 *
	 * \return
	 * 		- number of read bytes if success
	 * 		- -1 if error
	 */
	int read(uint8_t buffer[], uint32_t bufferSize);

	/**
	 * Read bufferSize bytes into buffer
	 *
	 * \param[out]	buffer		- pointer to buffer array
	 * \param[in]	bufferSize	- buffer size
	 * \param[in]	timeout		- read timeout
	 *
	 * \return
	 * 		- number of read bytes if success
	 * 		- -1 if error
	 */
	int read(uint8_t buffer[], uint32_t bufferSize, int64_t timeout);

	/**
	 * Write bufferSize bytes into buffer
	 *
	 * \param[out]	buffer		- pointer to buffer array
	 * \param[in]	bufferSize	- buffer size
	 *
	 * \return
	 * 		- number of written bytes if success
	 * 		- -1 if error
	 */
	int write(const uint8_t buffer[], uint32_t bufferSize);

	/**
	 * Ser port baudrate
	 *
	 * \param[in] baudrate - baudrate to set
	 *
	 * \return
	 * 		- 0 if success
	 * 		- -1 if error
	 */
	int setBaudrate(uint32_t baudrate);

private:
	Config	config;
	int		fd		= -1;

	/**
	 * Set different params
	 *
	 * \return
	 * 		- 0 if success
	 * 		- -1 if error
	 */
	int setParams();
};

} /* namespace Aim */

#endif /* SRC_AIM_CONNECTION_SERIAL_H_ */
