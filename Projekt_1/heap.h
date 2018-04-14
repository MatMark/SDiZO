#pragma once
#include "inter.h"

class heap : public inter

{	
	
private:
	int size;
	int * h;
	int Find(int value, int node);
	float SymBuild(int size);

protected:
	void Build();
	void Add();
	void Delete();
	void Search();
	void Print();
	void SymAdd(int size, int rep);
	void SymDelete(int size, int rep);
	void SymSearch(int size, int rep);
public:
	heap();
	~heap();
};

