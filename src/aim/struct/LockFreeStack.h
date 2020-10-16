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
		std::shared_ptr<T>	data;
		Node* 				next;
	};

	Node* head = nullptr;

public:
	/**
	 * Push new element
	 *
	 * \param[in] data - data to add
	 */
	void push(T const& data) {
		Node* node = new Node();
		node->data = std::make_shared<T>(data);
		node->next = head;
		head = node;
	}

	/**
	 * Pop element
	 *
	 * \return
	 * 		- nullptr if no data if error
	 * 		- ptr to data if success
	 */
	std::shared_ptr<T> pop() {
		Node* oldHead = head;
		if (oldHead == nullptr) {
			return nullptr;
		}

		head = head->next;

		std::shared_ptr<T> res;
		res.swap(oldHead->data);

		delete oldHead;

		return res;
	}
};

} /* namespace Aim */

#endif /* SRC_AIM_STRUCT_LOCKFREESTACK_H_ */
