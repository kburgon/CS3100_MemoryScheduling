#include "../headers/Processor.hpp"

Processor::Processor()
{
	std::cout << "Initializing processor..." << std::endl;
}

void Processor::showHelpText()
{
	std::cout << "  List of commands and explanation:" << std::endl
		<< "	exit - exit the application" << std::endl
		<< "	setvars - set the user-defined variables\n"
		<< "	run - run the scheduler\n";
}

void Processor::startShell()
{
	latPlot = 0;
	rtPlot = 0;
	cutilPlot = 0;
	iutilPlot = 0;
	thPlot = 0;
	std::string cmd;
	std::vector<std::string> parsedCmd;
	double setFloat;
	setInterruptTime = 10;
	int setInt;
	bool willExit = false;
	while (!willExit)
	{
		std::cout << "[main]:";
		std::cin >> cmd;
		if (cmd == "help")
		{
			showHelpText();
		}
		else if (cmd == "exit")
		{
			willExit = true;
		}
		else if (cmd == "setvars")
		{
			std::cout << "Setting the variables.\nNumber of CPUs: ";
			std::cin >> setInt;
			std::cout << "Setting CPUs to " << setInt << std::endl;
			mainScheduler.setNumCpus(setInt);
			roundRScheduler.setNumCpus(setInt);
			ASJScheduler.setNumCpus(setInt);
			sjScheduler.setNumCpus(setInt);
			// run setter for scheduler
			std::cout << "Number of IO devices: ";
			std::cin >> setInt;
			std::cout << "Setting IO devices to " << setInt << std::endl;
			mainScheduler.setNumIoDevices(setInt);
			roundRScheduler.setNumIoDevices(setInt);
			ASJScheduler.setNumIoDevices(setInt);
			sjScheduler.setNumIoDevices(setInt);
			// run setter for IO devices
			std::cout << "Cost of context switch: ";
			std::cin >> setFloat;
			std::cout << "Setting context switch to " << setFloat << std::endl;
			mainScheduler.setCntxtSwitchCost(setFloat);
			roundRScheduler.setCntxtSwitchCost(setFloat);
			ASJScheduler.setCntxtSwitchCost(setFloat);
			sjScheduler.setCntxtSwitchCost(setFloat);
			// run setter for context switch cost
			std::cout << "Percent CPU vs. IO bound: ";
			std::cin >> setFloat;
			std::cout << "Setting percentage to " << setFloat << std::endl;
			mainScheduler.setPercentCpuIo(setFloat);
			roundRScheduler.setPercentCpuIo(setFloat);
			ASJScheduler.setPercentCpuIo(setFloat);
			sjScheduler.setPercentCpuIo(setFloat);
			// run setter for CPU vs. IO percentage
			std::cout << "Task creation frequency (every _ units of time): ";
			std::cin >> setFloat;
			std::cout << "Setting creation frequency to " << setFloat << std::endl;
			mainScheduler.setTaskCreateFreq(setFloat);
			roundRScheduler.setTaskCreateFreq(setFloat);
			ASJScheduler.setTaskCreateFreq(setFloat);
			sjScheduler.setTaskCreateFreq(setFloat);
			// run setter for task create frequency
			std::cout << "Round robin interrupt time: ";
			std::cin >> setInterruptTime;

			std::cout << "Memory size: ";
			std::cin >> setInt;
			mainScheduler.setMemSize(setInt);
			roundRScheduler.setMemSize(setInt);
			ASJScheduler.setMemSize(setInt);
			sjScheduler.setMemSize(setInt);
			std::cout << "Page fault length: ";
			std::cin >> setFloat;
			mainScheduler.setPfCost(setFloat);
			roundRScheduler.setPfCost(setFloat);
			ASJScheduler.setPfCost(setFloat);
			sjScheduler.setPfCost(setFloat);
			std::cout << "Variables set.\n";
		}
		else if (cmd == "run")
		{
			mainScheduler.init();
			sessionResults = mainScheduler.getData();
			printResults(sessionResults);
			std::cout << "Pausing..\n";
			std::cin >> cmd;
			std::shared_ptr<RRQueue> roundRobin = std::make_shared<RRQueue>(setInterruptTime);
			roundRScheduler.setReadyQueue(roundRobin);
			roundRScheduler.init();
			roundResults = roundRScheduler.getData();
			printResults(roundResults);
			std::cout << "Pausing..\n";
			std::cin >> cmd;
			std::shared_ptr<ASJQueue> asjQ = std::make_shared<ASJQueue>();
			ASJScheduler.setReadyQueue(asjQ);
			ASJScheduler.init();
			asjResults = ASJScheduler.getData();
			printResults(asjResults);
			std::cin >> cmd;
			std::shared_ptr<SJQueue> sjQ = std::make_shared<SJQueue>();
			sjScheduler.setReadyQueue(sjQ);
			sjScheduler.init();
			sjResults = sjScheduler.getData();
			printResults(sjResults);
		}
		else
		{
			std::cout << "Unrecognized command: " << cmd << std::endl;
		}
		parsedCmd.clear();
	}
}

