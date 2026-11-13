#include <iostream>
#include <vector>
 
#include "TreeExplorer.h"
 
namespace {
 
int failures = 0;
int checks = 0;
 
using Seq = std::vector<int>;
 
void check(bool ok, const char* what) {
    ++checks;
    if (!ok) {
        ++failures;
        std::cout << "FAIL: " << what << '\n';
    }
}
 
TreeNode* mk(int v, TreeNode* l = nullptr, TreeNode* r = nullptr) {
    TreeNode* n = new TreeNode{v};
    n->left = l;
    n->right = r;
    return n;
}
 
void expectAll(const TreeNode* t, const Seq& pre, const Seq& in, const Seq& post,
               const Seq& lvl, std::size_t nodes, std::size_t leaves, int height,
               long long sum, const char* name) {
    std::cout << "Testing: " << name << '\n';
    check(preorder(t) == pre, "preorder");
    check(inorder(t) == in, "inorder");
    check(postorder(t) == post, "postorder");
    check(levelOrder(t) == lvl, "levelOrder");
    check(countNodes(t) == nodes, "countNodes");
    check(countLeaves(t) == leaves, "countLeaves");
    check(treeHeight(t) == height, "treeHeight");
    check(sumValues(t) == sum, "sumValues");
}
 
TreeNode* leftChain() { return mk(1, mk(2, mk(3, mk(4)))); }
TreeNode* rightChain() { return mk(1, nullptr, mk(2, nullptr, mk(3, nullptr, mk(4)))); }
 
TreeNode* duplicateTree() {
    return mk(7, mk(0, mk(-3), mk(7)), mk(7, nullptr, mk(-3)));
}
 
TreeNode* extraTree() { return mk(1, mk(2, mk(4), mk(5)), mk(3, mk(6))); }
 
}
