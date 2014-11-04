//============================================================================
// Name        : path-sum.cpp
// Author      : Xichen Shi
// Version     :
// Copyright   : Your copyright notice
// Description : Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void pathSumHelper(TreeNode *node, int sum, vector<int> path, vector<vector<int> > &paths) {
	if(node == NULL) return;

	path.push_back(node->val);
	if(node->val == sum && node->right == NULL && node->left == NULL) {
		paths.push_back(path);
	}

	if(node->left) {
		pathSumHelper(node->left, sum-node->val, path, paths);
	}
	if(node->right) {
		pathSumHelper(node->right, sum-node->val, path, paths);
	}
}

vector<vector<int> > pathSum(TreeNode *root, int sum) {
	vector<vector<int> > paths;
	vector<int> path;
	pathSumHelper(root, sum, path ,paths);
	return paths;
}

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
