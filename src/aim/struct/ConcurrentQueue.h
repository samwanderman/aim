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
public:
	/**
	 * Constructor
	 */
	ConcurrentQueue() { }

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
	ConcurrentQueue(ConcurrentQueue<T>&& other) {
		std::lock_guard lock(other.mutex);
		container = other.container;
	}

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
	ConcurrentQueue<T>& operator=(ConcurrentQueue<T>&& other) {
		std::lock_guard lock(other.mutex);
		container = other.container;

		return *this;
	}

	/**
	 * Push element into queue
	 *
	 * \param[in] item - item to push
	 */
	void push(T item) {
		std::lock_guard lock(mutex);
		container.push(item);
	}

	/**
	 * Pop element
	 *
	 * \param[out] item - ref to element
	 *
	 * \return
	 * 		- true if success
	 * 		- false if error
	 */
	bool pop(T& item) {
		std::lock_guard lock(mutex);
		if (container.size() > 0) {
			item = container.front();
			container.pop();

			return true;
		}

		return false;
	}

	/**
	 * Pop element
	 *
	 * \return
	 * 		- smart pointer to value if success
	 * 		- nullptr if error
	 */
	std::shared_ptr<T> pop() {
		std::lock_guard lock(mutex);
		if (container.size() > 0) {
			std::shared_ptr<T> item = std::make_shared<T>(container.front());
			container.pop();

			return item;
		}

		return nullptr;
	}

	/**
	 * Get queue size
	 *
	 * \return size
	 */
	int size() {
		std::lock_guard lock(mutex);

		return container.size();
	}

private:
	std::mutex		mutex;
	std::queue<T>	container;
};

} /* namespace Aim */

#endif /* SRC_AIM_STRUCT_CONCURRENTQUEUE_H_ */
