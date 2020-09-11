/*
 * LogTest.cpp
 *
 *  Created on: 28.08.2020
 *      Author: Potapov Sergei
 *       Email: samwanderman@yandex.ru
 */

#include "../src/aim/logger/Log.h"
#include "../src/aim/logger/ConsoleChannel.h"
#include "../src/aim/logger/FileChannel.h"

using namespace Aim;

int main(int ac, char** av) {
	Log::addChannel(new ConsoleChannel());
	FileChannel::Config config;
	config.path			= "log";
	config.fileMaxSize	= 32;
	Log::addChannel(new FileChannel(config));

	Log::info("INFO");
	Log::debug("DEBUG");
	Log::warn("WARN");
	Log::error("ERROR");

	return 0;
}
