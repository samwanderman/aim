/*
 * LockFreeStack.h
 *
 *  Created on: 13.10.2020
 *      Author: Potapov Sergei
 *       Email: samwanderman@yandex.ru
 */

#ifndef SRC_AIM_STRUCT_LOCKFREESTACK_H_
#define SRC_AIM_STRUCT_LOCKFREESTACK_H_

#include <memory>
#include <atomic>

namespace Aim {

/**
 * Lock free stack implementation
 */
template <typename T>
class LockFreeStack {
private:
//	struct Node;
//
//	/**
//	 * Counted Node
//	 */
//	struct CountedNode {
//		Node		node;
//		int16_t		externCounter = 0;
//	};

	/**
	 * Node struct
	 */
	struct Node {
		std::shared_ptr<T>	data;
		std::atomic<Node*>	next;
	};

	std::atomic<Node*> head;

public:
	/**
	 * Push new element
	 *
	 * \param[in] data - data to add
	 */
	void push(T const& data) {
		Node* oldHead = head.load();

		Node* node = new Node();
		node->data		= std::make_shared<T>(data);
		node->next		= oldHead;

		while (!head.compare_exchange_weak(oldHead, node));
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

		std::shared_ptr<T> res;
		res.swap(oldHead->data);

		delete oldHead;

		return res;
	}
};

} /* namespace Aim */

#endif /* SRC_AIM_STRUCT_LOCKFREESTACK_H_ */
