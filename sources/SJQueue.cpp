#include "../headers/SJQueue.hpp"

void SJQueue::pushTask(std::shared_ptr<Task> curTask)
{
	queue.push(curTask);
}

std::shared_ptr<Task> SJQueue::pullTask()
{
	std::shared_ptr<Task> toPull = queue.top();
	queue.pop();
	return toPull;
}

bool SJQueue::isEmpty()
{
	std::cout << "Number of tasks in readyQueue: " << queue.size() << std::endl;
	// printQueue();
	if (queue.empty())
		return true;
	return false;
}

// bool operator>(const std::shared_ptr<Task>& tOne, const std::shared_ptr<Task>& tTwo)
// {
// 	if (tOne->getBurstTime() > tTwo->getBurstTime()) return true;
// 	return false;
// }

// bool operator<(const std::shared_ptr<Task>& tTwo, const std::shared_ptr<Task>& tOne)
// {
// 	if (tOne->getBurstTime() > tTwo->getBurstTime()) return true;
// 	return false;
// }
