#include "GenerIL.h"

GenerIL::GenerIL(Tree* root, GlobalData* global)
{
	this->root = root;
	this->global = global;
}

void GenerIL::saveOperator(int operation)
{
	global->operation.push_back(operation);
}

void GenerIL::deltaGener(int operation)
{
	Triada triada;

	triada.operand2 = global->res.back();
	global->res.pop_back();
	global->t.pop_back();

	triada.operand1 = global->res.back();
	global->res.pop_back();

	triada.operation = operation;

	if (global->operation.size() != 1)
	{
		global->res.push_back(currentLink());
	}
	else
	{
		global->t.pop_back();
	}

	global->code[global->k++] = triada;
}

void GenerIL::deltaGenerUnar(int operation)
{
	if (operation == TMinus)
	{
		Triada triada;

		triada.operand2 = global->res.back();
		global->res.pop_back();

		triada.operand1.isConst = true;
		triada.operand1.isLink = false;
		memcpy(triada.operand1.lex, "0", strlen("0") + 1);

		triada.operation = operation;

		if (global->operation.size() != 1)
		{
			global->res.push_back(currentLink());
		}
		else
		{
			global->t.pop_back();
		}

		global->code[global->k++] = triada;
	}
}

void GenerIL::deltaPushType()
{
	global->t.push_back(global->dataType);
}

void GenerIL::deltaPushRes(Operand result)
{
	global->res.push_back(result);
}

void GenerIL::deltaSetAddr()
{
	global->addr.push_back(global->k);
}

void GenerIL::deltaGenerIf()
{
	Triada triada;

	triada.operand1.number = global->k + 1;
	triada.operand1.isLink = true;

	triada.operation = ifOper;

	global->code[global->k++] = triada;
}

void GenerIL::deltaFormIf()
{
	int addr = global->addr.back() - 1;

	global->addr.pop_back();

	global->code[addr].operand2.number = global->k + 1;
	global->code[addr].operand2.isLink = true;
}

void GenerIL::deltaGenerGoto()
{
	Triada triada;

	triada.operation = gotoOper;

	global->code[global->k++] = triada;
}

void GenerIL::deltaFormGoto()
{
	int addr = global->addr.back() - 1;

	global->addr.pop_back();

	global->code[addr].operand1.number = global->k + 1;
	global->code[addr].operand1.isLink = true;
}

void GenerIL::deltaGenerNop()
{
	Triada triada;

	triada.operation = nopOper;

	global->code[global->k++] = triada;
}

void GenerIL::deltaGenerCall()
{
	Triada triada;

	triada.operand1 = global->res.back();
	global->res.pop_back();

	triada.operation = callOper;

	if (global->operation.size() != 1)
	{
		global->res.push_back(currentLink());
	}
	else
	{
		global->t.pop_back();
	}

	global->code[global->k++] = triada;
}

void GenerIL::deltaGenerReturn()
{
	Triada triada;

	triada.operand1 = global->res.back();
	global->res.pop_back();
	global->res.pop_back();
	global->t.pop_back();
	global->t.pop_back();

	triada.operation = returnOper;

	global->code[global->k++] = triada;
}

void GenerIL::deltaStartFunc()
{
	Triada triada;

	triada.operand1 = global->res.back();
	triada.operation = procOper;

	global->code[global->k++] = triada;

	triada.operation = prologOper;
	global->code[global->k++] = triada;
}

void GenerIL::deltaEndFunc()
{
	Triada triada;

	triada.operation = epilogOper;
	global->code[global->k++] = triada;

	triada.operation = retOper;
	global->code[global->k++] = triada;

	triada.operation = endpOper;
	global->code[global->k++] = triada;
}

