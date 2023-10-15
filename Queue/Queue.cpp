#include <iostream>

struct TQueueItem
{
	int Value;
	TQueueItem *Next;
	TQueueItem *Prev;
};

struct TQueue
{
	TQueueItem *Head;
	TQueueItem *Tail;
};

TQueue InitQueue()
{
	TQueue r;
	r.Head = NULL;
	r.Tail = NULL;
	return r;
}

int IsEmpty(const TQueue& Q)
{
	return Q.Head == NULL;
}

void EnQueue(TQueue& Q, int v)
{
	if (!Q.Tail)
	{
		Q.Head = new TQueueItem;
		Q.Head->Value = v;
		Q.Head->Next = NULL;
		Q.Head->Prev = NULL;
		Q.Tail = Q.Head;
	}
	else
	{
		Q.Tail->Next = new TQueueItem;
		Q.Tail->Next->Value = v;
		Q.Tail->Next->Next = NULL;
		Q.Tail->Next->Prev = Q.Tail->Next;
		Q.Tail = Q.Tail->Next;
	}
}

int DeQueue(TQueue& Q)
{
	if (IsEmpty(Q))
		return 0;

	int result = Q.Head->Value;
	TQueueItem *t = Q.Head;
	Q.Head = Q.Head->Next;
	delete t;

	if (Q.Head)
		Q.Head->Prev = NULL;
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
		T = NULL;
	}
}

void DestroyQueue(TQueue &Q)
{
	_DestroyQueue(Q.Head);
	Q.Tail = Q.Head;
}

int main()
{

}