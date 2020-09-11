/*
 * NonBlockingQueueTest.cpp
 *
 *  Created on: 10.09.2020
 *      Author: Potapov Sergei
 *       Email: samwanderman@yandex.ru
 */

#include <cassert>
#include "../src/aim/struct/NonBlockingQueue.h"

using namespace Aim;

void test01() {
	printf("test01()\r\n");

	NonBlockingQueue<int> queue;

	std::shared_ptr<int> data;

	assert((data = queue.tryPop()) == nullptr);

	const int val = 42;

	queue.push(val);

	printf("Queue size: %i\r\n", queue.size());

	data = queue.tryPop();
	if (data != nullptr) {
		printf("1\r\n");
	} else {
		printf("2\r\n");
	}

//	assert((data = queue.tryPop()) != nullptr);
//	assert(*data == 42);
//	assert((data = queue.tryPop()) == nullptr);
}

int main(int ac, char** av) {
	test01();

	return 0;
}
