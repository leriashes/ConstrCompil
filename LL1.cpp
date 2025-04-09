#include "LL1.h"

Scaner* LL1::scan = (Scaner*)NULL;

int LL1::LL_1() //функция синтаксического анализатора
{
	int t, fl = 1, uk1, ttt;
	LEX l, lll;

	m[z] = neterm_S;
	t = scan->FScaner(l);

	while (fl)
	{
		if (m[z] <= MaxTypeTerminal)	//в верхушке магазина терминал
		{
			if (m[z] == t)
			{
				if (t == TEnd)
				{
					fl = 0;
				}
				else
				{
					tran->SaveLex(l);
					t = scan->FScaner(l);
				}
			}
			else
			{
				scan->PrintError("Неверный символ", l);
				return -1;
			}
		}
		else	//в верхушке магазина нетерминал
		{
			switch (m[z])
			{
			case neterm_S:
				// S -> A S | eps
				if (t == TEnd)
				{
					m[z++] = TEnd;
				}
				else
				{
					m[z++] = neterm_S;
					m[z++] = neterm_A;
				}
				break;

			case neterm_A:
				// A -> T A1 | I
				// A -> T sem_startDeclare A1 | I
				if (t == TClass)
				{
					m[z++] = neterm_I;
				}
				else
				{
					m[z++] = neterm_A1;
					m[z++] = sem_startDeclare;
					m[z++] = neterm_T;
				}
				break;

			case neterm_A1:
				// A1 -> D | F
				if (t == TIdent)
				{
					uk1 = scan->GetUK();
					ttt = scan->FScaner(lll);
					scan->PutUK(uk1);

					if (ttt == TTochka || ttt == TLS)
					{
						m[z++] = neterm_F;
					}
					else
					{
						m[z++] = neterm_D;
					}
				}
				else
				{
					m[z++] = neterm_F;
				}
				break;

			case neterm_D:
				// D -> E;
				m[z++] = TTochkaZap;
				m[z++] = neterm_E;
				break;

			case neterm_T:
				// T -> bool | double | a
				// T -> bool | double | a sem_findClass
				if (t == TBool || t == TDouble)
				{
					m[z++] = t;
				}
				else
				{
					m[z++] = sem_findClass;
					m[z++] = TIdent;
				}
				break;

			case neterm_E:
				// E -> a L E1
				m[z++] = neterm_E1;
				m[z++] = neterm_L;
				m[z++] = TIdent;
				break;

			case neterm_E1:
				// E1 -> , a L E1 | eps
				if (t == TZapya)
				{
					m[z++] = neterm_E1;
					m[z++] = neterm_L;
					m[z++] = TIdent;
					m[z++] = TZapya;
				}
				else
				{
					epsilon();
				}
				break;

			case neterm_L:
				// L -> = Q | eps
				// L -> sem_setIdent = Q sem_match | sem_setIdent
				if (t == TSave)
				{
					m[z++] = sem_match;
					m[z++] = neterm_Q;
					m[z++] = TSave;
					m[z++] = sem_setIdent;
				}
				else
				{
					m[z++] = sem_setIdent;
				}
				break;

			case neterm_I: 
				// I -> class a sem_setClass { G } sem_returnLevel ;
				m[z++] = TTochkaZap;
				m[z++] = sem_returnLevel;
				m[z++] = TFRS;
				m[z++] = neterm_G;
				m[z++] = TFLS;
				m[z++] = sem_setClass;
				m[z++] = TIdent;
				m[z++] = TClass;
				break;

			case neterm_G:
				// G -> A G | eps
				if (t == TBool || t == TDouble || t == TIdent)
				{
					m[z++] = neterm_G;
					m[z++] = neterm_A;
				}
				else
				{
					epsilon();
				}
				break;

			case neterm_F:
				// F -> N1 ( ) K
				// F -> N1 sem_setFunct ( ) K sem_returnLevel
				m[z++] = sem_returnLevel;
				m[z++] = neterm_K;
				m[z++] = TRS;
				m[z++] = TLS;
				m[z++] = sem_setFunct;
				m[z++] = neterm_N1;
				break;

			case neterm_K:
				// K -> { J }
				// K -> { sem_setNewLevel J } sem_returnLevel
				m[z++] = sem_returnLevel;
				m[z++] = TFRS;
				m[z++] = neterm_J;
				m[z++] = sem_setNewLevel;
				m[z++] = TFLS;
				break;

			case neterm_J:
				// J -> T D J | I J | M J | eps
				// J -> T sem_startDeclare D J | I J | M J | eps
				if (t == TClass)
				{
					m[z++] = neterm_J;
					m[z++] = neterm_I;
				}
				else if (t == TIdent)
				{
					uk1 = scan->GetUK();
					ttt = scan->FScaner(lll);
					scan->PutUK(uk1);

					if (ttt == TIdent)
					{
						m[z++] = neterm_J;
						m[z++] = neterm_D;
						m[z++] = sem_startDeclare;
						m[z++] = neterm_T;
					}
					else
					{
						m[z++] = neterm_J;
						m[z++] = neterm_M;
					}
				}
				else if (t == TBool || t == TDouble)
				{
					m[z++] = neterm_J;
					m[z++] = neterm_D;
					m[z++] = sem_startDeclare;
					m[z++] = neterm_T;
				}
				else if (t == TFRS)
				{
					epsilon();
				}
				else
				{
					m[z++] = neterm_J;
					m[z++] = neterm_M;
				}
				break;

			case neterm_M:
				// M -> B O ; | K | M1 | ; | H ; | main ( ) ;
				// M -> B sem_findVar O ; | K | M1 | ; | H ; | main sem_findFunct ( ) ;
				if (t == TIdent)
				{
					m[z++] = TTochkaZap;
					m[z++] = neterm_O;
					m[z++] = sem_findVar;
					m[z++] = neterm_B;
				}
				else if (t == TMain)
				{
					m[z++] = TTochkaZap;
					m[z++] = TRS;
					m[z++] = TLS;
					m[z++] = sem_findFunct;
					m[z++] = TMain;
				}
				else if (t == TFLS)
				{
					m[z++] = neterm_K;
				}
				else if (t == TIf)
				{
					m[z++] = neterm_M1;
				}
				else if (t == TTochkaZap)
				{
					m[z++] = TTochkaZap;
				}
				else
				{
					m[z++] = TTochkaZap;
					m[z++] = neterm_H;
				}
				break;

			case neterm_M1:
				// M1 -> if ( Q ) M N
				m[z++] = neterm_N;
				m[z++] = neterm_M;
				m[z++] = TRS;
				m[z++] = neterm_Q;
				m[z++] = TLS;
				m[z++] = TIf;
				break;

			case neterm_H:
				// H -> return Q
				// H -> return Q sem_match
				m[z++] = sem_match;
				m[z++] = neterm_Q;
				m[z++] = TReturn;
				break;

			case neterm_N:
				// N -> else M | eps
				if (t == TElse)
				{
					m[z++] = neterm_M;
					m[z++] = TElse;
				}
				else
				{
					epsilon();
				}
				break;

			case neterm_O:
				// O -> = Q | ( )
				// O -> = Q sem_match | ( )
				if (t == TSave)
				{
					m[z++] = sem_match;
					m[z++] = neterm_Q;
					m[z++] = TSave;
				}
				else
				{
					m[z++] = TRS;
					m[z++] = TLS;
				}
				break;

			case neterm_N1:
				// N1 -> B | main
				if (t == TMain)
				{
					m[z++] = TMain;
				}
				else
				{
					m[z++] = neterm_B;
				}
				break;

			case neterm_Q:
				// Q -> R Q1
				m[z++] = neterm_Q1;
				m[z++] = neterm_R;
				break;

			case neterm_Q1:
				// Q1 -> \ R Q1 | eps
				// Q1 -> \ R sem_match Q1 | eps
				if (t == TOR)
				{
					m[z++] = neterm_Q1;
					m[z++] = sem_match;
					m[z++] = neterm_R;
					m[z++] = TOR;
				}
				else
				{
					epsilon();
				}
				break;

			case neterm_R:
				// R -> U R1
				m[z++] = neterm_R1;
				m[z++] = neterm_U;
				break;

			case neterm_R1:
				// R1 -> ^ U R1 | eps
				// R1 -> ^ U sem_match R1 | eps
				if (t == TOR)
				{
					m[z++] = neterm_R1;
					m[z++] = sem_match;
					m[z++] = neterm_U;
					m[z++] = TXOR;
				}
				else
				{
					epsilon();
				}
				break;

			case neterm_U:
				// U -> V U1
				m[z++] = neterm_U1;
				m[z++] = neterm_V;
				break;

			case neterm_U1:
				// U1 -> & V U1 | eps
				// U1 -> & V sem_match U1 | eps
				if (t == TAnd)
				{
					m[z++] = neterm_U1;
					m[z++] = sem_match;
					m[z++] = neterm_V;
					m[z++] = TAnd;
				}
				else
				{
					epsilon();
				}
				break;

			case neterm_V:
				// V -> W V1
				m[z++] = neterm_V1;
				m[z++] = neterm_W;
				break;

			case neterm_V1:
				// V1 -> == W V1 | != W V1 | eps
				// V1 -> == W sem_match V1 | != W sem_match V1 | eps
				if (t == TEQ || t == TNEQ)
				{
					m[z++] = neterm_V1;
					m[z++] = sem_match;
					m[z++] = neterm_W;
					m[z++] = t;
				}
				else
				{
					epsilon();
				}
				break;

			case neterm_W:
				// W -> X W1
				m[z++] = neterm_W1;
				m[z++] = neterm_X;
				break;

			case neterm_W1:
				// W1 -> < X W1 | <= X W1 | > X W1 | >= X W1 | eps
				// W1 -> < X sem_match W1 | <= X sem_match W1 | > X sem_match W1 | >= X sem_match W1 | eps
				if (t >= TLT && t <= TGE)
				{
					m[z++] = neterm_W1;
					m[z++] = sem_match;
					m[z++] = neterm_X;
					m[z++] = t;
				}
				else
				{
					epsilon();
				}
				break;

			case neterm_X:
				// X -> Y X1
				m[z++] = neterm_X1;
				m[z++] = neterm_Y;
				break;

			case neterm_X1:
				// X1 -> + Y X1 | - Y X1 | eps
				// X1 -> + Y sem_match X1 | - Y sem_match X1 | eps
				if (t == TPlus || t == TMinus)
				{
					m[z++] = neterm_X1;
					m[z++] = sem_match;
					m[z++] = neterm_Y;
					m[z++] = t;
				}
				else
				{
					epsilon();
				}
				break;

			case neterm_Y:
				// Y -> Z Y1
				m[z++] = neterm_Y1;
				m[z++] = neterm_Z;
				break;

			case neterm_Y1:
				// Y1 -> * Z Y1 | / Z Y1 | % Z Y1 | eps
				// Y1 -> * Z sem_match Y1 | / Z sem_match Y1 | % Z sem_match Y1 | eps
				if (t == TMult || t == TDiv || t == TMod)
				{
					m[z++] = neterm_Y1;
					m[z++] = sem_match;
					m[z++] = neterm_Z;
					m[z++] = t;
				}
				else
				{
					epsilon();
				}
				break;

			case neterm_Z:
				// Z -> + Z1 | - Z1 | Z1
				m[z++] = neterm_Z1;

				if (t == TPlus || t == TMinus)
				{
					m[z++] = t;
				}
				break;

			case neterm_Z1:
				// Z1 -> B P | C | main ( ) | ( Q )
				// Z1 -> B P | C | main sem_findFunct ( ) | ( Q )
				if (t == TIdent)
				{
					m[z++] = neterm_P;
					m[z++] = neterm_B;
				}
				else if (t == TMain)
				{
					m[z++] = TRS;
					m[z++] = TLS;
					m[z++] = sem_findFunct;
					m[z++] = TMain;
				}
				else if (t == TLS)
				{
					m[z++] = TRS;
					m[z++] = neterm_Q;
					m[z++] = TLS;
				}
				else
				{
					m[z++] = neterm_C;
				}
				break;

			case neterm_P:
				// P -> ( ) | eps
				// P -> sem_findFunct ( ) | sem_findVar
				if (t == TLS)
				{
					m[z++] = TRS;
					m[z++] = TLS;
					m[z++] = sem_findFunct;
				}
				else
				{
					m[z++] = sem_findVar;
				}
				break;

			case neterm_B:
				// B -> a B1
				m[z++] = neterm_B1;
				m[z++] = TIdent;
				break;

			case neterm_B1:
				// B1 -> . a B1 | eps
				// B1 -> sem_findVar . a B1 | eps
				if (t == TTochka)
				{
					m[z++] = neterm_B1;
					m[z++] = TIdent;
					m[z++] = TTochka;
					m[z++] = sem_findVar;
				}
				else
				{
					epsilon();
				}
				break;

			case neterm_C:
				// C -> c1 | c2 | true | false
				if (t == TTrue || t == TFalse || t == TConstInt)
				{
					m[z++] = t;
				}
				else
				{
					m[z++] = TConstFloat;
				}
				break;

			case sem_startDeclare:
				tran->deltaStartDeclare(m[z + 1]);
				break;

			case sem_setIdent:
				tran->deltaSetIdent();
				break;

			case sem_findVar:
				tran->deltaFindVar();
				break;

			case sem_match:
				break;

			case sem_setFunct:
				tran->deltaSetFunct();
				break;

			case sem_returnLevel:
				tran->deltaReturnLevel();
				break;

			case sem_setNewLevel:
				tran->deltaSetNewLevel();
				break;

			case sem_setClass:
				tran->deltaSetClass();
				break;

			case sem_findFunct:
				tran->deltaFindFunct();
				break;

			case sem_findClass:
				tran->deltaFindClass();
				break;

			}
		}

		z--;
	}

	return 1;
}

void LL1::PrintTree()
{
	tran->PrintTree();
}

LL1::LL1(Scaner* scan)
{
	this->scan = scan;
	z = 0;
	this->tran = new Translate(scan);
}

LL1::~LL1()
{
	tran->CleanTree();
	delete tran;
}

void LL1::epsilon()	//обработка правила с пустой правой частью
{
	;
}
