#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct TRingListItem
{
	string Value;
	TRingListItem* Next;
	TRingListItem* Prev;
};

struct TRingList
{
	TRingListItem* First;
};

struct TRingListIterator
{
	TRingListItem* pointer;
};

TRingListIterator InitIterator()
{
	TRingListIterator r;
	r.pointer = nullptr;
	return r;
}

inline int IsValid(TRingListIterator It)
{
	return It.pointer != nullptr;
}

void MoveNext(TRingListIterator& It)
{
	if (IsValid(It))
		It.pointer = It.pointer->Next;
}

void MovePrevious(TRingListIterator& It)
{
	if (IsValid(It))
		It.pointer = It.pointer->Prev;
}

string GetValue(const TRingListIterator& It)
{
	if (IsValid(It))
		return It.pointer->Value;
}

void SetValue(TRingListIterator& It, string value)
{
	if (IsValid(It))
		It.pointer->Value = value;
}

TRingListIterator GetBegin(TRingList& L)
{
	TRingListIterator r;
	r.pointer = L.First;
	return r;
}

TRingList InitRingList()
{
	TRingList l;
	l.First = NULL;
	return l;
}

void AddListItem(TRingList& List, string val)
{
	if (!List.First)
	{
		List.First = new TRingListItem();
		List.First->Value = val;
		List.First->Next = List.First;
		List.First->Prev = List.First;
	}
	else
	{
		List.First->Prev->Next = new TRingListItem();
		List.First->Prev->Next->Value = val;
		List.First->Prev->Next->Prev = List.First->Prev;
		List.First->Prev->Next->Next = List.First;
		List.First->Prev = List.First->Prev->Next;
	}
}

void DeleteItem(TRingList& L, TRingListIterator& It)
{
	if (!IsValid(It))
		return;

	if (It.pointer == L.First)
		L.First = It.pointer->Next;

	TRingListItem* t1 = It.pointer->Prev;
	TRingListItem* t2 = It.pointer->Next;
	
	delete It.pointer;
	It.pointer = t2;

	if (t2 != nullptr)
		t2->Prev = t1;

	if (t1 != nullptr)
		t1->Next = t2;
}

void _DeleteListItem(TRingList& List, TRingListItem& Item)
{
	if (&Item != List.First)
	{
		Item.Prev->Next = Item.Next;
		Item.Next->Prev = Item.Prev;
		delete &Item;
	}
	else
	{
		Item.Prev->Next = Item.Next;
		Item.Next->Prev = Item.Prev;
		List.First = Item.Next;
		delete &Item;
	}
}

void DestroyList(TRingList& List)
{
	if (!List.First)
		return;

	TRingListItem* curr = List.First;
	TRingListItem* next;

	do
	{
		next = curr->Next;
		delete curr;
		curr = next;
	} while (curr != List.First);

	List.First = nullptr;
}

void PrintList(TRingList& List)
{
	TRingListItem* t = List.First;

	do
	{
		cout << t->Value << " ";
		t = t->Next;
	} while (t != List.First);
}

void FillList(TRingList& List, string fileName)
{
	ifstream file(fileName);

	if (!file)
	{
		cerr << "Couldn't open the file" << endl;
	}

	string line;

	while (getline(file, line))
	{
		AddListItem(List, line);
	}
}

int main()
{
	TRingList participants = InitRingList();
	TRingList prizes = InitRingList();
	FillList(participants, "Participants.txt");
	FillList(prizes, "Prizes.txt");

	int N, K, T;

	cout << "Enter:\nN (number of winners)\nK (each Kth is winner)\nT (each winner gets each Tth prize):" << endl;
	cin >> N >> K >> T;

	//TRingListItem* participant = participants.First;
	//TRingListItem* prize = prizes.First;
	TRingListIterator participant = GetBegin(participants);
	TRingListIterator prize = GetBegin(prizes);

	ofstream winnersFile;
	winnersFile.open("Winners.txt");

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j < K; j++)
		{
			//participant = participant->Next;
			MoveNext(participant);
		}

		for (int j = 1; j < T; j++)
		{
			//prize = prize->Next;
			MoveNext(prize);
		}

		if (winnersFile)
		{
			//winnersFile << "Winner " << i << ": " << participant->Value << "\nPrize: " << prize->Value << endl << endl;
			winnersFile << "Winner " << i << ": " << GetValue(participant) << "\nPrize: " << GetValue(prize) << endl << endl;
		}

		//TRingListItem* tempParticipant = participant->Next;
		//DeleteListItem(participants, *participant);
		TRingListIterator tempParticipant = participant;
		DeleteItem(participants, tempParticipant); //

		//participant = tempParticipant;
		//prize = prize->Next;
		participant = tempParticipant;
		//MoveNext(participant);
		MoveNext(prize);
	}

	DestroyList(participants);
	DestroyList(prizes);
	cout << "Result has been written in the file:" << endl;
}