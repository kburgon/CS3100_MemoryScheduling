// Event class
#include "../headers/Event.hpp"

Event::Event()
{
	// std::cout << "constructing event...\n";
	execTime = 0;
	relatedTask = nullptr;
	endSession = true;
	isIoEvent = false;
}

Event::Event(std::shared_ptr<Task> taskToRelate, double newExecTime, bool setIfIo, bool setEndSession)
{
	// std::cout << "constructing event...\n";
	relatedTask = taskToRelate;
	execTime = newExecTime;
	endSession = setEndSession;
	isIoEvent = setIfIo;
	if (isIoEvent)
	{
		ioWaitLoc = relatedTask->getIoWaitLoc();
	}
	else ioWaitLoc = -1;
}

bool Event::willEndSession()
{
	return endSession;
}

bool Event::isIo()
{
	return isIoEvent;
}

double Event::getTime()
{
	return execTime;
}

std::shared_ptr<Task> Event::getRelatedTask()
{
	return relatedTask;
}

void Event::operator=(Event evToAssign)
{
	execTime = evToAssign.getTime();
	endSession = evToAssign.willEndSession();
	relatedTask = evToAssign.getRelatedTask();
	isIoEvent = evToAssign.isIo();
}

bool Event::operator>(Event toCompare) const
{
	// std::cout << "Is " << execTime << " > " << toCompare.getTime() << "?\n";
	if (execTime > toCompare.getTime()) return true;
	return false;
}

bool Event::operator<(Event toCompare) const
{
	// std::cout << "Is " << execTime << " < " << toCompare.getTime() << "?\n";
	if (execTime < toCompare.getTime()) return true;
	return false;
}

int Event::getIoWaitLoc()
{
	return ioWaitLoc;
}
// Event::~Event()
// {
// 	delete relatedTask;
// }
