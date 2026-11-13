#pragma once
#include <cstddef>
#include <vector>

struct TreeNode{
  int value
  TreeNode* left = nullptr;
  TreeNode* right = nullptr;
};

std::vector<int> preorder(const TreeNode* root);
std::vector<int> inorder(const TreeNode* root);
std::vector<int> postorder(const TreeNode* root);
std::vector<int> levelOrder(const TreeNode* root);
std::size_t countNodes(const TreeNode* root);
std::size_t countLeaves(const TreeNode* root);
int treeHeight(const TreeNode* root);
long long sumValues(const TreeNode* root);
void destroyTree(TreeNode*& root);
