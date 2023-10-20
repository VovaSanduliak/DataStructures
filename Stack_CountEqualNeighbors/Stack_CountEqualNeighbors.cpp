#include <fstream>
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

bool Pop(TStack*& S, int& value)
{
	if (IsEmpty(S)) return false;

	value = S->Value;
	TStack* t = S->Next;
	delete S;
	S = t;

	return true;
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

void Output(TStack S)
{
	while (!IsEmpty(&S))
	{

	}
}

void Fill(TStack*& S)
{
	ifstream file("data.txt");

	if (!file)
	{
		cerr << "Couldn't open the file" << endl;
	}

	int input;
	while (file >> input)
	{
		Push(S, input);
	}
}

int CountEqualNeighbors(TStack*& S)
{
	int count	 = 0;
	int prevPrev = 0;
	int prev	 = 0;
	int curr	 = 0;
	TStack* tempStack = new TStack();

	if (!IsEmpty(S))
	{
		Pop(S, prevPrev);
		Push(tempStack, prevPrev);
	}

	if (!IsEmpty(S))
	{
		Pop(S, prev);
		Push(tempStack, prev);
	}

	while (!IsEmpty(S))
	{
		Pop(S, curr);
		Push(tempStack, prev);

		if (curr == prevPrev)
			count++;

		prevPrev = prev;
		prev = curr;
	}

	while (!IsEmpty(tempStack))
	{
		Pop(tempStack, curr);
		Push(S, curr);
	}

	return count;
}

void main()
{
	TStack* S = nullptr;
	Fill(S);

	cout << CountEqualNeighbors(S) << endl;


}