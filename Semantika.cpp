#include "Semantika.h"

Tree* Tree::cur = (Tree*)NULL;
Scaner* Tree::scan = (Scaner*)NULL;
Tree* Tree::lastcur = (Tree*)NULL;

Tree::Tree(Scaner* scan)
{
	this->scan = scan;

	node = new Node();
	node->objType = Empty;
	node->data.dataType = NO_TYPE;

	parent = NULL;
	left = NULL;
	right = NULL;

	lastcur = this;
	cur = this;
}

Tree::Tree(Node* data, Tree* parent)
{
	node = new Node();
	this->parent = parent;

	memcpy(node, data, sizeof(Node));
}

Tree::Tree(Tree* p, Tree* l, Tree* r, Node* data)
{
	node = new Node();

	parent = p;
	left = l;
	right = r;

	memcpy(node, data, sizeof(Node));
}

void Tree::SetLeft(Node* data)
{
	left = new Tree(this, NULL, NULL, data);
}

void Tree::SetRight(Node* data)
{
	right = new Tree(this, NULL, NULL, data);
}

void Tree::SetStart(int uk, int line, int pos)
{
	node->funcStart.uk = uk;
	node->funcStart.line = line;
	node->funcStart.pos = pos;
}

FStart Tree::GetStart()
{
	return node->funcStart;
}

void Tree::SetRightT(Tree* node)
{
	right = node;
}

Tree* Tree::GetRight()
{
	return right;
}

Tree* Tree::FindUp(Tree* from, LEX id)
{
	Tree* i = from;

	while ((i != NULL) && memcmp(id, i->node->id, max(strlen(i->node->id), strlen(id))) != 0)
		i = i->parent;

	return i;
}

Tree* Tree::FindRoot()
{
	Tree* i = cur;

	while ((i != NULL) && (i->parent != NULL))
		i = i->parent;

	return i;
}

Tree* Tree::FindUp(LEX id)
{
	return FindUp(this, id);
}

Tree* Tree::FindUpOneLevel(Tree* from, LEX id)
{
	Tree* i = from;		//������� ������� ������

	while ((i != NULL) && (i->parent == NULL || i->parent->right != i))
	{
		if (memcmp(id, i->node->id, max(strlen(i->node->id), strlen(id))) == 0)
			return i;	//������ ����������� �������������

		i = i->parent;
	}

	return NULL;
}

Tree* Tree::FindRightLeft(Tree* from, LEX id)
{
	Tree* i = from->right;
	while ((i != NULL) && (memcmp(id, i->node->id, max(strlen(i->node->id), strlen(id))) != 0))
		i = i->left;
	return i;
}

Tree* Tree::FindRightLeftVar(LEX id)
{
	Tree* v = FindRightLeft(this, id);

	if (v == NULL)
	{
		Tree* root = FindRoot();
		root->Print();
		scan->PrintError("����������� �������� ��������������");
	}

	if (v->node->objType == ObjFunct)
	{
		Tree* root = FindRoot();
		root->Print();
		scan->PrintError("�������� ������������� ����� �������");
	}

	if (v->node->objType == ObjClass)
	{
		Tree* root = FindRoot();
		root->Print();
		scan->PrintError("�������� ������������� ����� ������");
	}

	return v;
}

Tree* Tree::FindRightLeftFunct(LEX id)
{
	Tree* v = FindRightLeft(this, id);

	if (v == NULL)
	{
		Tree* root = FindRoot();
		root->Print();
		scan->PrintError("����������� �������� ������");
	}

	if (v->node->objType != ObjFunct)
	{
		Tree* root = FindRoot();
		root->Print();
		scan->PrintError("������������� �� �������� ������ ������");
	}

	return v;
}

void Tree::CleanTree()
{
	if (left != NULL)
	{
		left->CleanTree();
		delete left;
		left = NULL;
	}

	CleanChild();
}

void Tree::CleanChild()
{
	if (right != NULL)
	{
		right->CleanTree();
		delete right;
		right = NULL;
	}
}

