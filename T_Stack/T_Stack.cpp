#include <iostream>
#define Size 10

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

// Заповнює стек рандомними значеннями
void FillStack(TStack*& S, int size)
{
	for (int i = 0; i < size; i++)
	{
		int num = rand() % 10 + 1;
		Push(S, num);
	}
}

// Друкує елементи стеку
void PrintStack(TStack*& S)
{
	TStack* temp = NULL;

	while (!IsEmpty(S))
	{
		int val = Pop(S);
		Push(temp, val);
	}

	while (!IsEmpty(temp))
	{
		int val = Pop(temp);
		cout << val << " ";
		Push(S, val);
	}
}

// Перевіряє чи є число квадратом іншого числа
bool IsSquare(int num)
{
	int sRoot = sqrt(num);
	return sRoot * sRoot == num;
}

// Повертає новий стек без елементів, що є квадратами чисел
TStack* DeleteSquares(TStack*& S)
{
	TStack* temp = NULL;
	TStack* result = NULL;

	while (!IsEmpty(S))
	{
		int val = Pop(S);
		Push(temp, val);
	}

	while (!IsEmpty(temp))
	{
		int val = Pop(temp);
		Push(S, val);

		if (!IsSquare(val))
			Push(result, val);
	}

	return result;
}

int main()
{
	setlocale(LC_ALL, "ukr");
	srand(time(NULL));

	TStack* S = NULL;
	FillStack(S, Size);
	cout << "Стек: ";
	PrintStack(S);

	TStack* result = DeleteSquares(S);
	cout << "\nНовий стек: ";
	PrintStack(result);

}