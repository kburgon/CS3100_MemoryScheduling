#ifndef TASK_HPP
#define TASK_HPP

#include "Burst.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

class Task
{
private:
	bool setCompareAvg;
	std::vector<double> bTimes;
	double avgBTime;
	double interruptRunTime;
	double interruptTimeRemaining;
	bool burstInterrupted;
	bool isIo;
	std::vector<Burst> bursts;
	int requiredMemSize;
	std::vector<int> requiredMemory;
	double createTime;
	double latency;
	int curBurstLoc;
	int numOfBursts;
	bool firstResponse;
	double firstResponseTime;
	bool isCompleted;
	double getRandomFloat();
	int getRandomInt(int);
	void generateMemReq();
public:
	Task(int, double, double);
	int getBurstLoc();
	void endBurst(int);
	bool curBurstIo();
	void setCreateTime(double);
	int getIoWaitLoc();
	const double getBurstTime() const;
	double getFirstResponseTime();
	bool taskIsCompleted();
	double getLatency();
	bool isInterrupted() const;
	void setInterrupted(bool);
	void setInterruptRunTime(double);
	std::vector<Burst> assignBursts();
	void setRemainingInterruptTime(double);
	double getRemainingInterruptTime();
	std::vector<int> getRequiredMemory();
	int getMemSize();
	bool operator>(const Task&) const;
	bool operator<(const Task&) const;
	double getAvgTime() const;
};

// struct Compare
// {
// 	bool operator>(const std::shared_ptr<Task>& tOne, const std::shared_ptr<Task>& tTwo) const
// 	{
// 		if (tOne->getBurstTime() > tTwo->getBurstTime()) return true;
// 		return false;
// 	}

// 	bool operator<(const std::shared_ptr<Task>& tOne, const std::shared_ptr<Task>& tTwo) const
// 	{
// 		if (tOne->getBurstTime() < tTwo->getBurstTime()) return true;
// 		return false;
// 	}
// };

#endif