void Tree::Print()
{
	if (node->objType != Empty)
		printf("������� � ������� %s ------>", node->id);
	else
		printf("������� ������ ------>");

	if (left != NULL)
	{
		if (left->node->objType != Empty)
			printf("      ����� ������ %s", left->node->id);
		else
			printf("      ����� ������ �������");
	}


	if (right != NULL)
	{
		if (right->node->objType != Empty)
			printf("      ������ ������ %s", right->node->id);
		else
			printf("      ������ ������ �������");
	}

	printf("\n");

	if (left != NULL)
		left->Print();

	if (right != NULL)
	{
		printf("\n\n��������: ");
		if (node->objType != Empty)
			printf("������� %s\n", node->id);
		else
			printf("������� ������\n");
		right->Print();
	}
}

void Tree::SetCur(Tree* a)
{
	cur = a;
}

Tree* Tree::GetCur()
{
	return cur;
}

Tree* Tree::SemInclude(Tree* first)
{
	if (!flagInterpret) return NULL;

	if (first->node->objType == ObjFunct)
	{
		Tree* v;
		Node n;

		memcpy(n.id, first->node->id, strlen(first->node->id) + 1);
		n.objType = first->node->objType;
		n.data.dataType = first->node->data.dataType;
		n.funcStart = first->node->funcStart;
		memcpy(n.data.className, "", strlen("") + 1);

		if (this->node->objType == Empty && this->parent == NULL && this->left == NULL && this->right == NULL)
			memcpy(node, &n, sizeof(Node));
		else
		{
			Tree* lastleft = first->left;
			first->SetLeft(&n);
			lastcur = cur;
			cur = first->left;
			cur->left = lastleft;
		}

		v = cur;
		memcpy(&n.id, &"", 2);
		n.objType = Empty;

		cur->SetRight(&n);
		cur = cur->right;
		return v;
	}
	else
		return NULL;
}

Tree* Tree::SemInclude(LEX a, OBJ_TYPE ot, DATA_TYPE t)
{
	if (!flagInterpret) return NULL;

	if (DupControl(cur, a))
	{
		Tree* root = FindRoot();
		root->Print();
		scan->PrintError("��������� �������� ��������������");
	}

	Tree* v;
	Node n;

	memcpy(n.id, a, strlen(a) + 1);
	n.objType = ot;
	n.data.dataType = t;
	memcpy(n.data.className, "", strlen("") + 1);

	if (this->node->objType == Empty && this->parent == NULL && this->left == NULL && this->right == NULL)
		memcpy(node, &n, sizeof(Node));
	else
	{
		cur->SetLeft(&n);
		cur = cur->left;
	}

	if (ot == ObjFunct || ot == ObjClass)
	{
		v = cur;
		memcpy(&n.id, &"", 2);
		n.objType = Empty;

		cur->SetRight(&n);
		cur = cur->right;
		return v;
	}

	return cur;
}

Tree* Tree::SemInclude(LEX a, OBJ_TYPE ot, DATA_TYPE t, LEX className)
{
	if (!flagInterpret) return NULL;

	if (DupControl(cur, a))
	{
		Tree* root = FindRoot();
		root->Print();
		scan->PrintError("��������� �������� ��������������");
	}

	Tree* v;
	Node n;


	memcpy(n.id, a, strlen(a) + 1);
	n.objType = ot;
	n.data.dataType = t;
	memcpy(n.data.className, className, strlen(className) + 1);

	if (this->node->objType == Empty && this->parent == NULL && this->left == NULL && this->right == NULL)
		memcpy(node, &n, sizeof(Node));
	else
	{
		cur->SetLeft(&n);
		cur = cur->left;
	}

	if (ot == ObjFunct || ot == ObjClass)
	{
		v = cur;
		memcpy(&n.id, &"", 2);
		n.objType = Empty;

		cur->SetRight(&n);
		cur = cur->right;
		return v;
	}

	return cur;
}

