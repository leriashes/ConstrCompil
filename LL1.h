#pragma once
#include "Scaner.h"

class LL1
{
private:
	int m[5000];	//������� LL(1)-�����������
	int z;			//��������� ��������

	void epsilon();

public:
	static Scaner* scan;

	LL1(Scaner* scan);
	int LL_1();
};
