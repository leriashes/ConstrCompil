#pragma once
#include "Semantika.h"

struct GlobalData
{
	LEX prevLex;
	LEX className;
	DATA_TYPE dataType;
};

class Translate
{
	Tree* root;
	GlobalData* global;

public:
	Translate(Scaner* scan);
	~Translate();
	void PrintTree();
	void CleanTree();

	void SaveLex(LEX lex);

	void deltaStartDeclare(int lexType);
	void deltaSetIdent();
	void deltaFindVar();
	void deltaSetFunct();
	void deltaReturnLevel();
	void deltaSetNewLevel();
	void deltaSetClass();
	void deltaFindFunct();
	void deltaFindClass();
};