Tree* Tree::SemGetVar(LEX a)
{
	Tree* v = FindUp(cur, a);

	if (v == NULL)
	{
		Tree* root = FindRoot();
		root->Print();
		scan->PrintError("����������� �������� ��������������");
	}

	if (v->node->objType == ObjFunct)
	{
		Tree* root = FindRoot();
		root->Print();
		scan->PrintError("�������� ������������� ����� �������");
	}

	if (v->node->objType == ObjClass)
	{
		Tree* root = FindRoot();
		root->Print();
		scan->PrintError("�������� ������������� ����� ������");
	}

	return v;
}

Tree* Tree::SemNewLevel()
{
	Node n;

	memcpy(&n.id, &"", 2);
	n.objType = Empty;

	cur->SetLeft(&n);
	cur = cur->left;
	Tree* v = cur;

	cur->SetRight(&n);
	cur = cur->right;

	return v;
}

Tree* Tree::SemReturnLevel()
{
	if (!flagInterpret) return NULL;

	if (cur->parent == NULL or cur->parent->right == cur)
	{
		cur = cur->parent;
		return cur;
	}

	cur = cur->parent;
	return SemReturnLevel();
}

Tree* Tree::SemGetFunct(LEX a)
{
	Tree* v = FindUp(cur, a);

	if (v == NULL)
	{
		Tree* root = FindRoot();
		root->Print();
		scan->PrintError("����������� �������� �������");
	}

	if (v->node->objType != ObjFunct)
	{
		Tree* root = FindRoot();
		root->Print();
		scan->PrintError("������������� �� �������� ������ �������");
	}

	return v;
}

Tree* Tree::SemGetClass(LEX a)
{
	Tree* v = FindUp(cur, a);

	if (v == NULL)
	{
		Tree* root = FindRoot();
		root->Print();
		scan->PrintError("����������� �������� ������");
	}

	if (v->node->objType != ObjClass)
	{
		Tree* root = FindRoot();
		root->Print();
		scan->PrintError("������������� �� �������� ������ ������");
	}

	return v;
}

int Tree::DupControl(Tree* addr, LEX a)
{
	if (FindUpOneLevel(addr, a) == NULL) return 0;
	return 1;
}

void Tree::MakeClassCopy(Tree* clss)
{
	if (!flagInterpret) return;

	if (clss->right != NULL)
	{
		this->right = new Tree(clss->right->node, this);

		this->right->MakeChildCopy(clss->right);
	}
}

void Tree::MakeChildCopy(Tree* source)
{
	if (source->left != NULL)
	{
		this->left = new Tree(source->left->node, this);

		this->left->MakeChildCopy(source->left);
	}

	if (source->right != NULL)
	{
		this->right = new Tree(source->right->node, this);

		this->right->MakeChildCopy(source->right);
	}
}

DATA_TYPE Tree::GetTypebyLex(int lexType)
{
	if (lexType == TBool)
		return TYPE_BOOL;
	
	if (lexType == TDouble)
		return TYPE_DOUBLE;

	return TYPE_OBJ_CL;
}

DATA_TYPE Tree::GetType()
{
	return node->data.dataType;
}

void Tree::GetClassName(LEX name)
{
	strcpy(name, node->data.className);
}

DATA_VALUE* Tree::GetValue()
{
	return &(node->data.dataValue);
}

Tree* Tree::GetCurrentFunct()
{
	if (parent == NULL)
		return NULL;

	if (node->objType == Empty && parent->node->objType == ObjFunct && parent->right == this)
		return parent;

	return parent->GetCurrentFunct();
}

