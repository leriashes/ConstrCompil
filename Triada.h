#pragma once
#include "defs.h"

struct Operand
{
	LEX lex; //непосред. операнд
	int number; //номер триады-ссылки
	bool isLink; //является ли ссылкой
	bool isConst; //константа
};

struct Triada
{
	int operation; //операция
	Operand operand1, operand2; //операнды
};
