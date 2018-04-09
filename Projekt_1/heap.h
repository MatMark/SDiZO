#pragma once
#include "inter.h"

class heap : public inter

{	
	
private:
	int size;
	int * h;
	bool Find(int value, int node);
	int DelFind(int value, int node);

protected:
	
public:
	heap();
	~heap();
	void Build();
	void Add();
	void Delete();
	void Search();
	void Print();
	float SymBuild(int size);
	void SymAdd(int size, int rep);
	void SymDelete(int size, int rep);
	void SymSearch(int size, int rep);
};

