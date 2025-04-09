#include <iostream>
#include "LL1.h"

int main()
{
    setlocale(LC_ALL, "rus");   //Поддержка русского языка

    Scaner* scan;
    int type;
    LEX lex;

    scan = new Scaner("input.txt");   //Имя файла для чтения


    LL1 ll(scan);
    ll.LL_1();

    type = scan->FScaner(lex);


    if (type != TEnd)
    {
        scan->PrintError("Лишний текст в конце программы", lex, '\0');
    }
    else
    {
        printf("\n\nОшибки не найдены.\n\n");
    }

    printf("\n\n\nСЕМАНТИЧЕСКОЕ ДЕРЕВО\n\n");
    ll.PrintTree();

    delete scan;

    return 0;
}