#include <iostream>
#include <fstream>
#include "BinaryTree.h"
#include "Queue.h"
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
	queue.Init();
	
	int a = 0;

}

int main()
{
	TreeNode* tree = nullptr;
	FillTree(tree);
	PrintNegative(tree);
	cout << "H" << endl;
}

