#include "TreeExplorer.h"
 
#include <algorithm>
#include <queue>

namespace{

void preorderHelper(const TreeNode* node, std::vector<int>& out) {
    if (node == nullptr) return;
    out.push_back(node->value);
    preorderHelper(node->left, out);
    preorderHelper(node->right, out);
}

void inorderHelper(const TreeNode* node, std::vector<int>& out) {
    if (node == nullptr) return;
    inorderHelper(node->left, out);
    out.push_back(node->value);
    inorderHelper(node->right, out);
}

void postorderHelper(const TreeNode* node, std::vector<int>& out) {
    if (node == nullptr) return;
    postorderHelper(node->left, out);
    postorderHelper(node->right, out);
    out.push_back(node->value);
}

}

std::vector<int> preorder(const TreeNode* root) {
    std::vector<int> out;
    preorderHelper(root, out);
    return out;
}

std::vector<int> inorder(const TreeNode* root) {
    std::vector<int> out;
    inorderHelper(root, out);
    return out;
}

std::vector<int> postorder(const TreeNode* root) {
    std::vector<int> out;
    postorderHelper(root, out);
    return out;
}




