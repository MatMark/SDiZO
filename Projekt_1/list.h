#pragma once
#include "inter.h"

struct element
{
	element * next, * prev;
	int value;
};

class list : public inter

{	
	
private:
	int size;
	element *first, *last;
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
	list();
	~list();
};

