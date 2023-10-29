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

TQueue InitQueue();

bool IsEmpty(const TQueue& Q);


void EnQueue(TQueue& Q, int v);


bool DeQueue(TQueue& Q, int& value);


void _DestroyQueue(TQueueItem*& T);


void DestroyQueue(TQueue& Q);