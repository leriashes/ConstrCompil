#pragma once
#include "Scaner.h"
#include "Translate.h"

class LL1
{
private:
	int m[5000];	//������� LL(1)-�����������
	int z;			//��������� ��������

	void epsilon();

public:
	static Scaner* scan;
	Translate* tran;

	LL1(Scaner* scan);
	~LL1();

	int LL_1();
	void PrintTree();
};
