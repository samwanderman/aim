/*
 * ConsoleChannel.cpp
 *
 *  Created on: 11.09.2020
 *      Author: Potapov Sergei
 *       Email: samwanderman@yandex.ru
 */

#include "ConsoleChannel.h"

#include <cstdio>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

namespace Aim {

/**
 * Constructor
 */
ConsoleChannel::ConsoleChannel() { }

/**
 * Destructor
 */
ConsoleChannel::~ConsoleChannel() { }

/**
 * Log error message
 */
void ConsoleChannel::log(LogLevel level, const char* format, va_list args) {
	std::string formatWithEndLine = std::string(format) + "\r\n";

	// setup colors
#ifdef _WIN32
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (level) {
	case LogLevel::Info: {
		SetConsoleTextAttribute(hConsole, 2);
	} break;

	case LogLevel::Debug: {
		SetConsoleTextAttribute(hConsole, 8);
	} break;

	case LogLevel::Warn: {
		SetConsoleTextAttribute(hConsole, 6);
	} break;

	case LogLevel::Error: {
		SetConsoleTextAttribute(hConsole, 4);
	} break;

	default: {
		SetConsoleTextAttribute(hConsole, 7);
	} break;
	}
#else
	switch (level) {
	case LogLevel::Info: {
		fprintf(stdout, "\x1b[32m");
	} break;

	case LogLevel::Debug: {
		fprintf(stdout, "\x1b[30;1m");
	} break;

	case LogLevel::Warn: {
		fprintf(stdout, "\x1b[33m");
	} break;

	case LogLevel::Error: {
		fprintf(stdout, "\x1b[31m");
	} break;

	default: {
		fprintf(stdout, "\x1b[32m");
	} break;
	}
#endif

	vfprintf(stdout, formatWithEndLine.c_str(), args);

#ifndef _WIN32
	fprintf(stdout, "\x1b[0m");
#endif
}

} /* namespace Aim */
