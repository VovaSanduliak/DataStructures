#include <iostream>
using namespace std;

struct TreeNode
{
	int Data;
	TreeNode* Left;
	TreeNode* Right;
};

void PreOrder(TreeNode* root);

void PostOrder(TreeNode* root);

void InOrder(TreeNode* root);
