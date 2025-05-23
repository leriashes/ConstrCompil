#pragma once
#include "Triada.h"
#include "Semantika.h"
#include "Translate.h"
#include <deque>
#include <vector>
#include <map>

typedef pair<string, bool> RegInfo;


class GenerIL
{
private:
	Tree* root;
	GlobalData* global; 
	ofstream file;
	int pc;
	vector<RegInfo> intReg; 
	map<string, int> regToTriad;

	void generatePublic(Tree* node);
	void generateDecl(Tree* node);
	void generateFunctions();
	void generateLocals(Tree* node, int* offs);
	void generateCommands();

	int countLocals(Tree* node, int offs);
	int countClassSize(Tree* node, int offset);
	string getOperand(Operand operand);

	void initRegisters();
	string getIntReg();
	void freeIntReg(string reg_name); 
	void reservIntReg(string reg_name);

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
