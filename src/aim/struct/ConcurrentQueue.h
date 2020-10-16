/*
 * ConcurrentQueue.h
 *
 *  Created on: 18.08.2020
 *      Author: Potapov Sergei
 *       Email: samwanderman@yandex.ru
 */

#ifndef SRC_AIM_STRUCT_CONCURRENTQUEUE_H_
#define SRC_AIM_STRUCT_CONCURRENTQUEUE_H_

#include <mutex>
#include <queue>
#include <memory>

namespace Aim {

/**
 * Concurrent queue template
 */
template<typename T>
class ConcurrentQueue {
private:
	/**
	 * Base node
	 */
	struct Node {
		std::shared_ptr<T> data;
		std::unique_ptr<Node> next;

		Node() {}

		Node(T const& data_) : data(data_) { }
	};

	/**
	 * Queue head control
	 */
	std::unique_ptr<Node> head;
	std::mutex headMutex;

	/**
	 * Queue tail control
	 */
	Node* tail;
	std::mutex tailMutex;

	/**
	 * Queue size
	 */
	int queueSize = 0;
	std::mutex queueSizeMutex;

	/**
	 * Get tail pointer
	 *
	 * \return tail
	 */
	Node* getTail() {
		std::lock_guard lock(tailMutex);
		return tail;
	}

	/**
	 * Increment queue size
	 */
	void incQueueSize() {
		std::lock_guard lock(queueSizeMutex);
		++queueSize;
	}

	/**
	 * Decrement queue size
	 */
	void decQueueSize() {
		std::lock_guard lock(queueSizeMutex);
		--queueSize;
	}

public:
	/**
	 * Constructor
	 */
	ConcurrentQueue() : head(new Node), tail(head.get()), queueSize(0) { }

	/**
	 * Copy-constructor
	 *
	 * \param[in] other - other
	 */
	ConcurrentQueue(const ConcurrentQueue<T>& other) = delete;

	/**
	 * Move-constructor
	 *
	 * \param[in] other - other
	 */
	ConcurrentQueue(ConcurrentQueue<T>&& other) = delete;

	/**
	 * Destructor
	 */
	virtual ~ConcurrentQueue() { }

	/**
	 * Copy-operator
	 *
	 * \param[in] other - other
	 *
	 * \return this
	 */
	ConcurrentQueue<T>& operator=(const ConcurrentQueue<T>& other) = delete;

	/**
	 * Move-operator
	 *
	 * \param[in] other - other
	 *
	 * \return this
	 */
	ConcurrentQueue<T>& operator=(ConcurrentQueue<T>&& other) = delete;

	/**
	 * Push element into queue
	 *
	 * \param[in] item - item to push
	 */
	void push(T const& item) {
		std::shared_ptr<T> data = std::make_shared<T>(std::move(item));
		std::unique_ptr<Node> newNode(new Node());

		std::lock_guard lock(tailMutex);
		tail->data = data;
		tail->next = std::move(newNode);
		tail = tail->next.get();
		incQueueSize();
	}

	/**
	 * Pop element
	 *
	 * \return
	 * 		- smart pointer to value if success
	 * 		- nullptr if error
	 */
	std::shared_ptr<T> pop() {
		std::lock_guard lock(headMutex);
		if (head.get() == getTail()) {
			return nullptr;
		}

		std::shared_ptr<T> data = head->data;
		head = std::move(head->next);
		decQueueSize();

		return data;
	}

	/**
	 * Get queue size
	 *
	 * \return queue size
	 */
	int size() {
		std::lock_guard lock(queueSizeMutex);

		return queueSize;
	}
};

} /* namespace Aim */

#endif /* SRC_AIM_STRUCT_CONCURRENTQUEUE_H_ */
