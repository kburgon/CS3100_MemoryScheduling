#include "../headers/Scheduler.hpp"

Scheduler::Scheduler()
{
	rQueue = std::make_shared<ReadyQueue>();
	numCpus = 4;
	maxNumCpus = numCpus;
	cpuVsIo = 50;
	taskCreateFreq = 5;
	cntxtSwitchCost = 1;
	numOfIoDevs = 3;
	curTime = 0;
}

Scheduler::Scheduler(std::shared_ptr<ReadyQueue> setReady)
{
	rQueue = setReady;
	numCpus = 4;
	maxNumCpus = numCpus;
	cpuVsIo = 50;
	taskCreateFreq = 5;
	cntxtSwitchCost = 1;
	numOfIoDevs = 3;
	curTime = 0;
}

void Scheduler::setNumCpus(int numToSet)
{
	numCpus = numToSet;
	maxNumCpus = numCpus;
}

void Scheduler::setPercentCpuIo(double setPercent)
{
	cpuVsIo = setPercent;
}

void Scheduler::setTaskCreateFreq(double setFreq)
{
	taskCreateFreq = setFreq;
}

void Scheduler::setCntxtSwitchCost(double setCost)
{
	cntxtSwitchCost = setCost;
}

void Scheduler::setNumIoDevices(int numDevices)
{
	numOfIoDevs = numDevices;
}

void Scheduler::init() // issue:  not adding context swith or page fault to init
{
	createTaskBinding();
	ioDevQueue.createQueues(numOfIoDevs);
	std::shared_ptr<Task> initTask = std::make_shared<Task>(numOfIoDevs, cpuBinding, ioBinding);
	initTask->setCreateTime(curTime);
	std::shared_ptr<Task> endTask = std::make_shared<Task>(numOfIoDevs, cpuBinding, ioBinding);
	endTask->setCreateTime(curTime);
	Event firstEvent(initTask, 0, false);
	Event lastEvent(endTask, 1000, false, true);
	eQueue.addEvent(firstEvent);
	eQueue.addEvent(lastEvent);
	runSession();
}

void Scheduler::createTaskBinding()
{
	double multiplier = cpuVsIo * 0.02;
	cpuBinding = multiplier;
	ioBinding = 2 - multiplier;
}

void Scheduler::createTasks(int numOfTasks)
{
	std::shared_ptr<Task> taskToAdd;
	Event eventToAdd;
	double newTaskExecTime;
	for (int n = 0; n < numOfTasks; n++)
	{
		taskToAdd = std::make_shared<Task>(numOfIoDevs, cpuBinding, ioBinding);
		taskToAdd->setCreateTime(curTime);
		execTask(taskToAdd);
	}
}

void Scheduler::handleIoEvent(std::shared_ptr<Task> eventTask)
{
	std::cout << "-\n";
	int ioDevLoc = eventTask->getIoWaitLoc();
	std::cout << "--\n";
	ioDevQueue.finishTask(ioDevLoc);
	std::cout << "---\n";
	eventTask->endBurst(curTime);
	if (!ioDevQueue.queueIsEmpty(ioDevLoc))
	{
		std::shared_ptr<Task> newEventTask = ioDevQueue.getNextTask(ioDevLoc);
		double eventTime = curTime + newEventTask->getBurstTime();
		Event newEvent(newEventTask, eventTime, true);
		eQueue.addEvent(newEvent);
	}
	ioUsage.push_back(ioDevQueue.getIoUtilization());
	// else std::cout << "<<<<<<<<<<<<The queue is empty!>>>>>>>>>>>>\n";
}

void Scheduler::handleCpuEvent(std::shared_ptr<Task> eventTask)
{
	eventTask->endBurst(curTime);
	std::shared_ptr<Task> toEx;
	Event eToEx;
	double pfCost;
	if (numCpus < maxNumCpus)
		numCpus++;
	double newEventTime;
	std::cout << "Does it fail here?\n";
	while (!rQueue->isEmpty() && numCpus > 0)
	{
		std::cout << "Number of cpus avaiable: " << numCpus << std::endl;
		std::cout << "\n\nFilling cpus...\n\n";
		toEx = rQueue->pullTask();
		memRef.loadMemory(toEx);
		pfCost = memRef.getPageFaultCost();
		newEventTime = curTime + cntxtSwitchCost + pfCost + eventTask->getBurstTime();
		eToEx = Event(toEx, newEventTime, false);
		eQueue.addEvent(eToEx);
		numCpus--;
	}
	double cpuUsePercent = 1 - (numCpus / maxNumCpus);
	cpuUsage.push_back(cpuUsePercent);
}

void Scheduler::execIO(std::shared_ptr<Task> execTask)
{
	if (!execTask->taskIsCompleted())
	{
		int ioDevLoc = execTask->getIoWaitLoc();
		std::cout << "Wait location: " << ioDevLoc << std::endl;
		if (ioDevQueue.queueIsEmpty(ioDevLoc))
		{
			double eventTime = curTime + execTask->getBurstTime();
			Event newEvent(execTask, eventTime, true);
			eQueue.addEvent(newEvent);
		}
		ioDevQueue.pushTask(execTask);
	}
	else
	{
		std::cout << "Task was finished.\n";
	}
}

