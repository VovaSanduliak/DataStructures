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

TList InitList()
{
    TList r;
    r.First = NULL;
    r.Last = NULL;
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

TListIterator GetBegin(TList& L)
{
    TListIterator r;
    r.pointer = L.First;
    return r;
}

TListIterator GetEnd(TList& L)
{
    TListIterator r;
    r.pointer = L.Last;
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

// Перевіряє чи входить елемент в множину
bool IsIn(int value, TList& List)
{
    //TListItem* t = List.First;
    TListIterator t = GetBegin(List);

    // Якщо список порожній
    if (!IsValid(t))
        return false;

    while (IsValid(t))
    {
        if (GetValue(t) == value)
            return true;

        //t = t->Next;
        MoveNext(t);
    }

    return false;
}

// Повертає новий список перетин елементів двох списків
TList Intersection(TList& List1, TList& List2)
{
    TList result = InitList();

    //TListItem* t1 = List1.First;
    TListIterator t1 = GetBegin(List1);
    while (IsValid(t1))
    {
        if (IsIn(GetValue(t1), result))
        {
            //t1 = t1->Next;
            MoveNext(t1);
            continue;
        }

        TListIterator t2 = GetBegin(List2);
        while (IsValid(t2))
        {
            if (GetValue(t1) == GetValue(t2))
            {
                AddListItem(result, GetValue(t1));
                break;
            }

            //t2 = t2->Next;
            MoveNext(t2);
        }

        //t1 = t1->Next;
        MoveNext(t1);
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