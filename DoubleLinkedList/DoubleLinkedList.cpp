#include <iostream>

using namespace std;

#define ListSize 15
#define MaxValue 20

struct TListItem
{
    int Value;
    TListItem *Next, *Prev;
};

struct TList
{
    TListItem *First, *Last;
};

TList InitList()
{
    TList r;
    r.First = NULL;
    r.Last = NULL;
    return r;
}

void AddListItem(TList &List, int val)
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
    TListItem *t = List.First;
    TListItem *r;

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
    TListItem *t = List.First;

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