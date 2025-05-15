#include "Translate.h"

Translate::Translate(Tree* root, GlobalData* global)
{
	this->root = root;
	this->global = global;
}

Translate::~Translate()
{
	delete root;
	delete global;
}

void Translate::PrintTree()
{
	root->Print();
}

void Translate::CleanTree()
{
	root->CleanTree();
}

void Translate::SaveLex(LEX lex)
{
	memcpy(global->prevLex, lex, strlen(lex) + 1);
}

void Translate::deltaStartDeclare(int lexType)
{
	global->dataType = root->GetTypebyLex(lexType);
}

void Translate::deltaSetIdent()
{
	if (global->dataType == TYPE_OBJ_CL)
	{
		root->SemInclude(global->prevLex, ObjObjectCl, TYPE_OBJ_CL, global->className);
	}
	else
	{
		root->SemInclude(global->prevLex, ObjVar, global->dataType);
	}
}

void Translate::deltaFindVar()
{
	if (global->obj)
	{
		global->obj = false;
		global->dataType = root->FindRightLeftVar(global->prevLex)->GetType();
	}
	else
	{
		global->dataType = root->SemGetVar(global->prevLex)->GetType();
	}
}

void Translate::deltaSetFunct()
{
	if (global->dataType == TYPE_OBJ_CL)
	{
		root->SemInclude(global->prevLex, ObjFunct, TYPE_OBJ_CL, global->className);
	}
	else
	{
		root->SemInclude(global->prevLex, ObjFunct, global->dataType);
	}
}

void Translate::deltaReturnLevel()
{
	root->SemReturnLevel();
}

void Translate::deltaSetNewLevel()
{
	root->SemNewLevel();
}

void Translate::deltaSetClass()
{
	root->SemInclude(global->prevLex, ObjClass, NO_TYPE);
}

void Translate::deltaFindFunct()
{
	if (global->obj)
	{
		global->obj = false;
		global->dataType = root->FindRightLeftFunct(global->prevLex)->GetType();

	}
	else
	{
		global->dataType = root->SemGetFunct(global->prevLex)->GetType();
	}
}

void Translate::deltaFindClass()
{
	root->SemGetClass(global->prevLex);
	memcpy(global->className, global->prevLex, strlen(global->prevLex) + 1);
}

void Translate::deltaConstType(int constTerm)
{
	if (constTerm == TConstInt || constTerm == TTrue || constTerm == TFalse)
		global->constType = TYPE_BOOL;
	else
		global->constType = TYPE_DOUBLE;
}
