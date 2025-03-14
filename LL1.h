#pragma once
#include "Scaner.h"

class LL1
{
private:
	int m[5000];	//магазин LL(1)-анализатора
	int z;			//указатель магазина

	void epsilon();

public:
	static Scaner* scan;

	LL1(Scaner* scan);
	int LL_1();
};
