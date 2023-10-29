#include <iostream>
#include <fstream>
#include "Queue.h"
#include "BinaryTree.h"
using namespace std;

void Insert(TreeNode<int>*& root, int val)
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
		root = new TreeNode<int>(val);
	}
}

void FillTree(TreeNode<int>*& root)
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

void PrintNegative(TreeNode<int>*& root)
{
	if (root == nullptr) return;

	
	int a = 0;

}

int main()
{
	TreeNode<int>* tree = nullptr;
	FillTree(tree);
	PrintNegative(tree);
	cout << "H" << endl;
}

