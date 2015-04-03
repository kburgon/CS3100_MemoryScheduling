#include "../headers/ASJQueue.hpp"

void ASJQueue::pushTask(std::shared_ptr<Task> curTask)
{
	readyList.push(curTask);
}

std::shared_ptr<Task> ASJQueue::pullTask()
{
	// std::cout << "This is being done in round robin\n";
	// std::shared_ptr<Task> toPull = readyList[0];
	// readyList.erase(readyList.begin());
	// // timeAvg.push_back(toPull->getBurstTime());
	// // allowedTime = calcAvg();
	// double taskTime;
	// if (toPull->isInterrupted())
	// {
	// 	taskTime = toPull->getRemainingInterruptTime();
	// 	toPull->setInterrupted(false);
	// }
	// else
	// {
	// 	taskTime = toPull->getBurstTime();
	// }
	// if (taskTime > allowedTime)
	// {
	// 	toPull->setInterruptRunTime(allowedTime);
	// 	toPull->setInterrupted(true);
	// 	toPull->setRemainingInterruptTime(taskTime - allowedTime);
	// 	pushTask(toPull);
	// }
	// else
	// {
	// 	toPull->setInterrupted(false);
	// }

	std::shared_ptr<Task> toPull = readyList.top();
	readyList.pop();
	return toPull;
}

bool ASJQueue::isEmpty()
{
	std::cout << "Does it fail here?\n";
	std::cout << "Number of tasks in readyQueue: " << readyList.size() << std::endl;
	// printQueue();
	if (readyList.empty())
		return true;
	return false;
}

double ASJQueue::calcAvg()
{
	std::cout << "Getting average\n";
	auto sum = std::accumulate(timeAvg.cbegin(), timeAvg.cend(), 0);
    return sum / static_cast<double>(timeAvg.size());
}
