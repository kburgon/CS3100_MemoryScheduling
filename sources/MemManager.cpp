#include "../headers/MemManager.hpp"

MemManager::MemManager()
{
	memSize = 10;
	faultCost = 0.5;
	totalCost = 0;
}

MemManager::MemManager(int newMemSize, double setFaultCost)
{
	memSize = newMemSize;
	faultCost = setFaultCost;
	totalCost = 0;
}

void MemManager::loadMemory(std::shared_ptr<Task> curTask)
{
	if (memory.empty())
	{
		memory = curTask->getRequiredMemory();
		totalCost = faultCost * 1;
	}
	else
	{
		std::vector<int> taskMemRef = curTask->getRequiredMemory();
		for (auto&& memSpace:memory)
		{

		}
	}
}

double MemManager::getPageFaultCost()
{
	return 0.5;
}