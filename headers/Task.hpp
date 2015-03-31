#ifndef TASK_HPP
#define TASK_HPP

#include "Burst.hpp"
#include <iostream>
#include <vector>

class Task
{
private:
	double interruptRunTime;
	double interruptTimeRemaining;
	bool burstInterrupted;
	bool isIo;
	std::vector<Burst> bursts;
	double createTime;
	double latency;
	int curBurstLoc;
	int numOfBursts;
	bool firstResponse;
	double firstResponseTime;
	bool isCompleted;
	double getRandomFloat();
	int getRandomInt(int);
public:
	Task(int, double, double);
	int getBurstLoc();
	void endBurst(int);
	bool curBurstIo();
	void setCreateTime(double);
	int getIoWaitLoc();
	double getBurstTime();
	double getFirstResponseTime();
	bool taskIsCompleted();
	double getLatency();
	bool isInterrupted();
	void setInterrupted(bool);
	void setInterruptRunTime(double);
	std::vector<Burst> assignBursts();
	void setRemainingInterruptTime(double);
	double getRemainingInterruptTime();
	bool operator>(Task) const;
	bool operator<(Task) const;
};

#endif