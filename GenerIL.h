#pragma once
#include "Triada.h"
#include "Semantika.h"
#include "Translate.h"
#include <deque>

class GenerIL
{
private:
	Tree* root;
	GlobalData* global; 
	ofstream file;

	void generatePublic(Tree* node);
	void generateDecl(Tree* node);

	int countClassSize(Tree* node, int offset);

public:
	GenerIL(Tree* root, GlobalData* global);

	void saveOperator(int operation);

	void deltaGener(int operation);
	void deltaGenerUnar(int operation);
	void deltaPushType();
	void deltaPushRes(Operand result);
	void deltaSetAddr();
	void deltaGenerIf();
	void deltaFormIf();
	void deltaGenerGoto();
	void deltaFormGoto();
	void deltaGenerNop();
	void deltaGenerCall();
	void deltaGenerReturn();
	void deltaStartFunc();
	void deltaEndFunc();
	void deltaMatch();
	void deltaMatchLeft();
	void deltaMatchBool();
	void deltaPushConstType();

	Operand R(int operand);
	Operand R();

	int genMatch(DATA_TYPE first, DATA_TYPE result);
	Operand currentLink();
	void needBoolType(Operand operand);
	string operationToSymbols(int operation);

	void printTriadaCode();
	void generateCode();
};
