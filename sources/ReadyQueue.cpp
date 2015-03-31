// ready queue pseudocode
#include "../headers/ReadyQueue.hpp"

ReadyQueue::ReadyQueue()
{
	std::cout << "Started ready queue...\n";
}

void ReadyQueue::pushTask(std::shared_ptr<Task> curTask)
{
	// std::cout << "Adding item to queue...\n";
	readyList.push_back(curTask);
	// printQueue();
}

std::shared_ptr<Task> ReadyQueue::pullTask()
{
	std::shared_ptr<Task> toPull = readyList.back();
	readyList.pop_back();
	return toPull;
}

bool ReadyQueue::isEmpty()
{
	std::cout << "Number of tasks in readyQueue: " << readyList.size() << std::endl;
	// printQueue();
	if (readyList.empty())
		return true;
	return false;
}

void ReadyQueue::printQueue()
{
	std::cout << "\nPrinting queue...\n";
	for(auto&& queueItem:readyList)
	{
		std::cout << "Here is a task!\n";
	}
	std::cout << "Done printing queue\n\n";
}
