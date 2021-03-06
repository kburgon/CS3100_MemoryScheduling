#include "../headers/Task.hpp"

Task::Task(int ioDevCnt, double cpuMultiplier, double ioMultiplier)
{
	double ioTimeSet, cpuTimeSet;
	isIo = false;
	Burst newBurst;
	IoBurst newIoBurst;
	numOfBursts = 0;
	for (int n = 0; n < 10; n++)
	{
		if (isIo)
		{
			ioTimeSet = ioMultiplier * getRandomFloat();
			std::cout << "IO BINDING: The multiplier is at " << ioMultiplier << " and the new time is " << ioTimeSet << std::endl;
			newIoBurst = IoBurst(ioMultiplier, getRandomInt(ioDevCnt));
			bursts.push_back(newIoBurst);
			isIo = false;
		}
		else
		{
			cpuTimeSet = cpuMultiplier * getRandomFloat();
			std::cout << "CPU BINDING: The multiplier is at " << ioMultiplier << " and the new time is " << cpuTimeSet << std::endl;
			newBurst = Burst(cpuTimeSet);
			bursts.push_back(newBurst);
			isIo = true;
		}
		numOfBursts++;
	}
	curBurstLoc = 0;
	firstResponse = true;
	isCompleted = false;
	burstInterrupted = false;
	interruptTimeRemaining = -1;
	requiredMemSize = 5;
	setCompareAvg = false;
	avgBTime = 0;
	generateMemReq();
}

void Task::generateMemReq()
{
	for (int n = 0; n < requiredMemSize; ++n)
	{
		requiredMemory.push_back(getRandomInt(10));
	}
}

void Task::setCreateTime(double timeSet)
{
	createTime = timeSet;
}

void Task::endBurst(int endTime)
{
	if (bursts[curBurstLoc].isIo() && firstResponse == true)
	{
		firstResponse = false;
		firstResponseTime = endTime - createTime;
		bursts[curBurstLoc].endBurst(endTime);
		curBurstLoc++;
		std::cout << "Advancing to next burst\n";
	}
	else if (!isInterrupted() || bursts[curBurstLoc].isIo())
	{	
		bursts[curBurstLoc].endBurst(endTime);
		curBurstLoc++;
		std::cout << "Advancing to next burst\n";
		bTimes.push_back(bursts[curBurstLoc].getBurstTime());
	}
	else std::cout << "Not advancing to next burst\n";
	if (curBurstLoc == numOfBursts)
	{
		std::cout << "Shutting down task...\n";
		curBurstLoc = -1;
		isCompleted = true;
	}
	latency = endTime - createTime;
}

bool Task::curBurstIo()
{
	return bursts[curBurstLoc].isIo();
}

int Task::getIoWaitLoc()
{
	if (bursts[curBurstLoc].isIo())
	{
		return bursts[curBurstLoc].getIoLocation();
	}
	return -1;
}

int Task::getBurstLoc()
{
	return curBurstLoc;
}

const double Task::getBurstTime() const
{
	if (isInterrupted())
	{
		const double returnTime = interruptRunTime;
		return returnTime;
	}
	else if (interruptTimeRemaining == -1)
	{
		const double returnTime = bursts[curBurstLoc].getBurstTime();
		return returnTime;	
	}
	return interruptTimeRemaining;
}

std::vector<Burst> Task::assignBursts()
{
	return bursts;
}

bool Task::taskIsCompleted()
{
	return isCompleted;
}

double Task::getRandomFloat()
{
	std::random_device rdm;
	std::mt19937 mt(rdm());
	std::normal_distribution<> norm(2, 0.75);
	double normalNum = norm(mt);
	return normalNum;
}

int Task::getRandomInt(int upperNum)
{
	std::random_device rdm;
	std::mt19937 mt(rdm());
	std::uniform_int_distribution<> devLocGen(0, upperNum - 1);
	int randNum = devLocGen(mt);
	return randNum;
}

double Task::getLatency()
{
	return latency;
}

double Task::getFirstResponseTime()
{
	return firstResponseTime;
}

bool Task::isInterrupted() const
{
	return burstInterrupted;
}

void Task::setInterrupted(bool setIsInterrupted)
{
	burstInterrupted = setIsInterrupted;
}

void Task::setInterruptRunTime(double setTime)
{
	interruptRunTime = setTime;
}

void Task::setRemainingInterruptTime(double setTime)
{
	interruptTimeRemaining = setTime;
}

double Task::getRemainingInterruptTime()
{
	return interruptTimeRemaining;
}

bool Task::operator>(const Task& toCompare) const
{
	if (!setCompareAvg)
	{
		if (bursts[curBurstLoc].getBurstTime() > toCompare.getBurstTime())
			return true;
		return false;
	}
	return getAvgTime() > toCompare.getAvgTime();	
}

bool Task::operator<(const Task& toCompare) const
{
	if (!setCompareAvg)
	{
		if (bursts[curBurstLoc].getBurstTime() < toCompare.getBurstTime())
			return true;
		return false;
	}
	return getAvgTime() < toCompare.getAvgTime();
}

std::vector<int> Task::getRequiredMemory()
{
	// std::vector<int> testMem(10, 5);
	return requiredMemory;
}

int Task::getMemSize()
{
	// std::vector<int> testMem(10, 5);
	// return testMem.size();
	return requiredMemSize;
}

double Task::getAvgTime() const
{
	if (!bTimes.empty())
	{
		double totalTimes = std::accumulate(bTimes.begin(), bTimes.end(), totalTimes);
		return totalTimes / bTimes.size();
	}
	return 0;
}