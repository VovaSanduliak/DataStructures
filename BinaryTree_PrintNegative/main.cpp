#include <iostream>
#include <fstream>
#include "BinaryTree.h"
#include "Queue.h"
#define NEWLINE cout << endl;
using namespace std;

void Insert(TreeNode*& root, int val)
{
	if (root)
	{
		if (val < root->Data)
			Insert(root->Left, val);
		else if (val > root->Data)
			Insert(root->Right, val);
	}
	else
	{
		root = new TreeNode();
		root->Data = val;

	}
}

void FillTree(TreeNode*& root)
{
	ifstream file("data.txt");

	if (!file)
		cerr << "Couldn't open the file" << endl;

	int input;
	while (file >> input)
	{
		Insert(root, input);
	}
}

void PrintNegative(TreeNode*& root)
{
	if (root == nullptr) return;

	TQueue<TreeNode> queue;
	queue.EnQueue(*root);
	
	int count = 0;
	int elemsOnLevel = 1;

	while (!queue.IsEmpty())
	{
		TreeNode node;
		queue.DeQueue(node);

		if (node.Data < 0)
			cout << node.Data << " ";

		if (node.Left)
			queue.EnQueue(*node.Left);
		if (node.Right)
			queue.EnQueue(*node.Right);

		count++;
		if (count == elemsOnLevel)
		{
			count = 0;
			elemsOnLevel *= 2;
			NEWLINE
		}
	}

	int a = 0;
}

int main()
{
	TreeNode* tree = nullptr;
	FillTree(tree);
	PrintNegative(tree);
}

