#pragma once
#include "Semantika.h"
#include <deque>
#include "Scaner.h"
#include "Triada.h"

#define MAXCODE 1000

struct GlobalData
{
	LEX prevLex;
	LEX className;
	DATA_TYPE dataType;
	DATA_TYPE constType;

	int k;
	bool obj;
	deque<DATA_TYPE> t;
	Triada code[MAXCODE];
	deque<Operand> res;
	deque<int> addr;

	deque<int> operation;
};

class Translate
{
	Tree* root;
	GlobalData* global;

public:
	Translate(Tree* root, GlobalData* global);
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
	void deltaConstType(int constTerm);
};