void Tree::TypeCasting(DataS* firstData, DataS secondData, int operation, LEX operationName)
{
	if (!flagInterpret) return;

	DATA_TYPE resType = firstData->dataType;

	if (firstData->dataType == TYPE_OBJ_CL || secondData.dataType == TYPE_OBJ_CL)
		scan->PrintError("������ �������� ����������� ������ - ����������� ���������� ��������", "\0", '\0');

	if (resType != secondData.dataType)
	{
		if (resType == NO_TYPE || secondData.dataType == NO_TYPE)
			resType = NO_TYPE;
		else if (resType == TYPE_DOUBLE || secondData.dataType == TYPE_DOUBLE)
			resType = TYPE_DOUBLE;
		else if (resType == TYPE_BOOL || secondData.dataType == TYPE_BOOL)
			resType = TYPE_BOOL;
		else
			scan->PrintError("������ ���������� �����", "\0", '\0');
	}

	printf("\n���������� ����� %s � %s (%s) --> %s ------ ������ %d\n", DT_Name[firstData->dataType], DT_Name[secondData.dataType], operationName, DT_Name[resType], scan->Get_Number_Line());

	if (firstData->dataType != resType)
	{
		if (resType == TYPE_DOUBLE)
		{
			if (firstData->dataType == TYPE_BOOL)
			{
				firstData->dataValue.DataAsDouble = firstData->dataValue.DataAsBool;
			}
		}
		else
		{
			if (firstData->dataType == TYPE_DOUBLE)
			{
				firstData->dataValue.DataAsBool = firstData->dataValue.DataAsBool;
			}
		}
	}

	firstData->dataType = resType;

	if (resType == TYPE_DOUBLE)
	{
		if (secondData.dataType == TYPE_DOUBLE)
		{
			//L - ���������
			if (operation == TPlus)
				firstData->dataValue.DataAsDouble += secondData.dataValue.DataAsDouble;
			else if (operation == TMinus)
				firstData->dataValue.DataAsDouble -= secondData.dataValue.DataAsDouble;

			//M - ���������
			else if (operation == TMult)
				firstData->dataValue.DataAsDouble *= secondData.dataValue.DataAsDouble;
			else if (operation == TDiv)
				firstData->dataValue.DataAsDouble /= secondData.dataValue.DataAsDouble;

			//Z - ���������
			else if (operation == TLT)
			{
				firstData->dataValue.DataAsBool = firstData->dataValue.DataAsDouble < secondData.dataValue.DataAsDouble;
				firstData->dataType = TYPE_BOOL;
			}
			else if (operation == TGT)
			{
				firstData->dataValue.DataAsBool = firstData->dataValue.DataAsDouble > secondData.dataValue.DataAsDouble;
				firstData->dataType = TYPE_BOOL;
			}
			else if (operation == TLE)
			{
				firstData->dataValue.DataAsBool = firstData->dataValue.DataAsDouble <= secondData.dataValue.DataAsDouble;
				firstData->dataType = TYPE_BOOL;
			}
			else if (operation == TGE)
			{
				firstData->dataValue.DataAsBool = firstData->dataValue.DataAsDouble >= secondData.dataValue.DataAsDouble;
				firstData->dataType = TYPE_BOOL;
			}

			//V - ���������
			else if (operation == TEQ)
			{
				firstData->dataValue.DataAsBool = firstData->dataValue.DataAsDouble == secondData.dataValue.DataAsDouble;
				firstData->dataType = TYPE_BOOL;
			}
			else if (operation == TNEQ)
			{
				firstData->dataValue.DataAsBool = firstData->dataValue.DataAsDouble != secondData.dataValue.DataAsDouble;
				firstData->dataType = TYPE_BOOL;
			}
		}
		else if (secondData.dataType == TYPE_BOOL)
		{
			if (operation == TPlus)
				firstData->dataValue.DataAsDouble += secondData.dataValue.DataAsBool;
			else if (operation == TMinus)
				firstData->dataValue.DataAsDouble -= secondData.dataValue.DataAsBool;
			else if (operation == TMult)
				firstData->dataValue.DataAsDouble *= secondData.dataValue.DataAsBool;
			else if (operation == TDiv)
				firstData->dataValue.DataAsDouble /= secondData.dataValue.DataAsBool;

			else if (operation == TLT)
			{
				firstData->dataValue.DataAsBool = firstData->dataValue.DataAsDouble < secondData.dataValue.DataAsBool;
				firstData->dataType = TYPE_BOOL;
			}
			else if (operation == TGT)
			{
				firstData->dataValue.DataAsBool = firstData->dataValue.DataAsDouble > secondData.dataValue.DataAsBool;
				firstData->dataType = TYPE_BOOL;
			}
			else if (operation == TLE)
			{
				firstData->dataValue.DataAsBool = firstData->dataValue.DataAsDouble <= secondData.dataValue.DataAsBool;
				firstData->dataType = TYPE_BOOL;
			}
			else if (operation == TGE)
			{
				firstData->dataValue.DataAsBool = firstData->dataValue.DataAsDouble >= secondData.dataValue.DataAsBool;
				firstData->dataType = TYPE_BOOL;
			}

			else if (operation == TEQ)
			{
				firstData->dataValue.DataAsBool = firstData->dataValue.DataAsDouble == secondData.dataValue.DataAsBool;
				firstData->dataType = TYPE_BOOL;
			}
			else if (operation == TNEQ)
			{
				firstData->dataValue.DataAsBool = firstData->dataValue.DataAsDouble != secondData.dataValue.DataAsBool;
				firstData->dataType = TYPE_BOOL;
			}
		}
	}
	else if (resType == TYPE_BOOL)
	{
		if (secondData.dataType == TYPE_DOUBLE)
		{
			if (operation == TPlus)
				firstData->dataValue.DataAsBool += secondData.dataValue.DataAsDouble;
			else if (operation == TMinus)
				firstData->dataValue.DataAsBool -= secondData.dataValue.DataAsDouble;
			else if (operation == TMult)
				firstData->dataValue.DataAsBool *= secondData.dataValue.DataAsDouble;
			else if (operation == TDiv)
				firstData->dataValue.DataAsBool /= secondData.dataValue.DataAsDouble;

			else if (operation == TLT)
			{
				firstData->dataValue.DataAsBool = firstData->dataValue.DataAsBool < secondData.dataValue.DataAsDouble;
				firstData->dataType = TYPE_BOOL;
			}
			else if (operation == TGT)
			{
				firstData->dataValue.DataAsBool = firstData->dataValue.DataAsBool > secondData.dataValue.DataAsDouble;
				firstData->dataType = TYPE_BOOL;
			}
			else if (operation == TLE)
			{
				firstData->dataValue.DataAsBool = firstData->dataValue.DataAsBool <= secondData.dataValue.DataAsDouble;
				firstData->dataType = TYPE_BOOL;
			}
			else if (operation == TGE)
			{
				firstData->dataValue.DataAsBool = firstData->dataValue.DataAsBool >= secondData.dataValue.DataAsDouble;
				firstData->dataType = TYPE_BOOL;
			}

			else if (operation == TEQ)
			{
				firstData->dataValue.DataAsBool = firstData->dataValue.DataAsBool == secondData.dataValue.DataAsDouble;
				firstData->dataType = TYPE_BOOL;
			}
			else if (operation == TNEQ)
			{
				firstData->dataValue.DataAsBool = firstData->dataValue.DataAsBool != secondData.dataValue.DataAsDouble;
				firstData->dataType = TYPE_BOOL;
			}
		}
		else if (secondData.dataType == TYPE_BOOL)
		{
			if (operation == TPlus)
				firstData->dataValue.DataAsBool += secondData.dataValue.DataAsBool;
			else if (operation == TMinus)
				firstData->dataValue.DataAsBool -= secondData.dataValue.DataAsBool;
			else if (operation == TMult)
				firstData->dataValue.DataAsBool *= secondData.dataValue.DataAsBool;
			else if (operation == TDiv)
				firstData->dataValue.DataAsBool /= secondData.dataValue.DataAsBool;
			else if (operation == TMod)
				firstData->dataValue.DataAsBool %= secondData.dataValue.DataAsBool;
			else if (operation == TAnd)
				firstData->dataValue.DataAsBool &= secondData.dataValue.DataAsBool;
			else if (operation == TOR)
				firstData->dataValue.DataAsBool |= secondData.dataValue.DataAsBool;
			else if (operation == TXOR)
				firstData->dataValue.DataAsBool ^= secondData.dataValue.DataAsBool;

			else if (operation == TLT)
			{
				firstData->dataValue.DataAsBool = firstData->dataValue.DataAsBool < secondData.dataValue.DataAsBool;
				firstData->dataType = TYPE_BOOL;
			}
			else if (operation == TGT)
			{
				firstData->dataValue.DataAsBool = firstData->dataValue.DataAsBool > secondData.dataValue.DataAsBool;
				firstData->dataType = TYPE_BOOL;
			}
			else if (operation == TLE)
			{
				firstData->dataValue.DataAsBool = firstData->dataValue.DataAsBool <= secondData.dataValue.DataAsBool;
				firstData->dataType = TYPE_BOOL;
			}
			else if (operation == TGE)
			{
				firstData->dataValue.DataAsBool = firstData->dataValue.DataAsBool >= secondData.dataValue.DataAsBool;
				firstData->dataType = TYPE_BOOL;
			}

			else if (operation == TEQ)
			{
				firstData->dataValue.DataAsBool = firstData->dataValue.DataAsBool == secondData.dataValue.DataAsBool;
				firstData->dataType = TYPE_BOOL;
			}
			else if (operation == TNEQ)
			{
				firstData->dataValue.DataAsBool = firstData->dataValue.DataAsBool != secondData.dataValue.DataAsBool;
				firstData->dataType = TYPE_BOOL;
			}
		}
	}

}

