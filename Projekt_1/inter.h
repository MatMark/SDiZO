#pragma once
#include "timer.h"

#define N 100000	//(0,N) przedzial losowanych wartosci

class inter
{
private:
	
protected:
	
public:
	virtual void Add() = 0;
	virtual void Delete() = 0;
	virtual void Build() = 0;
	virtual void Search() = 0;
	virtual void Print() = 0;
	virtual float SymBuild(int size) = 0;
	virtual void SymAdd(int size, int rep) = 0;
	virtual void SymDelete(int size, int rep) = 0;
	virtual void SymSearch(int size, int rep) = 0;
};
