// EventQueue pseudocode
#include "../headers/EventQueue.hpp"

void EventQueue::addEvent(Event newEvent)
{
	// std::cout << "Running add event...\n";
	// std::cout << "Pusing event that will happen at " << newEvent.getTime() << std::endl;
	pq.push(newEvent);
	// check if io event
	// if so set time to curTime + curTask.time
	// check if cpu event
	// if cpu then set time to curTime + curTask.time + contextSwitch
	// create event
	// add event to queue
}

Event EventQueue::pullEvent()
{
	Event toPop = pq.top();
	pq.pop();
	return toPop;
	// pulls event off of priority queue
	// returns event
}

EventQueue::EventQueue()
{
	// std::cout << "Constructing Event Queue...\n";
	// context switch cost = 0.5
	// set priority queue
}

bool EventQueue::isEmpty()
{
	if (pq.empty()) return true;
	return false;
}

// EventQueue::EventQueue(double newSwitchCost)
// {
// 	switchCost = newSwitchCost;
// 	// set priority queue
// }

// EventQueue::EventQueue(Task *curTask, int curTime, double newSwitchCost)
// {
// 	switchCost = newSwitchCost;
// 	addEvent(curTask, curTime);
// }
