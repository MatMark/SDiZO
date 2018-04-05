#pragma once
#include "inter.h"

class tab : public inter

{	
	
private:
	int size;
	int * t;
protected:
	
public:
	tab();
	~tab();
	void Build();
	void Add();
	void Delete();
	void Search();
	void Print();
	void SymBuild(int size);
	void SymAdd(int size, int rep);
	void SymDelete(int size, int rep);
	void SymSearch(int size, int rep);
};

