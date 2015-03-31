#include "../headers/RRQueue.hpp"

void RRQueue::pushTask(std::shared_ptr<Task> curTask)
{
	std::cout << "This is being done in round robin\n";
	readyList.push_back(curTask);
}

std::shared_ptr<Task> RRQueue::pullTask()
{
	std::cout << "This is being done in round robin\n";
	std::shared_ptr<Task> toPull = readyList[0];
	readyList.erase(readyList.begin());
	double taskTime;
	if (toPull->isInterrupted())
	{
		taskTime = toPull->getRemainingInterruptTime();
		toPull->setInterrupted(false);
	}
	else
	{
		taskTime = toPull->getBurstTime();
	}
	if (taskTime > allowedTime)
	{
		toPull->setInterruptRunTime(allowedTime);
		toPull->setInterrupted(true);
		toPull->setRemainingInterruptTime(taskTime - allowedTime);
		pushTask(toPull);
	}
	else
	{
		toPull->setInterrupted(false);
	}
	return toPull;
}

bool RRQueue::isEmpty()
{
	std::cout << "Number of tasks in readyQueue: " << readyList.size() << std::endl;
	// printQueue();
	if (readyList.empty())
		return true;
	return false;
}

// void RRQueue::setInterruptTime(double);
