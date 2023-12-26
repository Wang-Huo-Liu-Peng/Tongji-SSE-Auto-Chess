#pragma once
#ifndef __SAFE__QUEUE__H__
#define __SAFE__QUEUE__H__
#include <mutex>
#include <queue>

//用锁实现安全队列
template <typename T>
class SafeQueue {
private:
	std::queue<T> m_queue;
	std::mutex m_mutex;
public:
	SafeQueue() {

	}

	SafeQueue(SafeQueue& other) {
		//拷贝构造，如果用得到再实现
	}

	~SafeQueue() {

	}


	bool empty() {
		std::unique_lock<std::mutex> lock(m_mutex);
		return m_queue.empty();  //在锁保护下检查是否为空
	}

	int size() {
		std::unique_lock<std::mutex> lock(m_mutex);
		return m_queue.size();  //在锁保护下获取数量
	}

	void enqueue(T& t) {
		std::unique_lock<std::mutex> lock(m_mutex);
		m_queue.push(t);        //在锁保护下插入元素
	}

	bool dequeue(T& t) {
		std::unique_lock<std::mutex> lock(m_mutex);
		//在锁保护下弹出元素
		if (m_queue.empty()) {
			return false;
		}
		t = std::move(m_queue.front());

		m_queue.pop();
		return true;
	}
};
#endif