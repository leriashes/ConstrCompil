#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>		//������ � �������

using namespace std;

#define MAX_TEXT 100000     //������������ ����� ������ ��
#define MAX_LEX 100         //������������ ����� �������
#define MAX_KEYW 9			//����� �������� ����
#define MAX_CONST 10		//����� ���������

typedef char IM[MAX_TEXT];   //����� ��
typedef char LEX[MAX_LEX];   //�������

//�������� �����
#define TBool		1
#define TDouble     2
#define TIf			3
#define TElse		4
#define TMain		5
#define TReturn		6
#define TTrue		7
#define TFalse		8
#define TClass		9

//��������������
#define TIdent      10

//���������
#define TConstInt		20
#define TConstFloat		21

//����������� �����
#define TTochka     30	//.
#define TZapya		31	//,
#define TTochkaZap  32	//;
#define TLS         33	//(
#define TRS			34	//)
#define TFLS        35	//{
#define TFRS        36	//}

//����� ��������
#define TOR			40	//|
#define TLT         41	//<
#define TLE         42	//<=
#define TGT         43	//>
#define TGE         44	//>=
#define TEQ         45	//==
#define TNEQ        46	//!=
#define TPlus       47	//+
#define TMinus      48	//-
#define TXOR	    49	//^
#define TAnd	    50	//&
#define TSave       51	//=
#define TMult       52	//*
#define TDiv        53	///
#define TMod        54	//%

//����� ��������� ������
#define TEnd        70

//��������� ������
#define TError      71

#define MaxTypeTerminal TError

//�����������
#define neterm_S	1000
#define neterm_A	1001
#define neterm_A1	1002
#define neterm_D	1003
#define neterm_T	1004
#define neterm_E	1005
#define neterm_E1	1006
#define neterm_L	1007
#define neterm_I	1008
#define neterm_G	1009
#define neterm_F	1010
#define neterm_K	1011
#define neterm_J	1012
#define neterm_M	1013
#define neterm_M1	1014
#define neterm_H	1015
#define neterm_N	1016
#define neterm_O	1017
#define neterm_N1	1018
#define neterm_Q	1019
#define neterm_Q1	1020
#define neterm_R	1021
#define neterm_R1	1022
#define neterm_U	1023
#define neterm_U1	1024
#define neterm_V	1025
#define neterm_V1	1026
#define neterm_W	1027
#define neterm_W1	1028
#define neterm_X	1029
#define neterm_X1	1030
#define neterm_Y	1031
#define neterm_Y1	1032
#define neterm_Z	1033
#define neterm_Z1	1034
#define neterm_P	1035
#define neterm_B	1036
#define neterm_B1	1037
#define neterm_C	1038
