#include "GenerIL.h"

void GenerIL::generatePublic(Tree* node)
{
	if ((node->GetObjType() == ObjVar || node->GetObjType() == ObjFunct || node->GetObjType() == ObjObjectCl) && node->GetLevel() == 0)
	{
		file << "PUBLIC " + node->GenPublicName() << endl;
	}

	if (node->GetLeft() != NULL)
	{
		generatePublic(node->GetLeft());
	}
}

void GenerIL::generateDecl(Tree* node)
{
	if (node->GetObjType() == ObjVar && node->GetLevel() == 0)
	{
		file << node->GenPublicDecl() << endl;
	}
	else if (node->GetObjType() == ObjObjectCl && node->GetLevel() == 0)
	{
		int len = countClassSize(node->GetRight()->GetLeft(), 0);

		if (len > 0)
			node->SetSize(DB, len);
		else
			node->SetSize(DB, 1);

		file << node->GenPublicDecl() << endl;
	}

	if (node->GetLeft() != NULL)
	{
		generateDecl(node->GetLeft());
	}
}

void GenerIL::generateFunctions(Tree* node)
{
	if (node->GetObjType() == ObjFunct && node->GetLevel() == 0)
	{
		file << endl << "_TEXT SEGMENT" << endl;
		file << node->GetAsmId() << " PROC" << endl;
		file << node->GetAsmId() << " ENDP" << endl;
		file << "_TEXT ENDS" << endl;
	}

	if (node->GetLeft() != NULL)
	{
		generateFunctions(node->GetLeft());
	}
}

int GenerIL::countClassSize(Tree* node, int offset)
{
	int t = 0;

	if (node != NULL)
	{
		if (node->GetObjType() == ObjVar || node->GetObjType() == ObjObjectCl)
		{
			if (node->GetObjType() == ObjObjectCl)
			{
				int len = countClassSize(node->GetRight()->GetLeft(), 0);

				if (len > 0)
					node->SetSize(DB, len);
				else
					node->SetSize(DB, 1);
			}

			t = node->GetSize();
			if (offset % node->GetSize() != 0)
			{
				int delta = node->GetSize() - (offset % node->GetSize());
				t += delta;
			}
			offset += t;
			
		}
			
		t += countClassSize(node->GetLeft(), offset);
	}

	return t;
}

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

	global->code[addr].operand1.number = global->k;
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

	if (global->operation.size() != 0)
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
		root->scan->PrintError("Объект является экземпляром класса - недопустимо проведение операции", "\0", '\0');

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
		needBoolType(operand2);
	}

	global->res.pop_back();

	Operand operand1 = global->res.back();

	if (first != TYPE_BOOL)
	{
		needBoolType(operand1);
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

void GenerIL::deltaPushConstType()
{
	global->t.push_back(global->constType);
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
	else if (operand == TTrue)
	{
		result.isConst = true;
		result.isLink = false;
		memcpy(result.lex, "1", 3);
	}
	else if (operand == TFalse)
	{
		result.isConst = true;
		result.isLink = false;
		memcpy(result.lex, "0", 3);
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

	Tree* var = root->FindUp(root->GetCur(), global->prevLex);

	if (var != nullptr && var->GetObjType() == ObjVar)
	{
		var->GetAsmId(&result.lex);
	}

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

void GenerIL::needBoolType(Operand operand)
{
	if (!operand.isLink)
	{
		root->scan->PrintError("Выражение должно относиться к целочисленному типу", operand.lex);
	}
	else
	{
		root->scan->PrintError("Выражение должно относиться к целочисленному типу");
	}
}

string GenerIL::operationToSymbols(int operation)
{
	switch (operation)
	{
	case TSave:
		return "=";

	case TEQ:
		return "==";

	case TNEQ:
		return "!=";

	case TLT:
		return "<";

	case TGT:
		return ">";

	case TLE:
		return "<=";

	case TGE:
		return ">=";

	case TOR:
		return "|";

	case TXOR:
		return "^";

	case TAnd:
		return "&";

	case TPlus:
		return "+";

	case TMinus:
		return "-";

	case TMult:
		return "*";

	case TDiv:
		return "/";

	case TMod:
		return "%";

	case boolToDouble:
		return "bool->double";

	case doubleToBool:
		return "double->bool";

	case ifOper:
		return "if";

	case gotoOper:
		return "goto";

	case nopOper:
		return "nop";

	case callOper:
		return "call";

	case procOper:
		return "proc";

	case prologOper:
		return "prolog";

	case epilogOper:
		return "epilog";

	case retOper:
		return "ret";

	case endpOper:
		return "endp";

	case returnOper:
		return "return";

	default:
		return "UNKNOWN_OPERATION";
	}
}

void GenerIL::printTriadaCode()
{
	cout << "\n\nТРИАДЫ\n";

	for (int i = 0; i < global->k; i++)
	{
		Triada triada = global->code[i];

		cout << i + 1 << ") " << operationToSymbols(triada.operation) << " ";

		if (triada.operation < prologOper)
		{
			if (triada.operand1.isLink)
				cout << "(" << triada.operand1.number + 1 << ") ";
			else
				cout << triada.operand1.lex << " ";

			if (triada.operation < boolToDouble || triada.operation == ifOper)
			{
				if (triada.operand2.isLink)
					cout << "(" << triada.operand2.number + 1 << ") ";
				else
					cout << triada.operand2.lex << " ";
			}
		}

		cout << endl;
	}
}

void GenerIL::generateCode()
{
	int level = 0;
	root->SetLevel(level);

	file = ofstream("prog.asm");

	if (file.is_open()) {
		file << "_BSS SEGMENT" << endl;

		generatePublic(root);
		file << endl;

		generateDecl(root);
		file << endl;

		generateFunctions(root);

		file.close();
	}
	else {
		std::cerr << "Не удалось открыть файл!" << std::endl;
	}
}