std::vector<std::string> Processor::parseString(const std::string& toParse)
{
        std::string temp;
        std::vector<std::string> parsedList;
        bool newWord = true;
        for (auto&& inChar:toParse)
    {
        if (inChar == ' ')
        {
                newWord = true;
        }
        else
        {
            if (newWord)
            {
                    temp = inChar;
                    parsedList.push_back(temp);
                    newWord = false;
            }
            else
            {
                    temp = inChar;
                    parsedList[parsedList.size() - 1] += temp;
            }
        }
    }
    return parsedList;
}

void Processor::printResults(Data results)
{
	std::cout << "\n\nRESULTS FROM SESSION:\n"
		<< "\n--Latency--\n"
		<< "Min latency: " << results.minLatency << std::endl
		<< "Max latency: " << results.maxLatency << std::endl
		<< "Avg latency: " << results.avgLatency << std::endl
		<< "\n--Response Time--\n"
		<< "Min response time: " << results.minResponseTime << std::endl
		<< "Max response time: " << results.maxResponseTime << std::endl
		<< "Avg response time: " << results.avgResponseTime << std::endl
		<< "\n--CPU Utilization--\n"
		<< "Min utilization: " << results.minCpuUtilization << std::endl
		<< "Max utilization: " << results.maxCpuUtilization << std::endl
		<< "Avg utilization: " << results.avgCpuUtilization << std::endl
		<< "\n--IO Utilization--\n"
		<< "Min utilization: " << results.minIoUtilization << std::endl
		<< "Max utilization: " << results.maxIoUtilization << std::endl
		<< "Avg utilization: " << results.avgIoUtilization << std::endl
		<< "\n--Throughput--\n"
		<< "Min throughput: " << results.minThroughput << std::endl
		<< "Max throughput: " << results.maxThroughput << std::endl
		<< "Avg throughput: " << results.avgThroughput << std::endl
		<< std::endl;
	std::ofstream dout;
	dout.open("latResult.dat", std::ios::out | std::ios::app);
	dout << latPlot << "	" << results.avgLatency << std::endl;
	dout.close();
	dout.open("rtResult.dat", std::ios::out | std::ios::app);
	dout << rtPlot << "	" << results.avgResponseTime << std::endl;
	dout.close();
	dout.open("cutilResult.dat", std::ios::out | std::ios::app);
	dout << cutilPlot << "	" << results.avgCpuUtilization << std::endl;
	dout.close();
	dout.open("iutilResult.dat", std::ios::out | std::ios::app);
	dout << iutilPlot << "	" << results.avgIoUtilization << std::endl;
	dout.close();
	dout.open("thResult.dat", std::ios::out | std::ios::app);
	dout << thPlot << "	" << results.avgThroughput << std::endl;
	dout.close();
	++latPlot;
	++rtPlot;
	++cutilPlot;
	++iutilPlot;
	++thPlot;
}
