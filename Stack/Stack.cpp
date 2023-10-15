#include <iostream>

struct TStack
{
	int Value;
	TStack* Next;

};

int IsEmpty(const TStack* S)
{
	return S == NULL;
}

void Push(TStack *&S, int v)
{
	if (!S)
	{
		S = new TStack;
		S->Next = NULL;
		S->Value = v;
	}
	else
	{
		TStack *t = S;
		S = new TStack;
		S->Next = t;
		S->Value = v;
	}
}

int Pop(TStack*& S)
{
	if (IsEmpty(S))
		return 0;

	int result = S->Value;
	TStack* t = S->Next;
	delete S;
	S = t;

	return result;
}

void DestroyStack(TStack*& S)
{
	if (S)
	{
		DestroyStack(S->Next);
		delete S;
		S = NULL;
	}
}