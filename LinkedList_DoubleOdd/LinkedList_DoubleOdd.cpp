#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>

#define ListSize 15
#define MaxValue 20

struct TListItem
{
    int Value;
    TListItem* Next;
};

struct TList
{
    TListItem* First;
};

TList InitList()
{
    TList r;
    r.First = NULL;
    return r;
}

void AddListItem(TList& List, int val)
{
    if (List.First == NULL)
    {
        List.First = (TListItem*)malloc(sizeof(TListItem));
        List.First->Next = NULL;
        List.First->Value = val;
    }
    else
    {
        TListItem* CurItem = List.First;

        while (CurItem != NULL)
        {
            if (CurItem->Next == NULL)
            {
                TListItem* NewItem = (TListItem*)malloc(sizeof(TListItem));
                NewItem->Value = val;
                CurItem->Next = NewItem;
            }

            CurItem = CurItem->Next;
        }
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

    List.First = NULL;
}

void PrintList(TList& List)
{
    TListItem* t = List.First;

    while (t != NULL)
    {
        printf("%i", t->Value);
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
            CurItem->Next = NewItem;
            NewItem->Value = CurItem->Value;

            CurItem = CurItem->Next->Next;
        }
    }
}

int main()
{
    TList List = InitList();

    for (int i = 0; i < ListSize; i++)
    {
        AddListItem(List, i);
    }

    printf("Your list:\n");
    PrintList(List);
    DoubleOdd(List);

    printf("Your list:\n");
    PrintList(List);

    return 0;
}