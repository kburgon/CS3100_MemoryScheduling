#ifndef RRQUEUE_HPP
#define RRQUEUE_HPP

#include "ReadyQueue.hpp"

class RRQueue:public ReadyQueue
{
public:
	virtual void pushTask(std::shared_ptr<Task> curTask);
	virtual std::shared_ptr<Task> pullTask();
	virtual bool isEmpty();
	RRQueue():ReadyQueue()
	{
		std::cout << "Initiating round robin scheduling...\n";
		allowedTime = 10;
	}
	RRQueue(double newAllowedTime):ReadyQueue()
	{
		std::cout << "Initiating round robin scheduling...\n";
		allowedTime = newAllowedTime;
	}
	// void setInterruptTime(double);
private:
	std::vector<std::shared_ptr<Task>> readyList;
	double allowedTime;
	double setInterruptTime;
};

#endif