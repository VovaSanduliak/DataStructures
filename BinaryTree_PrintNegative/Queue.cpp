#include "Queue.h"
using namespace std;

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