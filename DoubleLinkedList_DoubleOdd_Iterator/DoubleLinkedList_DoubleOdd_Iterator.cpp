#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <fstream>

using namespace std;

#define ListSize 15
#define MaxValue 20

struct TListItem
{
    int Value;
    TListItem* Next, * Prev;
};

struct TRingList
{
    TListItem* First, * Last;
};

struct TListIterator
{
    TListItem* pointer;
};

TListIterator InitIterator()
{
    TListIterator r;
    r.pointer = NULL;
    return r;
}

inline int IsValid(TListIterator It)
{
    return It.pointer != NULL;
}

void MoveNext(TListIterator& It)
{
    if (IsValid(It))
        It.pointer = It.pointer->Next;
}

void MovePrevious(TListIterator& It)
{
    if (IsValid(It))
        It.pointer = It.pointer->Prev;
}

int GetValue(const TListIterator& It)
{
    if (IsValid(It))
        return It.pointer->Value;
    return 0;
}

void SetValue(const TListIterator& It, int value)
{
    if (IsValid(It))
        It.pointer->Value = value;
}

TListIterator GetBegin(TRingList& L)
{
    TListIterator r;
    r.pointer = L.First;
    return r;
}

TListIterator GetEnd(TRingList& L)
{
    TListIterator r;
    r.pointer = L.Last;
    return r;
}

void InsertAfter(TRingList& L, const TListIterator& It, int value)
{
    if (!IsValid(It))
        return;
    TListItem* t = (TListItem*)malloc(sizeof(TListItem));
    t->Value = value;
    t->Next = It.pointer->Next;
    t->Prev = It.pointer;
    if (It.pointer->Next != NULL)
        It.pointer->Next->Prev = t;
    It.pointer->Next = t;
    if (It.pointer == L.Last)
        L.Last = t;
}

void InsertBefore(TRingList& L, const TListIterator& It, int value)
{
    if (!IsValid(It))
        return;
    TListItem* t = (TListItem*)malloc(sizeof(TListItem));
    t->Value = value;
    t->Prev = It.pointer->Prev;
    t->Next = It.pointer;
    if (It.pointer->Prev != NULL)
        It.pointer->Prev->Next = t;
    It.pointer->Prev = t;
    if (It.pointer == L.First) L.First = t;
}

void DeleteItem(TRingList& L, TListIterator& It)
{
    if (!IsValid(It))
        return;

    if (It.pointer == L.First)
        L.First = It.pointer->Next;

    if (It.pointer == L.Last)
        L.Last = It.pointer->Prev;

    TListItem* t1 = It.pointer->Prev;
    TListItem* t2 = It.pointer->Next;
    free(It.pointer);
    It.pointer = t2;

    if (t2 != NULL)
        t2->Prev = t1;

    if (t1 != NULL)
        t1->Next = t2;

    if (L.First == NULL)
        L.Last = NULL;

    if (L.Last == NULL)
        L.First = NULL;
}

TRingList InitRingList()
{
    TRingList r;
    r.First = NULL;
    r.Last = NULL;
    return r;
}

void AddListItem(TRingList& List, int val)
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

void DestroyList(TRingList& List)
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

void PrintList(TRingList& List)
{
    TListItem* t = List.First;

    while (t != NULL)
    {
        printf("%i", t->Value);
        t = t->Next;
    }

}

void DoubleOdd(TRingList& List) {
    TListIterator cur = GetBegin(List);

    while (IsValid(cur))
    {
        if (GetValue(cur) % 2 == 0)
        {
            MoveNext(cur);
        }
        else
        {
            InsertAfter(List, cur, GetValue(cur));

            MoveNext(cur);
            MoveNext(cur);
        }
    }
}

void FillList(TRingList& List)
{
    ifstream file("data.txt");

    if (!file)
    {
        // cerr
    }

    int input;
    while (file >> input)
    {
        AddListItem(List, input);
    }
}

int main()
{
    TRingList L;
    L = InitRingList();
    for (int i = 0; i < ListSize; i++)
    {
        AddListItem(L, i);
    }

    PrintList(L);
    printf("\n");
    TListIterator t = GetBegin(L);
    while (IsValid(t))
    {
        InsertBefore(L, t, GetValue(t));
        MoveNext(t);
    }

    PrintList(L);
    printf("\n");
    t = GetBegin(L);
    while (IsValid(t))
    {
        if (GetValue(t) % 2 != 0)
            DeleteItem(L, t);
        else
            MoveNext(t);

        PrintList(L);
        printf("\n");
        DestroyList(L);
    }

    return 0;
}