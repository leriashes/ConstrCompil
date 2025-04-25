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
	root->SemGetVar(global->prevLex);
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
	root->SemGetFunct(global->prevLex);
}

void Translate::deltaFindClass()
{
	root->SemGetClass(global->prevLex);
	memcpy(global->className, global->prevLex, strlen(global->prevLex) + 1);
}

void Translate::deltaConstType(int constTerm)
{
	global->dataType = root->SemGetVar(global->prevLex)->GetType();
}
