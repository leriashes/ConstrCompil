#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>		//Работа с файлами

using namespace std;

#define MAX_TEXT 100000     //макисмальная длина текста ИМ
#define MAX_LEX 100         //максимальная длина лексемы
#define MAX_KEYW 9			//число ключевых слов
#define MAX_CONST 10		//Длина константы

typedef char IM[MAX_TEXT];   //текст ИМ
typedef char LEX[MAX_LEX];   //лексема

//ключевые слова
#define TBool		1
#define TDouble     2
#define TIf			3
#define TElse		4
#define TMain		5
#define TReturn		6
#define TTrue		7
#define TFalse		8
#define TClass		9

//идентификаторы
#define TIdent      10

//константы
#define TConstInt		20
#define TConstFloat		21

//специальные знаки
#define TTochka     30	//.
#define TZapya		31	//,
#define TTochkaZap  32	//;
#define TLS         33	//(
#define TRS			34	//)
#define TFLS        35	//{
#define TFRS        36	//}

//знаки операций
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

//конец исходного модуля
#define TEnd        70

//ошибочный символ
#define TError      71

#define MaxTypeTerminal TError

//нетерминалы
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

#define MaxTypeNeterminal		neterm_C

//операционные символы (семантика)
#define sem_startDeclare		1100
#define sem_setIdent			1101
#define sem_findVar				1102
#define sem_setFunct			1103
#define sem_returnLevel			1104
#define sem_setNewLevel			1105
#define sem_setClass			1106
#define sem_findFunct			1107
#define sem_findClass			1108
#define sem_constType			1109
#define sem_checkObject			1110

#define sem_match				1120
#define sem_matchLeft			1121
#define sem_matchBool			1122
#define sem_push				1123
#define sem_gener				1124	
#define sem_generIf				1125
#define sem_formIf				1126
#define sem_generGoto			1127
#define sem_formGoto			1128
#define sem_generNop			1129
#define sem_setAddr				1130
#define sem_generCall			1131
#define sem_startFunc			1132
#define sem_endFunc				1133
#define sem_generReturn			1134
#define sem_generUnar			1135

#define MaxTypeSem				sem_generUnar

#define ifOper					1200

#define boolToDouble			1210
#define doubleToBool			1211

#define callOper				1220
#define returnOper				1221
#define gotoOper				1222
#define procOper				1223

#define prologOper				1230
#define epilogOper				1231
#define retOper					1232
#define endpOper				1233
#define nopOper					1234
