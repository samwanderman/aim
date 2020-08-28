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
#include <thread>
#include <atomic>

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

void test02() {
	printf("Test02 ");

	ConcurrentQueue<int> queue;

	std::atomic<bool> start;

	start = false;

	std::thread th1([&start, &queue]() {
		while (!start.load()) {}
		queue.push(42);
	});

	std::thread th2([&start, &queue]() {
		while (!start.load()) {}
		queue.push(42);
	});

	start = true;

	th1.join();
	th2.join();

	assert(queue.size() == 2);

	start = false;

	std::thread th3([&start, &queue]() {
		while (!start.load()) {}
		queue.pop();
	});

	std::thread th4([&start, &queue]() {
		while (!start.load()) {}
		queue.pop();
	});

	start = true;

	th3.join();
	th4.join();

	assert(queue.size() == 0);

	printf("complete\r\n");
}

int main(int ac, char** av) {
	test01();
	test02();

	return 0;
}
