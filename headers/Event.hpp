#ifndef EVENT_HPP
#define EVENT_HPP

#include "Task.hpp"
#include <memory>
#include <iostream>

class Event
{
private:
	double execTime;
	std::shared_ptr<Task> relatedTask;
	bool endSession;
	bool isIoEvent;
	int ioWaitLoc;
public:
	Event();
	Event(std::shared_ptr<Task>, double, bool, bool=false);
	bool willEndSession();
	double getTime();
	bool isIo();
	std::shared_ptr<Task> getRelatedTask();
	void operator=(Event);
	bool operator>(Event) const;
	bool operator<(Event) const;
	int getIoWaitLoc();
	// ~Event();
};

#endif