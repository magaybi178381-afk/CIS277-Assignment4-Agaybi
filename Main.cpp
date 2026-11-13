#include <iostream>
#include <string>
#include <vector>
 
#include "TreeExplorer.h"

namespace {
 
TreeNode* makeNode(int value, TreeNode* left = nullptr, TreeNode* right = nullptr) {
    TreeNode* node = new TreeNode{value};
    node->left = left;
    node->right = right;
    return node;
}
 
void printSequence(const std::string& label, const std::vector<int>& values) {
    std::cout << "  " << label << ": ";
    for (std::size_t i = 0; i < values.size(); ++i) {
        if (i > 0) std::cout << ' ';
        std::cout << values[i];
    }
    std::cout << '\n';
}
 
void report(const std::string& name, const TreeNode* root) {
    std::cout << name << '\n';
    printSequence("Preorder   ", preorder(root));
    printSequence("Inorder    ", inorder(root));
    printSequence("Postorder  ", postorder(root));
    printSequence("Level order", levelOrder(root));
    std::cout << "  Nodes: " << countNodes(root) << '\n';
    std::cout << "  Leaves: " << countLeaves(root) << '\n';
    std::cout << "  Height (levels): " << treeHeight(root) << '\n';
    std::cout << "  Sum: " << sumValues(root) << "\n\n";
}
 
}

int main() {
    TreeNode* treeA = makeNode(50,
                               makeNode(30, makeNode(20), makeNode(40)),
                               makeNode(70, makeNode(60), makeNode(80)));
 
    TreeNode* treeB = makeNode(10,
                               makeNode(30, nullptr, makeNode(5)),
                               makeNode(20, nullptr, makeNode(15)));
 
    report("Tree A (BST)", treeA);
    report("Tree B (binary tree, not BST)", treeB);
 
    destroyTree(treeA);
    destroyTree(treeB);
 
    std::cout << "Tree A root is " << (treeA == nullptr ? "null" : "NOT null") << '\n';
    std::cout << "Tree B root is " << (treeB == nullptr ? "null" : "NOT null") << '\n';
    return 0;
}
 

