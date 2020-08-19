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
	 * \return
	 * 		- number of read bytes if success
	 * 		- -1 if error
	 */
	int read(uint8_t buffer[], uint32_t bufferSize);

	/**
	 * Write bufferSize bytes into buffer
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
};

} /* namespace Aim */

#endif /* SRC_AIM_CONNECTION_SERIAL_H_ */
