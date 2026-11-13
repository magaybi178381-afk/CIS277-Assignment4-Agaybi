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

int main() {
    {
        TreeNode* t = nullptr;
        expectAll(t, {}, {}, {}, {}, 0, 0, 0, 0, "empty tree");
        destroyTree(t);
        destroyTree(t);
        check(t == nullptr, "null root stays null after repeated destroy");
    }

    {
        TreeNode* t = mk(-4);
        expectAll(t, {-4}, {-4}, {-4}, {-4}, 1, 1, 1, -4, "singleton -4");
        destroyTree(t);
        check(t == nullptr, "singleton root cleared");
    }

    {
        TreeNode* t = leftChain();
        expectAll(t, {1, 2, 3, 4}, {4, 3, 2, 1}, {4, 3, 2, 1}, {1, 2, 3, 4}, 4, 1, 4,
                  10, "left-only chain");
        destroyTree(t);
        check(t == nullptr, "left chain root cleared");
    }
    {
        TreeNode* t = rightChain();
        expectAll(t, {1, 2, 3, 4}, {1, 2, 3, 4}, {4, 3, 2, 1}, {1, 2, 3, 4}, 4, 1, 4,
                  10, "right-only chain");
        destroyTree(t);
        check(t == nullptr, "right chain root cleared");
    }

    {
        TreeNode* t = duplicateTree();
        expectAll(t, {7, 0, -3, 7, 7, -3}, {-3, 0, 7, 7, 7, -3}, {-3, 7, 0, -3, 7, 7},
                  {7, 0, 7, -3, 7, -3}, 6, 3, 3, 15, "duplicates, zero, negatives");
        destroyTree(t);
    }

    {
        TreeNode* t = extraTree();
        Seq first = preorder(t);
        first[0] = 999;
        first.push_back(-1);
        first.clear();
        check(preorder(t) == Seq({1, 2, 4, 5, 3, 6}), "preorder unchanged after edit");
        Seq lvl = levelOrder(t);
        lvl[0] = 42;
        check(levelOrder(t) == Seq({1, 2, 3, 4, 5, 6}), "levelOrder unchanged after edit");
        check(inorder(t) == inorder(t), "repeated inorder equal");
        check(t->value == 1 && t->left->value == 2 && t->right->value == 3,
              "tree values unchanged");
        check(countNodes(t) == 6 && sumValues(t) == 21, "measurements unchanged");
        destroyTree(t);
    }

    {
        TreeNode* t = extraTree();
        destroyTree(t);
        check(t == nullptr, "first destroy clears root");
        t = mk(5, mk(6), mk(7));
        expectAll(t, {5, 6, 7}, {6, 5, 7}, {6, 7, 5}, {5, 6, 7}, 3, 2, 2, 18,
                  "rebuilt tree");
        destroyTree(t);
        check(t == nullptr, "second destroy clears root");
    }

    {
        TreeNode* t = extraTree();
        expectAll(t, {1, 2, 4, 5, 3, 6}, {4, 2, 5, 1, 6, 3}, {4, 5, 2, 6, 3, 1},
                  {1, 2, 3, 4, 5, 6}, 6, 3, 3, 21,
                  "extra tree (node 3 has one child, so it is not a leaf)");
        destroyTree(t);
    }

    std::cout << '\n' << (checks - failures) << "/" << checks << " checks passed\n";
    return failures == 0 ? 0 : 1;
}
