/*
 * NonBlockingQueueTest.cpp
 *
 *  Created on: 10.09.2020
 *      Author: Potapov Sergei
 *       Email: samwanderman@yandex.ru
 */

#include <cassert>

#include "../src/aim/struct/LockFreeQueue.h"

using namespace Aim;

void test01() {
	printf("Test01: ");

	LockFreeQueue<int> queue;

//	std::unique_ptr<int> res = queue.pop();
//	assert(res == nullptr);

	int val = 42;
	queue.push(val);

	std::unique_ptr<int> res = queue.pop();
//	assert(res != nullptr);
//	printf("%i", *res);
//	assert(*res == val);

//	res = queue.pop();
//	assert(res == nullptr);

//	res = queue.pop();
//	assert(res == nullptr);

	printf("Success\r\n");
}

int main(int ac, char** av) {
	test01();

	return 0;
}
