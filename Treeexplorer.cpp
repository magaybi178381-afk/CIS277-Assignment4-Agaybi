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

}
