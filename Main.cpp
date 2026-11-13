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

