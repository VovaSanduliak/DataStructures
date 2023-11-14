#include <iostream>
#define ListSize 10

using namespace std;

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

// Заповнює список рандомними числами від 1 до 10
void FillList(TList& List, int size)
{
    for (int i = 0; i < size; i++)
    {
        int num = rand() % 10 + 1;
        AddListItem(List, num);
    }
}

// Перевіряє чи входить елемент в множину (список)
bool IsIn(const TListItem& item, const TList& List)
{
    TListItem* t = List.First;

    // множина (список) порожня
    if (t == NULL)
        return false;

    while (t != NULL)
    {
        if (t->Value == item.Value)
            return true;

        t = t->Next;
    }

    return false;
}

// Повертає новий список перетин елементів двох списків
TList Intersection(const TList& List1, const TList& List2)
{
    TList result = InitList();

    TListItem* t1 = List1.First;
    while (t1 != NULL)
    {
        if (IsIn(*t1, result))
        {
            t1 = t1->Next;
            continue;
        }
            
        TListItem* t2 = List2.First;
        while (t2 != NULL)
        {
            if (t1->Value == t2->Value)
            {
                AddListItem(result, t1->Value);
                break;
            }

            t2 = t2->Next;
        }

        t1 = t1->Next;
    }

    return result;
}

int main()
{
    setlocale(LC_ALL, "ukr");
    srand(time(NULL));

    TList List1 = InitList();
    FillList(List1, ListSize);
    cout << "Перший список: ";
    PrintList(List1);
    
    TList List2 = InitList();
    FillList(List2, ListSize);
    cout << "\nДругий список: ";
    PrintList(List2);

    TList List3 = Intersection(List1, List2);
    cout << "\nПеретин списків: ";
    PrintList(List3);

    return 0;
}