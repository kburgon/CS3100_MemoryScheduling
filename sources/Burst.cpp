// two classes: Burst and IoBurst
#include "../headers/Burst.hpp"

Burst::Burst(int newWaitLoc)
{
	bTime = 5;
	endTime = 0;
	isIoBurst = false;
	latency = 0;
	waitLocation = newWaitLoc;
}

int Burst::getIoLocation()
{
	return waitLocation;
}

Burst::Burst(double newBTime, int newWaitLoc)
{
	endTime = 0;
	isIoBurst = false;
	bTime = newBTime;
	latency = 0;
	waitLocation = newWaitLoc;
}

bool Burst::isIo()
{
	if (!isIoBurst) 
	{
		// std::cout << "This is a cpu burst\n";
		return false;
	}
	// std::cout << "This is an io burst\n";
	return true;
}

void Burst::endBurst(int endTime)
{
	latency = endTime;
}

void Burst::setIfIoStatus(bool setStatus)
{
	isIoBurst = setStatus;
}

double Burst::getLatency()
{
	return latency;
}

double Burst::getEndTime()
{
	return endTime;
}

double Burst::getBurstTime() const
{
	return bTime;
}

void Burst::setDevLoc(int newLoc)
{
	waitLocation = newLoc;
}

void Burst::setLatency(double newTime)
{
	latency = newTime;
}

void Burst::setEndTime(double newTime)
{
	endTime = newTime;
}

void Burst::setBurstTime(double newTime)
{
	bTime = newTime;
}

void Burst::setIoLoc(int newLoc)
{
	waitLocation = newLoc;
}

void Burst::operator=(Burst toAssign)
{
	latency = toAssign.getLatency();
	endTime = toAssign.getEndTime();
	bTime = toAssign.getBurstTime();
	setIfIoStatus(toAssign.isIo());
	waitLocation = toAssign.getIoLocation();
}

void IoBurst::operator=(IoBurst toAssign)
{
	setLatency(toAssign.getLatency());
	setEndTime(toAssign.getEndTime());
	setBurstTime(toAssign.getBurstTime());
	setIfIoStatus(toAssign.isIo());
	setIoLoc(toAssign.getIoLocation());
}

// child class IoBurst
