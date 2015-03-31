#ifndef BURST_HPP
#define BURST_HPP

#include <iostream>
#include <random>

class Burst
{
private:
	double bTime;
	double endTime;
	double latency;
	bool isIoBurst;
	int waitLocation;
public:
	int getIoLocation();
	void setIfIoStatus(bool);
	Burst(int=-1);
	Burst(double, int=-1);
	bool isIo();
	double getLatency();
	double getEndTime();
	double getBurstTime() const;
	void endBurst(int);
	void setDevLoc(int);
	void operator=(Burst);
	void setLatency(double);
	void setBurstTime(double);
	void setEndTime(double);
	void setIoLoc(int);
};

class IoBurst:public Burst
{
private:
public:
	IoBurst(int newWaitLoc=0):Burst(newWaitLoc)
	{
		setIfIoStatus(true);
	}
	IoBurst(double newTime, int newWaitLoc=0):Burst(newTime, newWaitLoc)
	{
		setIfIoStatus(true);
	}
	void operator=(IoBurst);
};

#endif
