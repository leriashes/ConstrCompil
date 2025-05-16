#pragma once
#include "defs.h"
#include "Semantika.h"

struct Operand
{
	LEX lex; //непосред. операнд
	int number; //номер триады-ссылки
	bool isLink; //является ли ссылкой
	bool isConst; //константа
	Tree* node;
};

struct Triada
{
	int operation; //операция
	Operand operand1, operand2; //операнды
};
