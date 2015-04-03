#ifndef SJQUEUE_HPP
#define SJQUEUE_HPP

#include "ReadyQueue.hpp"
#include <vector>
#include <queue>

class SJQueue:public ReadyQueue
{
public:
	void pushTask(std::shared_ptr<Task> curTask);
	std::shared_ptr<Task> pullTask();
	bool isEmpty();
	SJQueue():ReadyQueue()
	{
		
	}
	// friend bool operator>(const std::shared_ptr<Task>&, const std::shared_ptr<Task>&);
	// friend bool operator<(const std::shared_ptr<Task>&, const std::shared_ptr<Task>&);
private:
	std::priority_queue<std::shared_ptr<Task>, std::vector<std::shared_ptr<Task>>, std::less<std::shared_ptr<Task>>> queue;
};

#endif