/*
 * LockFreeStack.h
 *
 *  Created on: 13.10.2020
 *      Author: Potapov Sergei
 *       Email: samwanderman@yandex.ru
 */

#ifndef SRC_AIM_STRUCT_LOCKFREESTACK_H_
#define SRC_AIM_STRUCT_LOCKFREESTACK_H_

#include <cstdint>
#include <atomic>
#include <memory>

namespace Aim {

/**
 * Lock free stack implementation
 */
template <typename T>
class LockFreeStack {
private:
	/**
	 * Node struct
	 */
	struct Node {
		T		data;
		Node*	next = nullptr;

		Node(T const& data_) : data(data_), next(nullptr) { }
	};

	std::atomic<Node*>		head = nullptr;
	std::atomic<uint32_t>	size = 0;

public:
	/**
	 * Push new element
	 *
	 * \param[in] data - data to add
	 */
	void push(T const& data) {
		Node* node = new Node(data);

		node->next = head.load();

		while (!head.compare_exchange_weak(node->next, node));
		++size;
	}

	/**
	 * Pop element
	 *
	 * \return
	 * 		- nullptr if no data if error
	 * 		- ptr to data if success
	 */
	std::shared_ptr<T> pop() {
		Node* oldHead = head.load();
		if (oldHead == nullptr) {
			return nullptr;
		}

		while (!head.compare_exchange_weak(oldHead, oldHead->next));
		--size;

		std::shared_ptr<T> data = std::make_shared<T>(std::move(oldHead->data));

		delete oldHead;

		return data;
	}

	/**
	 * Get stack size
	 *
	 * \return size
	 */
	uint32_t getSize() {
		return size;
	}
};

} /* namespace Aim */

#endif /* SRC_AIM_STRUCT_LOCKFREESTACK_H_ */
