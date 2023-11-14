#include <iostream>
using namespace std;

struct TQueueItem
{
	int Value;
	TQueueItem* Next;
	TQueueItem* Prev;
};

struct TQueue
{
	TQueueItem* Head;
	TQueueItem* Tail;
};

TQueue InitQueue()
{
	TQueue r;
	r.Head = nullptr;
	r.Tail = nullptr;
	return r;
}

bool IsEmpty(const TQueue& Q)
{
	return Q.Head == nullptr;
}

void EnQueue(TQueue& Q, int v)
{
	if (IsEmpty(Q))
	{
		Q.Head = new TQueueItem;
		Q.Head->Value = v;
		Q.Head->Next = nullptr;
		Q.Head->Prev = nullptr;
		Q.Tail = Q.Head;
	}
	else
	{
		Q.Tail->Next = new TQueueItem();
		Q.Tail->Next->Value = v;
		Q.Tail->Next->Next = nullptr;
		Q.Tail->Next->Prev = Q.Tail->Next;
		Q.Tail = Q.Tail->Next;
	}
}

int DeQueue(TQueue& Q)
{
	if (IsEmpty(Q))
		return 0;

	int result = Q.Head->Value;
	TQueueItem* t = Q.Head;
	Q.Head = Q.Head->Next;
	delete t;

	if (Q.Head)
		Q.Head->Prev = nullptr;
	else
		Q.Tail = Q.Head;

	return result;
}

void _DestroyQueue(TQueueItem*& T)
{
	if (T)
	{
		_DestroyQueue(T->Next);
		delete T;
		T = nullptr;
	}
}

void DestroyQueue(TQueue& Q)
{
	_DestroyQueue(Q.Head);
	Q.Tail = Q.Head;
}

// Заповнює чергу рандомними елементами від 1 до 10
void FillQueue(TQueue& Q, int size)
{
	for (int i = 0; i < size; i++)
	{
		int num = rand() % 10 + 1;
		EnQueue(Q, num);
	}
}

// Друкує чергу
void PrintQueue(TQueue& Q)
{
	TQueue temp = InitQueue();

	while (!IsEmpty(Q))
	{
		int val = DeQueue(Q);
		EnQueue(temp, val);
	}

	while (!IsEmpty(temp))
	{
		int val = DeQueue(temp);
		cout << val << " ";
		EnQueue(Q, val);
	}
}

// Перевіряє чи є число простим
bool isPrime(int num)
{
	if (num == 0 || num == 1)
		return false;

	if (num == 2 || num == 3 || num == 5 || num == 7)
		return true;

	if (num % 2 == 0)
		return false;

	for (int i = 3; i < num; i += 2)
	{
		if (num % i == 0)
			return false;
	}

	return true;
}

// Повертає нову чергу з елементів черги Q, які є простими числами
TQueue GetPrimeNumbers(TQueue& Q)
{
	TQueue temp = InitQueue();
	TQueue result = InitQueue();

	while (!IsEmpty(Q))
	{
		int val = DeQueue(Q);
		EnQueue(temp, val);
	}

	while (!IsEmpty(temp))
	{
		int val = DeQueue(temp);
		EnQueue(Q, val);
		
		if (isPrime(val))
			EnQueue(result, val);
	}

	return result;
}

int main()
{
	setlocale(LC_ALL, "ukr");
	srand(time(NULL));

	TQueue Queue = InitQueue();
	FillQueue(Queue, 10);
	cout << "Черга: ";
	PrintQueue(Queue);
	
	TQueue newQueue = GetPrimeNumbers(Queue);
	cout << "\nНова черга (прості числа): ";
	PrintQueue(newQueue);
}