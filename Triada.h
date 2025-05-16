#pragma once
#include "defs.h"
#include "Semantika.h"

struct Operand
{
	LEX lex; //��������. �������
	int number; //����� ������-������
	bool isLink; //�������� �� �������
	bool isConst; //���������
	Tree* node;
};

struct Result
{
	string nameResult; //��� �������� ��� ������� ������
	bool flagRegister; //������� �������� ���������� � ��������
};

struct Triada
{
	int operation; //��������
	Operand operand1, operand2; //��������
	Result result; //���������� � ����������
};
