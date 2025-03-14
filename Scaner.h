#pragma once
#include "defs.h"


class Scaner
{
private:
	IM t;		//�������� �����
	int uk;		//��������� ������� ������� � �������� ������

	int line_number;		//������
	int position;		//�������

public:
	void PutUK(int i);
	int GetUK();

	void Set_Position(int n);
	void Set_Line_Number(int n);
	void New_Line();
	int Get_Number_Line();
	int Get_Position();

	void PrintError(string, string, char);
	void PrintError(string);
	void PrintError(string, string);
	int FScaner(LEX lex);
	void GetData(string);

	Scaner(string);	//�����������
	~Scaner() {}		//����������
};