void GenerIL::deltaMatch()
{
	DATA_TYPE second = global->t.back();
	global->t.pop_back();

	DATA_TYPE first = global->t.back();
	global->t.pop_back();

	DATA_TYPE resType = first;

	if (first == TYPE_OBJ_CL || second == TYPE_OBJ_CL)
		root->scan->PrintError("Îáúåêò ÿâëÿåòñÿ ıêçåìïëÿğîì êëàññà - íåäîïóñòèìî ïğîâåäåíèå îïåğàöèè", "\0", '\0');

	if (first != second)
	{
		if (first == NO_TYPE || second == NO_TYPE)
			resType = NO_TYPE;
		else if (first == TYPE_DOUBLE || second == TYPE_DOUBLE)
			resType = TYPE_DOUBLE;
		else
			resType = TYPE_BOOL;

		if (first != resType)
		{
			int operation = genMatch(first, resType);

			Triada triada;

			Operand operand2 = global->res.back();
			global->res.pop_back();

			triada.operand1 = global->res.back();
			global->res.pop_back();

			global->res.push_back(currentLink());
			global->res.push_back(operand2);

			triada.operation = operation;

			global->code[global->k++] = triada;
		}
		else if (second != resType)
		{
			int operation = genMatch(second, resType);

			Triada triada;

			triada.operand1 = global->res.back();
			global->res.pop_back();

			Operand operand1 = global->res.back();
			global->res.pop_back();

			global->res.push_back(operand1);
			global->res.push_back(currentLink());

			triada.operation = operation;

			global->code[global->k++] = triada;
		}
	}

	global->t.push_back(resType);
	global->t.push_back(resType);
}

void GenerIL::deltaMatchLeft()
{
	DATA_TYPE second = global->t.back();
	global->t.pop_back();

	DATA_TYPE first = global->t.back();
	global->t.pop_back();

	DATA_TYPE resType = first;

	if (first != second)
	{
		int operation = genMatch(second, resType);

		Triada triada;

		triada.operand1 = global->res.back();
		global->res.pop_back();

		Operand operand1 = global->res.back();
		global->res.pop_back();

		global->res.push_back(operand1);
		global->res.push_back(currentLink());

		triada.operation = operation;

		global->code[global->k++] = triada;
	}

	global->t.push_back(resType);
	global->t.push_back(resType);
}

void GenerIL::deltaMatchBool()
{
	DATA_TYPE second = global->t.back();
	global->t.pop_back();

	DATA_TYPE first = global->t.back();
	global->t.pop_back();

	Operand operand2 = global->res.back();

	if (second != TYPE_BOOL)
	{
		needIntType(operand2);
	}

	global->res.pop_back();

	Operand operand1 = global->res.back();

	if (first != TYPE_BOOL)
	{
		needIntType(operand1);
	}

	global->res.push_back(operand2);

	DATA_TYPE resType = TYPE_BOOL;

	if (first != resType)
	{
		int operation = genMatch(first, resType);

		Triada triada;

		global->res.pop_back();

		triada.operand1 = operand1;
		global->res.pop_back();

		global->res.push_back(currentLink());
		global->res.push_back(operand2);

		triada.operation = operation;

		global->code[global->k++] = triada;
	}
	else if (second != resType)
	{
		int operation = genMatch(second, resType);

		Triada triada;

		triada.operand1 = operand2;
		global->res.pop_back();
		global->res.pop_back();

		global->res.push_back(operand1);
		global->res.push_back(currentLink());

		triada.operation = operation;

		global->code[global->k++] = triada;
	}

	global->t.push_back(resType);
	global->t.push_back(resType);
}

Operand GenerIL::R(int operand)
{
	Operand result;

	if (operand == TConstInt || operand == TConstFloat)
	{
		result.isConst = true;
		result.isLink = false;
		memcpy(result.lex, global->prevLex, strlen(global->prevLex) + 1);
	}
	else
	{
		result.isConst = false;
		result.isLink = true;
		result.number = global->k - 1;
	}

	return result;
}

Operand GenerIL::R()
{
	Operand result;

	result.isConst = false;
	result.isLink = false;
	memcpy(result.lex, global->prevLex, strlen(global->prevLex) + 1);

	return result;
}

int GenerIL::genMatch(DATA_TYPE first, DATA_TYPE result)
{
	int res = 0;

	if (first == TYPE_BOOL)
	{
		if (result == TYPE_DOUBLE)
		{
			res = boolToDouble;
		}
	}
	else if (first == TYPE_DOUBLE)
	{
		if (result == TYPE_BOOL)
		{
			res = doubleToBool;
		}
	}

	return res;
}

Operand GenerIL::currentLink()
{
	Operand link;

	link.isLink = true;
	link.isConst = false;
	link.number = global->k;

	return link;
}
