#include "Scaner.h"

LEX Keyword[MAX_KEYW] = { "bool", "double", "if", "else", "main", "return", "true", "false", "class" };

int IndexKeyword[MAX_KEYW] = { TBool, TDouble, TIf, TElse, TMain, TReturn, TTrue, TFalse, TClass };

void Scaner::PutUK(int i)
{
	uk = i;
}

int Scaner::GetUK()
{
	return uk;
}

void Scaner::Set_Position(int n)
{
	position = n;
}

void Scaner::Set_Line_Number(int n)
{
	line_number = n;
}

void Scaner::New_Line()
{
	line_number = line_number + 1;
	Set_Position(1);
}

int Scaner::Get_Number_Line()
{
	return line_number;
}

int Scaner::Get_Position()
{
	return position;
}

//������ ������
void Scaner::PrintError(string error, string a, char znak)
{
	if (a[0] == '\0')
	{
		cout << "\n������ - " << error;
		cout << "\n������: " << line_number << " �������: " << position;
	}
	else
	{
		cout << "\n������ - " << error << " - �������� ������ ";
		cout << "\n������: " << line_number << " �������: " << position;
	}
	if (znak != '\0')
	{
		cout << " (" << znak << ")";	//����� ���������� �������
	}

	exit(0);
}

void Scaner::PrintError(string error, string lex)
{
	cout << "\n\n������!\n" << error << ": " << lex << "\n������: " << line_number << "\n�������: " << position << "\n\n";
	exit(0);
}

// ���������-������
void Scaner::PrintError(string error)
{
	cout << "\n\n������!\n" << error << "\n������: " << line_number << "\n�������: " << position << "\n\n";
	exit(0);
}

