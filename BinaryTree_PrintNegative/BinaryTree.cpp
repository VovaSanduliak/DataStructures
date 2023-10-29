#include "BinaryTree.h"
using namespace std;

void PreOrder(TreeNode* root)
{
	if (root)
	{
		cout << root->Data << endl;
		PreOrder(root->Left);
		PreOrder(root->Right);
	}
}

void PostOrder(TreeNode* root)
{
	if (root)
	{
		PostOrder(root->Left);
		PostOrder(root->Right);
		cout << root->Data << endl;
	}
}

void InOrder(TreeNode* root)
{
	if (root)
	{
		InOrder(root->Left);
		cout << root->Data << endl;
		InOrder(root->Right);
	}
}