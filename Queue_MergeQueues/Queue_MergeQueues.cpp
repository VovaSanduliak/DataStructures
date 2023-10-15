#include <fstream>
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

bool DeQueue(TQueue& Q, int& value)
{
	if (IsEmpty(Q)) return false;

	value = Q.Head->Value;
	TQueueItem* t = Q.Head;
	Q.Head = Q.Head->Next;
	delete t;

	if (Q.Head)
		Q.Head->Prev = nullptr;
	else
		Q.Tail = Q.Head;

	return true;
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

void Fill(TQueue& Q)
{
	ifstream file("data.txt");

	if (!file)
	{
		cerr << "Couldn't open the file" << endl;
	}

	int input;
	while (file >> input)
	{
		EnQueue(Q, input);
	}
}

void SeparateQueue(TQueue& Queue, TQueue& Queue1, TQueue& Queue2)
{
	TQueue *tempQueue = new TQueue;
	tempQueue->Head = nullptr;
	tempQueue->Tail = nullptr;

	int currValue = 0;

	while (!IsEmpty(Queue))
	{
		DeQueue(Queue, currValue);

		if (currValue > 0)
			EnQueue(Queue1, currValue);
		else
			EnQueue(Queue2, currValue);

		EnQueue(*tempQueue, currValue);
	}

	/*while (!IsEmpty(tempQueue))
	{
		DeQueue(tempQueue, currValue);
		EnQueue(Queue, currValue);
	}*/

	Queue.Head = tempQueue->Head;
	Queue.Tail = tempQueue->Tail;
	delete tempQueue;
}

void Output(TQueue S)
{

}

int main()
{
	TQueue Queue = InitQueue();
	TQueue Queue1 = InitQueue();
	TQueue Queue2 = InitQueue();
	Fill(Queue);
	SeparateQueue(Queue, Queue1, Queue2);

	

	cout << "" << endl;
}