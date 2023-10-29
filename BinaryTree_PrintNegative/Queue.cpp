#include "Queue.h"
using namespace std;

void TQueue::InitQueue()
{
	Head = nullptr;
	Tail = nullptr;
}

bool TQueue::IsEmpty()
{
	return Head == nullptr;
}

void TQueue::EnQueue(int val)
{
	if (IsEmpty())
	{
		Head = new TQueueItem;
		Head->Value = val;
		Head->Next = nullptr;
		Head->Prev = nullptr;
		Tail = Head;
	}
	else
	{
		Tail->Next = new TQueueItem();
		Tail->Next->Value = val;
		Tail->Next->Next = nullptr;
		Tail->Next->Prev = Tail->Next;
		Tail = Tail->Next;
	}
}

bool TQueue::DeQueue(int& val)
{
	if (IsEmpty()) return false;

	val = Head->Value;
	TQueueItem* t = Head;
	Head = Head->Next;
	delete t;

	if (Head)
		Head->Prev = nullptr;
	else
		Tail = Head;

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

void TQueue::DestroyQueue()
{
	_DestroyQueue(Head);
	Tail = Head;
}
