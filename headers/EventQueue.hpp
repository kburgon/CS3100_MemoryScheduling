#ifndef EVENTQUEUE_HPP
#define EVENTQUEUE_HPP

#include "Task.hpp"
#include "Event.hpp"
#include <vector>
#include <memory>
#include <queue>
#include <iostream>

class EventQueue
{
private:
	std::vector<Event> events;
	std::priority_queue<Event, std::vector<Event>, std::greater<Event>> pq;
	double switchCost;
public:
	EventQueue();
	EventQueue(double);
	// EventQueue();
	void addEvent(Event);
	Event pullEvent();
	bool isEmpty();
};



#endif