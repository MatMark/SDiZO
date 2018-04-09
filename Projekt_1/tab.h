#pragma once
#include "inter.h"

class tab : public inter

{	
	
private:
	int size;
	int * t;
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
	tab();
	~tab();
};

