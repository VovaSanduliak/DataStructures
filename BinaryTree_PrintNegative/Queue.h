#include <fstream>
#include <iostream>
using namespace std;

template <typename T>
struct TQueueItem
{
	T Value;
	TQueueItem* Next;
	TQueueItem* Prev;
};

template <typename T>
struct TQueue
{
	TQueueItem<T>* Head;
	TQueueItem<T>* Tail;

	TQueue<T>()
	{
		Head = nullptr;
		Tail = nullptr;
	}

	void Init();
	bool IsEmpty();
	void EnQueue(T& val);
	bool DeQueue(T& value);
	void DestroyQueue();
};

