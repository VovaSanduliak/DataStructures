#include "Queue.h"
using namespace std;

template <typename T>
void TQueue<T>::Init()
{
	Head = nullptr;
	Tail = nullptr;
}

template <typename T>
bool TQueue<T>::IsEmpty()
{
	return Head == nullptr;
}

template <typename T>
void TQueue<T>::EnQueue(T& val)
{
	if (IsEmpty())
	{
		Head = new TQueueItem<T>;
		Head->Value = val;
		Head->Next = nullptr;
		Head->Prev = nullptr;
		Tail = Head;
	}
	else
	{
		Tail->Next = new TQueueItem<T>;
		Tail->Next->Value = val;
		Tail->Next->Next = nullptr;
		Tail->Next->Prev = Tail->Next;
		Tail = Tail->Next;
	}
}

template <typename T>
bool TQueue<T>::DeQueue(T& val)
{
	if (IsEmpty()) return false;

	val = Head->Value;
	TQueueItem<T>* t = Head;
	Head = Head->Next;
	delete t;

	if (Head)
		Head->Prev = nullptr;
	else
		Tail = Head;

	return true;
}

template <typename T>
void _DestroyQueue(TQueueItem<T>*& item)
{
	if (item)
	{
		_DestroyQueue(item->Next);
		delete item;
		item = nullptr;
	}
}

template <typename T>
void TQueue<T>::DestroyQueue()
{
	_DestroyQueue(Head);
	Tail = Head;
}
