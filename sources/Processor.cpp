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
			// run setter for scheduler
			std::cout << "Number of IO devices: ";
			std::cin >> setInt;
			std::cout << "Setting IO devices to " << setInt << std::endl;
			mainScheduler.setNumIoDevices(setInt);
			// run setter for IO devices
			std::cout << "Cost of context switch: ";
			std::cin >> setFloat;
			std::cout << "Setting context switch to " << setFloat << std::endl;
			mainScheduler.setCntxtSwitchCost(setFloat);
			// run setter for context switch cost
			std::cout << "Percent CPU vs. IO bound: ";
			std::cin >> setFloat;
			std::cout << "Setting percentage to " << setFloat << std::endl;
			mainScheduler.setPercentCpuIo(setFloat);
			// run setter for CPU vs. IO percentage
			std::cout << "Task creation frequency (every _ units of time): ";
			std::cin >> setFloat;
			std::cout << "Setting creation frequency to " << setFloat << std::endl;
			mainScheduler.setTaskCreateFreq(setFloat);
			// run setter for task create frequency
			std::cout << "Round robin interrupt time: ";
			std::cin >> setInterruptTime;
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
			Scheduler roundRScheduler(roundRobin);
			roundRScheduler.init();
			roundResults = roundRScheduler.getData();
			printResults(roundResults);
			std::cout << "Pausing..\n";
			std::cin >> cmd;
			std::shared_ptr<ASJQueue> asjQ = std::make_shared<ASJQueue>();
			Scheduler ASJScheduler(asjQ);
			ASJScheduler.init();
			asjResults = ASJScheduler.getData();
			printResults(asjResults);
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
}
