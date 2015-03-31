#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <iostream>
#include "Event.hpp"
#include "EventQueue.hpp"
#include "Task.hpp"
#include "ReadyQueue.hpp"
#include "IOQueues.hpp"

struct Data
{
	double minLatency;
	double maxLatency;
	double avgLatency;
	double minResponseTime;
	double maxResponseTime;
	double avgResponseTime;
	double minCpuUtilization;
	double maxCpuUtilization;
	double avgCpuUtilization;
	double minIoUtilization;
	double maxIoUtilization;
	double avgIoUtilization;
	double minThroughput;
	double maxThroughput;
	double avgThroughput;
};

class Scheduler
{
private:
	std::vector<std::shared_ptr<Task>> finishedTasks;
	std::vector<double> ioUsage;
	std::vector<double> cpuUsage;
	double curTime;
	int numCpus;
	std::vector<uint> throughputList;
	double maxNumCpus;
	double cpuVsIo;
	double cpuBinding;
	double ioBinding;
	double taskCreateFreq;
	double cntxtSwitchCost;
	int numOfIoDevs;
	EventQueue eQueue;
	std::shared_ptr<ReadyQueue> rQueue;
	IOQueues ioDevQueue;
	void createTaskBinding();
	void createTasks(int);
	void execIO(std::shared_ptr<Task>);
	void handleIoEvent(std::shared_ptr<Task>);
	void handleCpuEvent(std::shared_ptr<Task>);
public:
	Scheduler();
	Scheduler(std::shared_ptr<ReadyQueue>);
	void setNumCpus(int numToSet);
	void setPercentCpuIo(double setPercent);
	void setTaskCreateFreq(double setFreq);
	void setCntxtSwitchCost(double setCost);
	void setNumIoDevices(int numDevices);
	void init();
	void runSession();
	Data getData();
	void calcLatency(Data&);
	void calcRespTime(Data&);
	void calcPercentUtilized(Data&);
	void calcThroughput(Data&);
	void execTask(std::shared_ptr<Task>);
	double getMinVal(std::vector<double>);
	double getMaxVal(std::vector<double>);
	double getAvgVal(std::vector<double>);
};

#endif