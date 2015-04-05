#include "../headers/ASJQueue.hpp"

void ASJQueue::pushTask(std::shared_ptr<Task> curTask)
{
	readyList.push(curTask);
}

std::shared_ptr<Task> ASJQueue::pullTask()
{
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
