#include<iostream>
#include<thread>
#include<queue>
#include<mutex>
#include<condition_variable>
#include<vector>
#include<functional>

#define default_thread_num 10

class thread_pool {
public:
	static thread_pool& getInstance() {
		static thread_pool ThreadPool(default_thread_num);
		return ThreadPool;
	}

	template<class F, class... Args>
	void enqueue(F&& f, Args&&... args) {       //通用引用
		std::function<void()>task =
			std::bind(std::forward<F>(f), std::forward<Args>(args...)); //通过完美转发实现通用引用
		std::unique_lock<std::mutex> lock(mtx);
		tasks.emplace(std::move(task));
		condition.notify_one();                //通知来了一个任务
	}

	void set_stop(int status=true) {
		stop = status;
	}
private:
	thread_pool(int numThreads) :stop(false) {
		for (int i = 0; i < numThreads; i++) {
			//push_back是采用拷贝构造加入容器，emplace_back是调用构造函数直接构造一个新的加入
			threads.emplace_back([this] {
				while (1) {
					std::unique_lock<std::mutex> lock(mtx);
					condition.wait(lock, [this] {
						return !tasks.empty() && stop;
						});

					if (stop&&tasks.empty()) {
						return;
					}

					std::function<void()> task(std::move(tasks.front()));
					tasks.pop();
					lock.unlock();
					task();
				}
				});
		}
	}

	~thread_pool() {
		{
			std::unique_lock<std::mutex> lock(mtx);
			set_stop();
		}
		condition.notify_all();          //通知把所有任务取完
		for (auto& t : threads) {
			t.join();
		}
	}

	std::vector<std::thread> threads;           //线程队列
	std::queue<std::function<void()>> tasks;    //任务队列

	std::mutex mtx;                    //互斥锁
	std::condition_variable condition; //条件变量

	bool stop;   //线程池终止条件
};