int Scaner::FScaner(LEX lex)
{
	int i;          //������� ����� �������
	for (i = 0; i < MAX_LEX; i++)
	{
		lex[i] = 0;    //������� ���� �������
	}
	i = 0;

start:
	//��� ������������ ��������:
	while (t[uk] == ' ' || t[uk] == '\n' || t[uk] == '\t')	//���������� ��������
	{
		if (t[uk] == ' ' || t[uk] == '\t')
		{
			position = position + 1;
		}
		else
		{
			New_Line();
		}

		uk++;
	}

	if (t[uk] == '/' && t[uk + 1] == '/')	//������������ �����������
	{
		uk = uk + 2;
		position = position + 2;

		while (t[uk] != '\n' && t[uk] != '\0')
		{
			uk++;
			position = position + 1;
		}

		New_Line();
		goto start;
	}

	if (t[uk] == '/' && t[uk + 1] == '*')	//������������� �����������
	{
		uk = uk + 2;
		position = position + 2;

		while ((t[uk] != '*' || t[uk + 1] != '/') && t[uk] != '\0')
		{
			if (t[uk] == '\n')
			{
				New_Line();
			}
			else
			{
				position = position + 1;
			}

			uk++;
		}

		if (t[uk] == '*' && t[uk + 1] == '/')
		{
			uk = uk + 2;
			position = position + 2;
		}

		goto start;
	}

	if (t[uk] == '\0')
	{
		lex[0] = '#';
		return TEnd;
	}

	if (t[uk] >= '0' && t[uk] <= '9')
	{
		lex[i++] = t[uk++];
		position = position + 1;

		while (t[uk] >= '0' && t[uk] <= '9')
		{
			if (i < MAX_CONST - 1)
			{
				lex[i++] = t[uk++];
			}
			else
			{
				uk++;
			}
			position = position + 1;
		}
		if (i == MAX_CONST - 1)
		{
			PrintError("������� ������� ���������", lex, '\0');
			return TError;
		}

		if (t[uk] == '.')
		{
			lex[i++] = ',';
			t[uk++];
			position = position + 1;
			goto CONT;
		}

		return TConstInt;
	}
	else if (t[uk] >= 'a' && t[uk] <= 'z' || t[uk] >= 'A' && t[uk] <= 'Z')			//������������� 
	{
		lex[i++] = t[uk++];
		position = position + 1;
		while (t[uk] >= '0' && t[uk] <= '9' || t[uk] >= 'a' && t[uk] <= 'z' ||
			t[uk] >= 'A' && t[uk] <= 'Z' || t[uk] == '_')
		{
			if (i < MAX_LEX - 1)
			{
				lex[i++] = t[uk++];
			}
			else
			{
				uk++;
			}
			position = position + 1;
		}

		int j;
		for (j = 0; j < MAX_KEYW; j++)
		{
			if (strcmp(lex, Keyword[j]) == 0)
			{
				return IndexKeyword[j];
			}
		}

		return TIdent;
	}
	else if (t[uk] == '.')
	{
		lex[i++] = t[uk++];
		position = position + 1;
		if (t[uk + 1] >= '0' && t[uk + 1] <= '9')
		{
			lex[i++] = t[uk++];

			position = position + 1;

			goto CONT;
		}
		return TTochka;
	}
	else if (t[uk] == ',')
	{
		lex[i++] = t[uk++];
		position = position + 1;
		return TZapya;
	}
	else if (t[uk] == ';')
	{
		lex[i++] = t[uk++];
		position = position + 1;
		return TTochkaZap;
	}
	else if (t[uk] == '(')
	{
		lex[i++] = t[uk++];
		position = position + 1;
		return TLS;
	}
	else if (t[uk] == ')')
	{
		lex[i++] = t[uk++];
		position = position + 1;
		return TRS;
	}
	else if (t[uk] == '{')
	{
		lex[i++] = t[uk++];
		position = position + 1;
		return TFLS;
	}
	else if (t[uk] == '}')
	{
		lex[i++] = t[uk++];
		position = position + 1;
		return TFRS;
	}
	else if (t[uk] == '+')
	{
		lex[i++] = t[uk++];
		position = position + 1;
		return TPlus;
	}
	else if (t[uk] == '-')
	{
		lex[i++] = t[uk++];
		position = position + 1;
		return TMinus;
	}
	else if (t[uk] == '*')
	{
		lex[i++] = t[uk++];
		position = position + 1;
		return TMult;
	}
	else if (t[uk] == '/')
	{
		lex[i++] = t[uk++];
		position = position + 1;
		return TDiv;
	}
	else if (t[uk] == '%')
	{
		lex[i++] = t[uk++];
		position = position + 1;
		return TMod;
	}
	else if (t[uk] == '&' && t[uk + 1] == '&')
	{
		lex[i++] = t[uk++];
		lex[i++] = t[uk++];
		position = position + 2;
		return TAnd;
	}
	else if (t[uk] == '|' && t[uk + 1] == '|')
	{
		lex[i++] = t[uk++];
		lex[i++] = t[uk++];
		position = position + 2;
		return TOR;
	}
	else if (t[uk] == '^')
	{
		lex[i++] = t[uk++];
		position = position + 1;
		return TXOR;
	}
	else if (t[uk] == '=')
	{
		lex[i++] = t[uk++];
		position = position + 1;
		if (t[uk] == '=')
		{
			lex[i++] = t[uk++];
			position = position + 1;
			return TEQ;
		}

		return TSave;
	}
	else if (t[uk] == '!' && t[uk + 1] == '=')
	{
		lex[i++] = t[uk++];
		lex[i++] = t[uk++];
		position = position + 2;
		return TNEQ;
	}
	else if (t[uk] == '<')
	{
		lex[i++] = t[uk++];
		position = position + 1;
		if (t[uk] == '=')
		{
			lex[i++] = t[uk++];
			position = position + 1;
			return TLE;
		}
		return TLT;
	}
	else if (t[uk] == '>')
	{
		lex[i++] = t[uk++];
		position = position + 1;
		if (t[uk] == '=')
		{
			lex[i++] = t[uk++];
			position = position + 1;
			return TGE;
		}

		return TGT;
	}
	else
	{
		PrintError("�������� ������", lex, t[uk]);
		uk++;
		return TError;
	}

CONT:
	while (t[uk] >= '0' && t[uk] <= '9')
	{
		if (i < MAX_CONST - 1)
		{
			lex[i++] = t[uk++];
		}
		else
		{
			uk++;
		}
	}
	if (i == MAX_CONST - 1)
	{
		PrintError("������� ������� ���������", lex, '\0');
		return TError;
	}

	return TConstFloat;
}

void Scaner::GetData(string FileName)
{
	ifstream file(FileName);
	char symb;

	if (!file.is_open())	//�������� ������� �����
	{
		PrintError("������ ��� ������ �����", "", '\0');
		exit(1);
	}
	else         //������� �������� �����
	{
		int i = 0;		//�������
		while (!file.eof())		//������ ����� �� �����
		{
			file.get(symb);
			if (!file.eof()) t[i++] = symb;
			if (i >= MAX_TEXT - 1)		//�������� �������
			{
				PrintError("������� ������� ������ ��������� ������", "", '\0');
				break;
			}
		}

		t[i] = '\0';
		file.close();	//�������� �����
	}
}

Scaner::Scaner(string FileName)
{
	GetData(FileName);	//��������� ������ �� ��������� �����
	PutUK(0);
	Set_Line_Number(1);
	Set_Position(1);
}
