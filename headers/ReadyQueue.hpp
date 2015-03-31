#ifndef READYQUEUE_HPP
#define READYQUEUE_HPP

#include "Task.hpp"
#include <memory>
#include <vector>
#include <iostream>

class ReadyQueue
{
public:
	virtual void pushTask(std::shared_ptr<Task> curTask);
	virtual std::shared_ptr<Task> pullTask();
	ReadyQueue();
	virtual bool isEmpty();
	void printQueue();
private:	
	std::vector<std::shared_ptr<Task>> readyList;
};

#endif