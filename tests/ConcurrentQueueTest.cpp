/*
 * ConcurrentQueueTest.cpp
 *
 *  Created on: 18.08.2020
 *      Author: Potapov Sergei
 *       Email: samwanderman@yandex.ru
 */

#include "../src/aim/struct/ConcurrentQueue.h"

#include <cstdio>
#include <cassert>

using namespace Aim;

void test01() {
	printf("Test01 ");
	ConcurrentQueue<int> queue;

	const int checkNumber = 42;

	assert(queue.size() == 0);

	queue.push(checkNumber);
	queue.push(checkNumber);

	assert(queue.size() == 2);

	int res1;

	queue.pop(res1);

	assert(res1 == checkNumber);

	std::shared_ptr<decltype(checkNumber)> res2 = queue.pop();
	assert(res2 != nullptr);
	assert(*res2 == checkNumber);

	printf("complete\r\n");
}

int main(int ac, char** av) {
	test01();

	return 0;
}
