/*
 * Log.h
 *
 *  Created on: 28.08.2020
 *      Author: Potapov Sergei
 *       Email: samwanderman@yandex.ru
 */

#ifndef SRC_AIM_LOGGER_LOG_H_
#define SRC_AIM_LOGGER_LOG_H_

#include <cstdio>
#include <cstdarg>
#include <string>

namespace Aim {

/**
 * Logger class
 */
class Log {
public:
	enum struct Level {
		Error = 1,
		Debug,
		Warn,
		Info
	};

	/**
	 * Log info message
	 */
	template<typename... Args>
	static void info(const char* format, Args... args) {
		print(Level::Info, format, args...);
	}

	/**
	 * Log debug message
	 */
	template<typename... Args>
	static void debug(const char* format, Args... args) {
		print(Level::Debug, format, args...);
	}

	/**
	 * Log warn message
	 */
	template<typename... Args>
	static void warn(const char* format, Args... args) {
		print(Level::Warn, format, args...);
	}

	/**
	 * Log error message
	 */
	template<typename... Args>
	static void error(const char* format, Args... args) {
		print(Level::Error, format, args...);
	}

private:
	/**
	 * Log error message
	 */
	template<typename... Args>
	static void print(Level level, const char* format, Args... args) {
		std::string formatWithEndLine = std::string(format) + "\r\n";

		// setup colors
	#ifdef _WIN32
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		switch (level) {
		case Level::Info: {
			SetConsoleTextAttribute(hConsole, 2);
		} break;

		case Level::Debug: {
			SetConsoleTextAttribute(hConsole, 8);
		} break;

		case Level::Warn: {
			SetConsoleTextAttribute(hConsole, 6);
		} break;

		case Level::Error: {
			SetConsoleTextAttribute(hConsole, 4);
		} break;

		default: {
			SetConsoleTextAttribute(hConsole, 7);
		} break;
		}
	#else
		switch (level) {
		case Level::Info: {
			fprintf(stdout, "\x1b[32m");
		} break;

		case Level::Debug: {
			fprintf(stdout, "\x1b[30;1m");
		} break;

		case Level::Warn: {
			fprintf(stdout, "\x1b[33m");
		} break;

		case Level::Error: {
			fprintf(stdout, "\x1b[31m");
		} break;

		default: {
			fprintf(stdout, "\x1b[32m");
		} break;
		}
	#endif

		printInner(formatWithEndLine.c_str(), args...);

	#ifndef _WIN32
		fprintf(stdout, "\x1b[0m");
	#endif
	}

	/**
	 * Print inner
	 *
	 * \param[in] fd		- file descriptor
	 * \param[in] format	- format string
	 * \param[in] ...args	- arguments
	 */
	static void printInner(const char* format, ...) {
		va_list args;
		va_start(args, format);
		vfprintf(stdout, format, args);
		va_end(args);
	}
};

} /* namespace Aim */

#endif /* SRC_AIM_LOGGER_LOG_H_ */
