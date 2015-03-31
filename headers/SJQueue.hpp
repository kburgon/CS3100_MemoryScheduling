// #ifndef SJQUEUE_HPP
// #define SJQUEUE_HPP

// #include "ReadyQueue.hpp"
// #include <queue>

// class SJQueue:public ReadyQueue
// {
// public:
// 	void pushTask(std::shared_ptr<Task> curTask);
// 	std::shared_ptr<Task> pullTask();
// 	bool isEmpty();
// 	SJQueue():ReadyQueue()
// 	{
		
// 	}
// private:
// 	std::priority_queue<std::shared_ptr<Task>, std::vector<Task>, std::less<Task>> queue;
// };

// #endif