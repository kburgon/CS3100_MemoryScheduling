#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include "Scheduler.hpp"
#include "RRQueue.hpp"
#include "ASJQueue.hpp"
#include "SJQueue.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <memory>
#include <fstream>
// #include <sstream>

class Processor
{
private:
	int latPlot;
	int rtPlot;
	int cutilPlot;
	int iutilPlot;
	int thPlot;
	double setInterruptTime;
	Scheduler mainScheduler;
	Scheduler roundRScheduler;
	Scheduler ASJScheduler;
	Scheduler sjScheduler;
	Data sessionResults;
	Data roundResults;
	Data asjResults;
	Data sjResults;
public:
	Processor();
	void startShell();
	void showHelpText();
	std::vector<std::string> parseString(const std::string&);
	void printResults(Data);
};

#endif
