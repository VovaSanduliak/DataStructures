#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

#define ListSize 14
#define MaxValue 20

struct TListItem
{
    int Value;
    TListItem* Next, * Prev;
};

struct TList
{
    TListItem* First, * Last;
};

TList InitList()
{
    TList r;
    r.First = NULL;
    r.Last = NULL;
    return r;
}

void AddListItem(TList& List, int val)
{
    if (List.First == NULL)
    {
        List.First = (TListItem*)malloc(sizeof(TListItem));
        List.First->Next = NULL;
        List.First->Prev = NULL;
        List.First->Value = val;
        List.Last = List.First;
    }
    else
    {
        List.Last->Next = (TListItem*)malloc(sizeof(TListItem));
        List.Last->Next->Prev = List.Last;
        List.Last->Next->Next = NULL;
        List.Last->Next->Value = val;
        List.Last = List.Last->Next;
    }
}

void DestroyList(TList& List)
{
    TListItem* t = List.First;
    TListItem* r;

    while (t != NULL)
    {
        r = t->Next;
        free(t);
        t = r;
    }

    List.First = List.Last = NULL;
}

void PrintList(TList& List)
{
    TListItem* t = List.First;

    while (t != NULL)
    {
        printf("%i ", t->Value);
        t = t->Next;
    }

}

void DoubleOdd(TList& List) {
    TListItem* CurItem = List.First;

    while (CurItem != NULL) {
        if (CurItem->Value % 2 == 0)
        {
            CurItem = CurItem->Next;
        }
        else
        {
            TListItem* NewItem = (TListItem*)malloc(sizeof(TListItem));

            NewItem->Next = CurItem->Next;
            NewItem->Prev = CurItem;
            CurItem->Next = NewItem;
            NewItem->Value = CurItem->Value;

            if (CurItem == List.Last)
            {
                List.Last = NewItem;
            }

            CurItem = CurItem->Next->Next;
        }
    }
}

void FillList(TList& List)
{
    ifstream file("data.txt");

    if (!file)
    {
        cerr << "Couldn't open the file" << endl;
    }

    int input;
    while (file >> input)
    {
        AddListItem(List, input);
    }
}

int main()
{
    TList List = InitList();

    FillList(List);

    printf("Your list:\n");
    PrintList(List);
    DoubleOdd(List);

    printf("\n");
    printf("Your list:\n");
    PrintList(List);

    return 0;
}