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

void DeleteListItem(TRingList& List, TRingListItem& Item)
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

	int N = 5;
	int K = 7;
	int T = 10;

	TRingListItem* participant = participants.First;
	TRingListItem* prize = prizes.First;

	ofstream winnersFile;
	winnersFile.open("Winners.txt");

	cout << "Results:" << endl;

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j < K; j++)
		{
			participant = participant->Next;
		}

		for (int j = 1; j < T; j++)
		{
			prize = prize->Next;
		}


		if (winnersFile)
		{
			winnersFile 
				<< "Winner " << i << ": " << participant->Value << "\nPrize: " << prize->Value 
				<< endl << endl;
		}

		TRingListItem* tempParticipant = participant->Next;
		DeleteListItem(participants, *participant);

		participant = tempParticipant;
		prize = prize->Next;
	}

	DestroyList(participants);
	DestroyList(prizes);
	int a = 0;
}