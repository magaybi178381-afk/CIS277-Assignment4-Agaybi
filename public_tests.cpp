// Public behavioral checks. These are examples, not an exhaustive grading suite.
#include "TreeExplorer.h"
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#if __cplusplus <= 202002L
#error "Select a C++23-capable compiler in C++23 mode."
#endif

namespace {
int checks = 0;
void require(bool ok, const std::string& label) {
    ++checks;
    if (!ok) throw std::runtime_error(label);
}
void checkTree(TreeNode* root, const std::vector<int>& pre,
               const std::vector<int>& in, const std::vector<int>& post,
               const std::vector<int>& level, std::size_t count,
               std::size_t leaves, int height, long long sum,
               const std::string& name) {
    require(preorder(root) == pre, name + ": preorder");
    require(inorder(root) == in, name + ": inorder");
    require(postorder(root) == post, name + ": postorder");
    require(levelOrder(root) == level, name + ": level order");
    require(countNodes(root) == count, name + ": node count");
    require(countLeaves(root) == leaves, name + ": leaf count");
    require(treeHeight(root) == height, name + ": level-based height");
    require(sumValues(root) == sum, name + ": sum");
    auto snapshot = inorder(root);
    if (!snapshot.empty()) snapshot[0] = 123456;
    require(inorder(root) == in, name + ": independent returned vector");
    require(preorder(root) == pre && postorder(root) == post && levelOrder(root) == level,
            name + ": repeat calls preserve data and shape");
}
void cleanup(TreeNode*& root, const std::string& name) {
    destroyTree(root);
    require(root == nullptr, name + ": cleanup resets caller pointer");
    destroyTree(root);
    require(root == nullptr, name + ": repeated cleanup is safe");
}
}

int main() {
    try {
        TreeNode* tree = nullptr;
        checkTree(tree, {}, {}, {}, {}, 0, 0, 0, 0, "empty");
        cleanup(tree, "empty");
        tree = new TreeNode{-7};
        checkTree(tree, {-7}, {-7}, {-7}, {-7}, 1, 1, 1, -7, "singleton");
        cleanup(tree, "singleton");

        tree = new TreeNode{50};
        tree->left = new TreeNode{30}; tree->right = new TreeNode{70};
        tree->left->left = new TreeNode{20}; tree->left->right = new TreeNode{40};
        tree->right->left = new TreeNode{60}; tree->right->right = new TreeNode{80};
        checkTree(tree, {50,30,20,40,70,60,80}, {20,30,40,50,60,70,80},
                  {20,40,30,60,80,70,50}, {50,30,70,20,40,60,80}, 7,4,3,350, "lesson tree");
        cleanup(tree, "lesson tree");

        tree = new TreeNode{10};
        tree->left = new TreeNode{30}; tree->right = new TreeNode{20};
        tree->left->right = new TreeNode{5}; tree->right->right = new TreeNode{15};
        checkTree(tree, {10,30,5,20,15}, {30,5,10,20,15}, {5,30,15,20,10},
                  {10,30,20,5,15}, 5,2,3,80, "non-BST");
        cleanup(tree, "non-BST");

        tree = new TreeNode{3}; tree->left = new TreeNode{2};
        tree->left->left = new TreeNode{1}; tree->left->left->left = new TreeNode{0};
        checkTree(tree, {3,2,1,0}, {0,1,2,3}, {0,1,2,3}, {3,2,1,0}, 4,1,4,6, "left chain");
        cleanup(tree, "left chain");

        tree = new TreeNode{0}; tree->right = new TreeNode{1};
        tree->right->right = new TreeNode{2}; tree->right->right->right = new TreeNode{3};
        checkTree(tree, {0,1,2,3}, {0,1,2,3}, {3,2,1,0}, {0,1,2,3}, 4,1,4,6, "right chain");
        cleanup(tree, "right chain");

        tree = new TreeNode{0}; tree->left = new TreeNode{-2}; tree->right = new TreeNode{-2};
        tree->left->right = new TreeNode{4};
        checkTree(tree, {0,-2,4,-2}, {-2,4,0,-2}, {4,-2,-2,0}, {0,-2,-2,4}, 4,2,3,0, "duplicates and negatives");
        cleanup(tree, "duplicates and negatives");

        // Values fit int, but their sum requires more than a 32-bit signed int.
        tree = new TreeNode{2000000000}; tree->left = new TreeNode{2000000000};
        checkTree(tree, {2000000000,2000000000}, {2000000000,2000000000},
                  {2000000000,2000000000}, {2000000000,2000000000}, 2,1,2,4000000000LL, "wide sum");
        cleanup(tree, "wide sum");
        std::cout << "PASS: " << checks << " public behavioral checks\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "FAIL: " << e.what() << '\n';
        return 1;
    }
}
