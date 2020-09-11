/*
 * NonBlockingQueue.h
 *
 *  Created on: 10.09.2020
 *      Author: Potapov Sergei
 *       Email: samwanderman@yandex.ru
 */

#ifndef SRC_AIM_STRUCT_NONBLOCKINGQUEUE_H_
#define SRC_AIM_STRUCT_NONBLOCKINGQUEUE_H_

#include <atomic>
#include <memory>

namespace Aim {

/**
 * Non-block queue implementation
 */
template<typename T>
class NonBlockingQueue {
private:
	/**
	 * Base node
	 */
	struct Node {
		std::shared_ptr<T>	data;
		Node*				next;

		Node() : next(nullptr) { }

		Node(T const& data_) : data(std::make_shared<T>(data_)), next(nullptr) { }
	};

	std::atomic<Node*>	head;
	std::atomic<Node*>	tail;
	std::atomic<int>	queueSize;

public:
	/**
	 * Constructor
	 */
	NonBlockingQueue() {
		Node* node = new Node();
		head.store(node);
		tail.store(node);
		queueSize.store(0);
	}

	/**
	 * Copy-constructor
	 *
	 * \param[in] other - other
	 */
	NonBlockingQueue(const NonBlockingQueue<T>& other) = delete;

	/**
	 * Move-constructor
	 *
	 * \param[in] other - other
	 */
	NonBlockingQueue(NonBlockingQueue<T>&& other) = delete;

	/**
	 * Destructor
	 */
	virtual ~NonBlockingQueue() { }

	/**
	 * Copy-operator
	 *
	 * \param[in] other - other
	 *
	 * \return this
	 */
	NonBlockingQueue<T>& operator=(const NonBlockingQueue<T>& other) = delete;

	/**
	 * Move-operator
	 *
	 * \param[in] other - other
	 *
	 * \return this
	 */
	NonBlockingQueue<T>& operator=(NonBlockingQueue<T>&& other) = delete;

	/**
	 * Push element to queue
	 *
	 * \param[in] data - data to push
	 */
	void push(T const& data) {
		Node* node = new Node(data);
		node->next = tail.load();

		while (!tail.compare_exchange_weak(node->next, node));
		++queueSize;
	}

	/**
	 * Try to pop element
	 *
	 * \return
	 * 		- smart pointer to object if success
	 * 		- nullptr if error
	 */
	std::shared_ptr<T> tryPop() {
		Node* oldHead = head.load();
		if (!oldHead->next) {
			return nullptr;
		}

		while (!head.compare_exchange_weak(oldHead, oldHead->next));
		std::shared_ptr<T> data = oldHead->data;
		delete oldHead;
		--queueSize;

		return data;
	}

	/**
	 * Get queue size
	 *
	 * \return queue size
	 */
	int size() {
		return queueSize.load();
	}
};

} /* namespace Aim */

#endif /* SRC_AIM_STRUCT_NONBLOCKINGQUEUE_H_ */
