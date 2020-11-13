/*
 * LockFreeStackTest.cpp
 *
 *  Created on: 13.10.2020
 *      Author: Potapov Sergei
 *       Email: samwanderman@yandex.ru
 */

#include "../src/aim/struct/LockFreeStack.h"

#include <iostream>
#include <cassert>
#include <thread>
#include <future>
#include <chrono>
#include <condition_variable>

using namespace std::chrono_literals;

void test01() {
	std::cout << "Test01: ";

	Aim::LockFreeStack<int> stack;

	auto res = stack.pop();
	assert (res == nullptr);

	stack.push(2);
	stack.push(42);

	res = stack.pop();
	assert (res != nullptr);
	assert (*res == 42);

	res = stack.pop();
	assert (res != nullptr);
	assert (*res == 2);

	res = stack.pop();
	assert (res == nullptr);

	std::cout << "success\r\n";
}

void test02() {
	std::cout << "Test02: ";

	Aim::LockFreeStack<int> stack;

	std::mutex m;
	std::condition_variable cond;

	std::thread th1([&]() {
		std::unique_lock<decltype(m)> lock(m);
		cond.wait(lock);
		stack.push(42);
	});

	std::thread th2([&]() {
		std::unique_lock<decltype(m)> lock(m);
		cond.wait(lock);
		stack.push(41);
	});

	cond.notify_all();

	std::this_thread::sleep_for(200ms);

	auto res = stack.pop();
	assert (res != nullptr);
	res = stack.pop();
	assert (res != nullptr);
	res = stack.pop();
	assert (res == nullptr);


	th1.join();
	th2.join();

	std::cout << "success\r\n";
}

int main() {
	test01();
	test02();

	return 0;
}
