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

std::vector<int> levelOrder(const TreeNode* root) {
    std::vector<int> out;
    if (root == nullptr) return out;
    std::queue<const TreeNode*> pending;
    pending.push(root);
    while (!pending.empty()) {
        const TreeNode* node = pending.front();
        pending.pop();
        out.push_back(node->value);
        if (node->left != nullptr) pending.push(node->left);
        if (node->right != nullptr) pending.push(node->right);
    }
    return out;
}

std::size_t countNodes(const TreeNode* root) {
    if (root == nullptr) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

std::size_t countLeaves(const TreeNode* root) {
    if (root == nullptr) return 0;
    if (root->left == nullptr && root->right == nullptr) return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}

int treeHeight(const TreeNode* root) {
    if (root == nullptr) return 0;
    return 1 + std::max(treeHeight(root->left), treeHeight(root->right));
}

long long sumValues(const TreeNode* root) {
    if (root == nullptr) return 0;
    return static_cast<long long>(root->value) + sumValues(root->left) +
           sumValues(root->right);
}

void destroyTree(TreeNode*& root) {
    if (root == nullptr) return;
    destroyTree(root->left);
    destroyTree(root->right);
    delete root;
    root = nullptr;
}


