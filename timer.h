#pragma once
#include <windows.h>

class timer

{	
	
private:
	double PCFreq;
	__int64 CounterStart;
	
protected:
	
public:
	timer();
	~timer();
	void StartCounter();
	double GetCounter();
};