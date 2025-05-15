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
		else if (m[z] <= MaxTypeNeterminal)	//в верхушке магазина нетерминал
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
				// L -> sem_setIdent = Q | sem_setIdent
				// L -> sem_setIdent push = Q matchLeft gener | sem_setIdent
				if (t == TSave)
				{
					m[z++] = sem_gener;
					m[z++] = sem_matchLeft;
					m[z++] = neterm_Q;
					m[z++] = TSave;
					m[z++] = sem_push;
					m[z++] = sem_setIdent;

					genIL->saveOperator(t);
				}
				else
				{
					m[z++] = sem_setIdent;
				}
				break;

			case neterm_I:
				// I -> class a { G } ;
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
				// F -> N1 sem_setFunct push ( ) startFunc K endFunc sem_returnLevel
				m[z++] = sem_returnLevel;
				m[z++] = sem_endFunc;
				m[z++] = neterm_K;
				m[z++] = sem_startFunc;
				m[z++] = TRS;
				m[z++] = TLS;
				m[z++] = sem_push;
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
				// M -> B O ; | K | M1 | ; | H ; | main sem_findFunct ( ) ;
				// M -> B O ; | K | M1 | ; | H ; | main sem_findFunct push ( ) generCall ;
				if (t == TIdent)
				{
					m[z++] = TTochkaZap;
					m[z++] = neterm_O;
					m[z++] = neterm_B;
				}
				else if (t == TMain)
				{
					m[z++] = TTochkaZap;
					m[z++] = sem_generCall;
					m[z++] = TRS;
					m[z++] = TLS;
					m[z++] = sem_push;
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
				// M1 -> if ( Q ) generIf setAddr M formIf generGoto setAddr N formGoto generNop
				m[z++] = sem_generNop;
				m[z++] = sem_formGoto;
				m[z++] = neterm_N;
				m[z++] = sem_setAddr;
				m[z++] = sem_generGoto;
				m[z++] = sem_formIf;
				m[z++] = neterm_M;
				m[z++] = sem_setAddr;
				m[z++] = sem_generIf;
				m[z++] = TRS;
				m[z++] = neterm_Q;
				m[z++] = TLS;
				m[z++] = TIf;
				break;

			case neterm_H:
				// H -> return Q
				// H -> return Q matchLeft generReturn
				m[z++] = sem_generReturn;
				m[z++] = sem_matchLeft;
				m[z++] = neterm_Q;
				m[z++] = TReturn;
				genIL->saveOperator(TReturn);
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
				// O -> sem_findVar = Q | sem_findFunct ( )
				// O -> sem_findVar push = Q sem_matchLeft gener | sem_findFunct push ( ) generCall
				if (t == TSave)
				{
					m[z++] = sem_gener;
					m[z++] = sem_matchLeft;
					m[z++] = neterm_Q;
					m[z++] = TSave;
					m[z++] = sem_push;
					m[z++] = sem_findVar;

					genIL->saveOperator(t);
				}
				else
				{
					m[z++] = sem_generCall;
					m[z++] = TRS;
					m[z++] = TLS;
					m[z++] = sem_push;
					m[z++] = sem_findFunct;
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
				// Q1 -> \ R sem_matchBool gener Q1 | eps
				if (t == TOR)
				{
					m[z++] = neterm_Q1;
					m[z++] = sem_gener;
					m[z++] = sem_matchBool;
					m[z++] = neterm_R;
					m[z++] = TOR;

					genIL->saveOperator(t);
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
				// R1 -> ^ U sem_matchBool gener R1 | eps
				if (t == TOR)
				{
					m[z++] = neterm_R1;
					m[z++] = sem_gener;
					m[z++] = sem_matchBool;
					m[z++] = neterm_U;
					m[z++] = TXOR;

					genIL->saveOperator(t);
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
				// U1 -> & V sem_matchBool gener U1 | eps
				if (t == TAnd)
				{
					m[z++] = neterm_U1;
					m[z++] = sem_gener;
					m[z++] = sem_matchBool;
					m[z++] = neterm_V;
					m[z++] = TAnd;

					genIL->saveOperator(t);
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
				// V1 -> == W sem_match gener V1 | != W sem_match geer V1 | eps
				if (t == TEQ || t == TNEQ)
				{
					m[z++] = neterm_V1;
					m[z++] = sem_gener;
					m[z++] = sem_match;
					m[z++] = neterm_W;
					m[z++] = t;

					genIL->saveOperator(t);
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
				// W1 -> < X sem_match gener W1 | <= X sem_match gener W1 | > X sem_match gener W1 | >= X sem_match gener W1 | eps
				if (t >= TLT && t <= TGE)
				{
					m[z++] = neterm_W1;
					m[z++] = sem_gener;
					m[z++] = sem_match;
					m[z++] = neterm_X;
					m[z++] = t;

					genIL->saveOperator(t);
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
				// X1 -> + Y sem_match gener X1 | - Y sem_match gener X1 | eps
				if (t == TPlus || t == TMinus)
				{
					m[z++] = neterm_X1;
					m[z++] = sem_gener;
					m[z++] = sem_match;
					m[z++] = neterm_Y;
					m[z++] = t;

					genIL->saveOperator(t);
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
				// Y1 -> * Z sem_match gener Y1 | / Z sem_match gener Y1 | % Z sem_matchBool gener Y1 | eps
				if (t == TMult || t == TDiv)
				{
					m[z++] = neterm_Y1;
					m[z++] = sem_gener;
					m[z++] = sem_match;
					m[z++] = neterm_Z;
					m[z++] = t;

					genIL->saveOperator(t);
				}
				else if (t == TMod)
				{
					m[z++] = neterm_Y1;
					m[z++] = sem_gener;
					m[z++] = sem_matchBool;
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
				// Z -> + Z1 generUnar | - Z1 generUnar | Z1

				if (t == TPlus || t == TMinus)
				{
					m[z++] = sem_generUnar;
					m[z++] = neterm_Z1;
					m[z++] = t;

					genIL->saveOperator(t);
				}
				else
				{
					m[z++] = neterm_Z1;
				}

				break;

			case neterm_Z1:
				// Z1 -> B P | C | main ( ) | ( Q )
				// Z1 -> B P | C | main sem_findFunct ( ) | ( Q )
				// Z1 -> B P | C constType | main sem_findFunct push ( ) generCall | ( Q )
				if (t == TIdent)
				{
					m[z++] = neterm_P;
					m[z++] = neterm_B;
				}
				else if (t == TMain)
				{
					m[z++] = sem_generCall;
					m[z++] = TRS;
					m[z++] = TLS;
					m[z++] = sem_push;
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
					m[z++] = sem_constType;
					m[z++] = neterm_C;
				}
				break;

			case neterm_P:
				// P -> ( ) | eps
				// P -> sem_findFunct ( ) | sem_findVar
				// P -> sem_findFunct push ( ) generCall | sem_findVar push
				if (t == TLS)
				{
					m[z++] = sem_generCall;
					m[z++] = TRS;
					m[z++] = TLS;
					m[z++] = sem_push;
					m[z++] = sem_findFunct;
				}
				else
				{
					m[z++] = sem_push;
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
				// B1 -> sem_findVar . sem_checkObject a B1 | eps
				if (t == TTochka)
				{
					m[z++] = neterm_B1;
					m[z++] = TIdent;
					m[z++] = sem_checkObject;
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
			}
		}
		else if (m[z] <= MaxTypeSem)	//в верхушке магазина операционный символ
		{
			switch (m[z])
			{
			case sem_startDeclare:
				tran->deltaStartDeclare(m[z + 1]);
				break;

			case sem_setIdent:
				tran->deltaSetIdent();
				break;

			case sem_findVar:
				tran->deltaFindVar();
				break;

			case sem_setFunct:
				tran->deltaSetFunct();
				break;

			case sem_checkObject:
				global->obj = true;
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

			case sem_constType:
				tran->deltaConstType(m[z + 1]);
				genIL->deltaPushType();
				genIL->deltaPushRes(genIL->R(m[z + 1]));
				break;

			case sem_match:
				genIL->deltaMatch();
				break;

			case sem_matchLeft:
				genIL->deltaMatchLeft();
				break;

			case sem_matchBool:
				genIL->deltaMatchBool();
				break;

			case sem_push:
				genIL->deltaPushType();
				genIL->deltaPushRes(genIL->R());
				break;

			case sem_gener:
				genIL->deltaGener(global->operation.back());
				global->operation.pop_back();
				break;

			case sem_generUnar:
				genIL->deltaGenerUnar(global->operation.back());
				global->operation.pop_back();
				break;

			case sem_generIf:
				genIL->deltaGenerIf();
				break;

			case sem_formIf:
				genIL->deltaFormIf();
				break;

			case sem_generGoto:
				genIL->deltaGenerGoto();
				break;

			case sem_formGoto:
				genIL->deltaFormGoto();
				break;

			case sem_generNop:
				genIL->deltaGenerNop();
				break;

			case sem_setAddr:
				genIL->deltaSetAddr();
				break;

			case sem_generCall:
				genIL->deltaGenerCall();
				break;

			case sem_startFunc:
				genIL->deltaStartFunc();
				break;

			case sem_endFunc:
				genIL->deltaEndFunc();
				break;

			case sem_generReturn:
				genIL->deltaGenerReturn();
				global->operation.pop_back();
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

void LL1::PrintTriada()
{
	genIL->printTriadaCode();
}

void LL1::GenCode()
{
	genIL->generateCode();
}

LL1::LL1(Scaner* scan)
{
	this->scan = scan;
	z = 0;
	this->root = new Tree(scan);
	this->global = new GlobalData();
	this->tran = new Translate(root, global);
	this->genIL = new GenerIL(root, global);
}

LL1::~LL1()
{
	tran->CleanTree();

	delete tran;
	delete genIL;
	delete scan;
}

void LL1::epsilon()	//обработка правила с пустой правой частью
{
	;
}
