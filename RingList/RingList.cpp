#include <fstream>
#include <iostream>

using namespace std;

struct TListItem
{
    int Value;
    TListItem* Next, * Prev;
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
        List.First = new TListItem();
        List.First->Next = NULL;
        List.First->Prev = NULL;
        List.First->Value = val;
        
    }
    else
    {
        List.Last->Next = new TListItem();
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

    List.First = NULL;
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

int main()
{
    TList List = InitList();

    for (int i = 0; i < ListSize; i++)
    {
        AddListItem(List, i);
    }

    PrintList(List);

    return 0;
}