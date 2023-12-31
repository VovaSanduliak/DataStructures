#include <iostream>
using namespace std;

struct Node
{
	int Data;
	Node* Left;
	Node* Right;
};

void PreOrder(Node* root)
{
	if (root)
	{
		cout << root->Data << endl;
		PreOrder(root->Left);
		PreOrder(root->Right);
	}
}

void PostOrder(Node* root)
{
	if (root)
	{
		PostOrder(root->Left);
		PostOrder(root->Right);
		cout << root->Data << endl;
	}
}

void InOrder(Node* root)
{
	if (root)
	{
		InOrder(root->Left);
		cout << root->Data << endl;
		InOrder(root->Right);
	}
}