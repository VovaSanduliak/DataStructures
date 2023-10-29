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

	void InitQueue();
	bool IsEmpty();
	void EnQueue(int val);
	bool DeQueue(int& value);
	void DestroyQueue();
};

