#ifndef MEMMANAGER_HPP
#define MEMMANAGER_HPP

#include <iostream>
#include <memory>
#include <vector>
#include "Task.hpp"
#include <algorithm>

class MemManager
{
public:
	MemManager();
	MemManager(int, double=0.5);
	void loadMemory(std::shared_ptr<Task>);
	double getPageFaultCost();
private:
	bool isInMemory(int);
	// void pushMemItem(int);
	void pushPage(int);
	int memSize;
	int curPageLoc;
	double faultCost;
	double totalCost;
	std::vector<int> memory;
};

#endif