DataS Tree::TypeCastingAssign(DATA_TYPE firstType, DataS second, LEX firstTypeName, LEX secondTypeName)
{
	if (firstType == TYPE_OBJ_CL)
	{
		if (second.dataType == TYPE_OBJ_CL)
		{
			if (strcmp(firstTypeName, secondTypeName) == 0)
			{
				printf("\n�������� ���������� �����: ������������ ������� ������ %s ������� ������ %s ------ ������ %d\n", firstTypeName, secondTypeName, scan->Get_Number_Line());
			}
			else
			{
				scan->PrintError("������� ������������ ������� ������ \"" + string(firstTypeName) +  "\" ������� ������ \"" + string(secondTypeName) + "\"", "\0", '\0');
			}
		}
		else
		{
			scan->PrintError("������� ������������ ������� ������ \"" + string(firstTypeName) + "\" �������� ���� \"" + string(DT_Name[second.dataType]) + "\"", "\0", '\0');
		}
	}
	else if (second.dataType == TYPE_OBJ_CL)
	{
		scan->PrintError("\n������� ������������ ���������� ���� \"" + string(DT_Name[firstType]) + "\" ������� ������", "\0", '\0');
	}
	else
	{
		printf("\n�������� ���������� �����: ���������� ���� %s � ���� %s (������������) --> %s ------ ������ %d\n", DT_Name[second.dataType], DT_Name[firstType], DT_Name[firstType], scan->Get_Number_Line());

		if (firstType == TYPE_BOOL)
		{
			if (second.dataType != TYPE_BOOL)
			{
				if (second.dataType == TYPE_DOUBLE)
				{
					second.dataValue.DataAsBool = second.dataValue.DataAsDouble;
				}

				second.dataType = TYPE_BOOL;
			}

			printf("\t���: bool\t��������: %d", second.dataValue.DataAsBool);
		}
		else if (firstType == TYPE_DOUBLE)
		{
			if (second.dataType != TYPE_DOUBLE)
			{
				if (second.dataType == TYPE_BOOL)
				{
					second.dataValue.DataAsDouble = second.dataValue.DataAsBool;
				}

				second.dataType = TYPE_DOUBLE;
			}

			printf("\t���: double\t��������: %f", second.dataValue.DataAsDouble);
		}

		return second;
	}
}

void Tree::CheckTypeBool(DATA_TYPE type)
{
	if (!flagInterpret) return;

	if (type != TYPE_BOOL)
	{
		scan->PrintError("��������� ������ ��������� � �������������� ����");
	}
}

void Tree::Back()
{
	cur->CleanChild();
	Tree* lastleft = cur->left;
	cur = cur->parent;
	delete cur->left;
	cur->left = lastleft;
	cur = lastcur;
}


