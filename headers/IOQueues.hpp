#ifndef IOQUEUES_HPP
#define IOQUEUES_HPP

#include "Task.hpp"
#include <memory>
#include <vector>
#include <iostream>

class IOQueues
{
private:
	std::vector<std::vector<std::shared_ptr<Task>>> queueList;
public:
	IOQueues(int=0);
	void createQueues(int);
	void pushTask(std::shared_ptr<Task>);
	std::shared_ptr<Task> getNextTask(int);
	void finishTask(int);
	bool queueIsEmpty(int);
	double getIoUtilization();
};

#endif