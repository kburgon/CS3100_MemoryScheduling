#ifndef ASJQUEUE_HPP
#define ASJQUEUE_HPP

#include "ReadyQueue.hpp"
#include <queue>

class ASJQueue:public ReadyQueue
{
public:
	ASJQueue():ReadyQueue() {}
	void pushTask(std::shared_ptr<Task> curTask);
	std::shared_ptr<Task> pullTask();
	bool isEmpty();
	double calcAvg();
private:
	double allowedTime;
	// std::vector<std::shared_ptr<Task>> readyList;
	std::priority_queue<std::shared_ptr<Task>, std::vector<std::shared_ptr<Task>>, std::less<std::shared_ptr<Task>>> readyList;
	std::vector<double> timeAvg;
};

#endif