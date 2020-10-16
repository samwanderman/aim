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
	assert (*res == 42);

	res = stack.pop();
	assert (res == nullptr);

	std::cout << "success\r\n";
}

int main() {
	test01();

	return 0;
}
