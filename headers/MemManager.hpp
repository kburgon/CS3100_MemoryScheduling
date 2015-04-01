#ifndef MEMMANAGER_HPP
#define MEMMANAGER_HPP

#include <iostream>
#include <memory>
#include <vector>
#include "Task.hpp"

class MemManager
{
public:
	MemManager();
	MemManager(int, double=0.5);
	void loadMemory(std::shared_ptr<Task>);
	double getPageFaultCost();
private:
	int memSize;
	double faultCost;
	double totalCost;
	std::vector<int> memory;
};

#endif