void Scheduler::execTask(std::shared_ptr<Task> exTask)
{
	if (!exTask->taskIsCompleted())
	{
		std::cout << "Number of cpus avaiable: " << numCpus << std::endl;
		rQueue->pushTask(exTask);
		if (numCpus > 0)
		{
			std::cout << "There are " << numCpus << " cpus left. Filling...\n";
			std::shared_ptr<Task> toExec = rQueue->pullTask();
			memRef.loadMemory(toExec);
			double pfCost = memRef.getPageFaultCost();
			double timeToEvent = cntxtSwitchCost + pfCost + toExec->getBurstTime();
			double nextEventTime = curTime + timeToEvent;
			Event nextEvent(exTask, nextEventTime, false);
			eQueue.addEvent(nextEvent);
			numCpus--;
		}
	}
	else
	{
		std::cout << "The task has finished.\n";
	}
	
}

void Scheduler::runSession()
{
	bool endOfSession = false;
	Event curEvent;
	std::shared_ptr<Task> curTask;
	double lastTaskCreateTime = 0;
	double lastTimedUnit = 0;
	double timeDif;
	uint prevFinishedTasks = 0;
	uint curFinTaskSize;
	while (!endOfSession)
	{
		std::cout << "\n\n************************************NEW EVENT*******************************\n";
		curEvent = eQueue.pullEvent();
		curTime = curEvent.getTime();
		if (curEvent.willEndSession())
		{
			endOfSession = true;
			std::cout << "Ending session now with time at " << curEvent.getTime() << "\n";
		}
		else
		{
			curTask = curEvent.getRelatedTask();
			if (curTask->curBurstIo()) std::cout << "This is an IO task\n";
			else std::cout << "This is a CPU task\n";
			if (curEvent.isIo() && curTask->getIoWaitLoc() > -1)
			{
				std::cout << "This is an IO event\n";
				handleIoEvent(curTask);
			}
			else
			{
				std::cout << "This is a CPU event\n";
				handleCpuEvent(curTask);
			}
			timeDif = curTime - lastTimedUnit;
			if (timeDif > 1.0)
			{
				lastTimedUnit = curTime;
				curFinTaskSize = finishedTasks.size();
				throughputList.push_back(curFinTaskSize - prevFinishedTasks);
			}
			std::cout << "Not ending session yet!  Time: " << curEvent.getTime() << "\n";
			if (!curTask->taskIsCompleted())
			{
				if (curTime > (lastTaskCreateTime + taskCreateFreq))
				{
					lastTaskCreateTime = curTime;
					createTasks(1);
				}
				if (curTask->curBurstIo())
				{
					std::cout << "This has been recognized as an io burst...\n";
					execIO(curTask);
				}
				else
				{
					std::cout << "This has been recognized as a cpu burst...\n";
					execTask(curTask);
				}
			}
			else
			{
				finishedTasks.push_back(curTask);
				std::cout << "Pushed back finished task.\n";
			}
		}
	}
}

Data Scheduler::getData()
{
	// std::cout << "initiating data..\n";
	Data results;
	// std::cout << "Calculating latency\n";
	calcLatency(results);
	// std::cout << "Calculating response time\n";
	calcRespTime(results);
	// std::cout << "Calculating utilization\n";
	calcPercentUtilized(results);
	// std::cout << "Calculating throughput\n";
	calcThroughput(results);
	return results;
}

void Scheduler::calcLatency(Data &resultDats)
{
	std::vector<double> latencyList;
	for (auto&& indTask:finishedTasks)
	{
		latencyList.push_back(indTask->getLatency());
	}
	resultDats.maxLatency = getMaxVal(latencyList);
	resultDats.minLatency = getMinVal(latencyList);
	resultDats.avgLatency = getAvgVal(latencyList);
}

void Scheduler::calcRespTime(Data &resultDats)
{
	std::vector<double> firstResponseL;
	for (auto&& indTask:finishedTasks)
	{
		firstResponseL.push_back(indTask->getFirstResponseTime());
	}
	resultDats.maxResponseTime = getMaxVal(firstResponseL);
	resultDats.minResponseTime = getMinVal(firstResponseL);
	resultDats.avgResponseTime = getAvgVal(firstResponseL);	
}

void Scheduler::calcPercentUtilized(Data &resultDats)
{
	resultDats.minCpuUtilization = getMinVal(cpuUsage);
	resultDats.maxCpuUtilization = getMaxVal(cpuUsage);
	resultDats.avgCpuUtilization = getAvgVal(cpuUsage);
	resultDats.minIoUtilization = getMinVal(ioUsage);
	resultDats.maxIoUtilization = getMaxVal(ioUsage);
	resultDats.avgIoUtilization = getAvgVal(ioUsage);
}

void Scheduler::calcThroughput(Data &resultDats)
{
	std::vector<double> resultThroughput;
	for (auto&& indRes:throughputList)
	{
		resultThroughput.push_back(static_cast<double>(indRes));
	}
	resultDats.minThroughput = getMinVal(resultThroughput);
	resultDats.maxThroughput = getMaxVal(resultThroughput);
	resultDats.avgThroughput = getAvgVal(resultThroughput);
}

double Scheduler::getMinVal(std::vector<double> valList)
{
	std::cout << "Finding minimum value\n";
	double minVal = 0;
	for (auto&& value:valList)
	{
		if (value < minVal)
			minVal = value;
	}
	return minVal;
}

double Scheduler::getMaxVal(std::vector<double> valList)
{
	std::cout << "Finding maximum value\n";
	double maxVal = 0;
	for (auto&& value:valList)
	{
		if (value > maxVal)
			maxVal = value;
	}
	return maxVal;
}

double Scheduler::getAvgVal(std::vector<double> valList)
{
	std::cout << "Getting average\n";
	auto sum = std::accumulate(valList.cbegin(), valList.cend(), 0);
    return sum / static_cast<double>(valList.size());
}
