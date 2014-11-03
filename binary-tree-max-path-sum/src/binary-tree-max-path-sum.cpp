//============================================================================
// Name        : binary-tree-min-path-sum.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <climits>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

int maxPathSumToLeaf(TreeNode *node) {
    if(node==NULL) return 0;
    int sum = max(max(maxPathSumToLeaf(node->left),maxPathSumToLeaf(node->right)),0)+node->val;
    return sum;
}

int maxPathSum(TreeNode *root) {
    if(root == NULL) return INT_MIN;

    int maxleft = maxPathSum(root->left);
    int maxright = maxPathSum(root->right);
    int maxroot = max(maxPathSumToLeaf(root->left),0)+max(maxPathSumToLeaf(root->right),0)+root->val;

    return max(max(maxleft,maxright),maxroot);
}

int main() {
    TreeNode node(2);
    node.right = new TreeNode(1);
    node.left = new TreeNode(3);
    cout<<maxPathSum(&node)<<endl;
	return 0;
}
