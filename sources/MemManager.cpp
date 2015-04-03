#include "../headers/MemManager.hpp"

MemManager::MemManager()
{
	memSize = 10;
	faultCost = 0.5;
	totalCost = 0;
	curPageLoc = -1;
}

MemManager::MemManager(int newMemSize, double setFaultCost)
{
	memSize = newMemSize;
	faultCost = setFaultCost;
	totalCost = 0;
	curPageLoc = -1;
}

void MemManager::loadMemory(std::shared_ptr<Task> curTask)
{
	totalCost = 0;
	if (memory.empty())
	{
		memory = curTask->getRequiredMemory();
		totalCost = faultCost * curTask->getMemSize();
		// curPageLoc = 0;
	}
	else
	{
		std::vector<int> taskMemRef = curTask->getRequiredMemory();
		for (auto&& memSpace:taskMemRef)
		{
			if (!isInMemory(memSpace))
			{
				pushPage(memSpace);
			}
		}
	}
}

double MemManager::getPageFaultCost()
{
	return totalCost;
}

bool MemManager::isInMemory(int memItem)
{
	auto foundVal = std::find(memory.begin(), memory.end(), memItem);
	if (*foundVal == memItem) return true;
	return false;
}

void MemManager::pushPage(int toPush)
{
	if (curPageLoc < 0 || curPageLoc >= memSize)
	{
		curPageLoc = 1;
	}
	if (curPageLoc == memory.size())
	{
		memory.push_back(toPush);
	}
	else 
	{
		memory[curPageLoc] = toPush;
	}
	totalCost += faultCost;
	++curPageLoc;
}

void MemManager::setMemSize(int newSize)
{
	memSize = newSize;
}

void MemManager::setPfCost(double newCost)
{
	faultCost = newCost;
}