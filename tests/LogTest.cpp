/*
 * LogTest.cpp
 *
 *  Created on: 28.08.2020
 *      Author: Potapov Sergei
 *       Email: samwanderman@yandex.ru
 */

#include "../src/aim/logger/Log.h"
#include "../src/aim/logger/ConsoleChannel.h"

using namespace Aim;

int main(int ac, char** av) {
	Log::addChannel(new ConsoleChannel());
	Log::info("INFO");
	Log::debug("DEBUG");
	Log::warn("WARN");
	Log::error("ERROR");

	return 0;
}
