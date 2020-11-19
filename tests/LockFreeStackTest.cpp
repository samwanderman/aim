/*
 * LockFreeStackTest.cpp
 *
 *  Created on: 13.10.2020
 *      Author: Potapov Sergei
 *       Email: samwanderman@yandex.ru
 */

#include "../src/aim/struct/LockFreeStack.h"
#include "../src/aim/logger/Log.h"

#include <cassert>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

using namespace std::chrono_literals;

void test01() {
	std::cout << "Test01: ";

	Aim::LockFreeStack<int> stack;

	auto res = stack.pop();
	assert (res == nullptr);

	stack.push(2);
	stack.push(42);

//	std::cout << "Size: " <<  stack.getSize() << "\r\n";

	res = stack.pop();

//	std::cout << "Size: " <<  stack.getSize() << "\r\n";
	assert (res != nullptr);
	assert (*res == 42);

	res = stack.pop();

//	std::cout << "Size: " <<  stack.getSize() << "\r\n";
	assert (res != nullptr);
	assert (*res == 2);

	res = stack.pop();

//	std::cout << "Size: " <<  stack.getSize() << "\r\n";
	assert (res == nullptr);

	std::cout << "success\r\n";
}

void test02() {
	std::cout << "Test02: ";

	Aim::LockFreeStack<int> stack;

	std::atomic<bool> start;

	std::thread th1([&]() {
		while (!start.load())
			std::this_thread::yield();

		for (int i = 0; i < 100; i++) {
			stack.push(i);
		}
	});

	std::thread th2([&]() {
		while (!start.load())
			std::this_thread::yield();

		for (int i = 0; i < 100; i++) {
			stack.push(100 + i);
		}
	});

	start.store(true);

	std::this_thread::sleep_for(200ms);

	assert (stack.getSize() == 200);
//	std::cout << "Size: " <<  stack.getSize() << "\r\n";

	th1.join();
	th2.join();

	start = false;

	std::thread th3([&]() {
		while (!start.load())
			std::this_thread::yield();

		while (stack.pop()) {
//			std::cout << "0";
		}
	});

	std::thread th4([&]() {
		while (!start.load())
			std::this_thread::yield();

		while (stack.pop()) {
//			std::cout << "1";
		}
	});

	start.store(true);

	std::this_thread::sleep_for(200ms);

	assert (stack.getSize() == 0);

//	std::cout << "\r\nSize: " <<  stack.getSize() << "\r\n";

	th3.join();
	th4.join();

	std::cout << "success\r\n";
}

int main() {
	test01();
	test02();

	return 0;
}
