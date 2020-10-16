/*
 * LockFreeQueue.h
 *
 *  Created on: 10.09.2020
 *      Author: Potapov Sergei
 *       Email: samwanderman@yandex.ru
 */

#ifndef SRC_AIM_STRUCT_LOCKFREEQUEUE_H_
#define SRC_AIM_STRUCT_LOCKFREEQUEUE_H_

#include <cstdint>
#include <atomic>
#include <memory>

namespace Aim {

/**
 * Non-block queue implementation
 */
template<typename T>
class LockFreeQueue {
private:
	struct Node {
		std::unique_ptr<T>		data;
		std::shared_ptr<Node>	next;
	};

	std::shared_ptr<Node> head;
	std::shared_ptr<Node> tail;

public:
	LockFreeQueue() : head(new Node), tail(head.get()) { }

	virtual ~LockFreeQueue() {
//		while (pop());
	}

	void push(T data) {
//		printf("%p %p", head, tail);
//		std::shared_ptr<Node> oldTail = tail;
//		oldTail->next = std::make_shared<Node>();
//		oldTail->data = std::make_unique<T>(std::move(data));
//		printf("<%X>", *(oldTail->data));
//		tail = oldTail->next;
//		printf("%p %p", head, tail);
	}

	std::unique_ptr<T> pop() {
//		if (head == tail) {
//			return std::unique_ptr<T>();
//		}
//
//		std::shared_ptr<Node> oldHead = head;
//		printf("<%X>", *(oldHead->data));
//		head = oldHead->next;
//
//		return std::move(oldHead->data);

//		printf("%X %X", head, tail);
//
//		auto begin = head;
//		printf("(%i)", begin == nullptr);
//		printf("\r\n-----\r\n");
//		while (begin->next != nullptr) {
//			printf("%X\r\n", *(begin->data));
//			begin = begin->next;
//		}
//		printf("-----\r\n");
//
		return nullptr;
	}
};

} /* namespace Aim */

#endif /* SRC_AIM_STRUCT_LOCKFREEQUEUE_H_ */
