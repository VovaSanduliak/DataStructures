#include <iostream>

using namespace std;

struct TStack
{
	int Value;
	TStack* Next;
};

int IsEmpty(const TStack* S)
{
	return S == nullptr;
}

void Push(TStack*& S, int v)
{
	if (!S)
	{
		S = new TStack;
		S->Next = nullptr;
		S->Value = v;
	}
	else
	{
		TStack* t = S;
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
		S = nullptr;
	}
}

void main()
{
	TStack* S = nullptr;

	for (int i = 0; i < 10; i++)
	{
		Push(S, i);
	}

	while (!IsEmpty(S))
		cout << Pop(S) << endl;


}