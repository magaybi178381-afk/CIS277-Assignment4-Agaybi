# CIS-277 Assignment 4: Binary Tree Explorer

## Student
Name: Marc Agaybi

## Design

### Initial plan (written before implementation — REPLACE WITH YOUR OWN WORDING)
- **Node fields:** int value, TreeNode* left, TreeNode* right, both pointers defaulting to nullptr.
- **Empty-tree base case:** every recursive function returns immediately (empty vector / 0) when the node pointer is nullptr.
- **Collecting results:** each depth-first traversal creates one std::vector<int>, passes it by reference to a file-private helper, and the helper appends one value per visit. No subtree vectors are copied or concatenated.
- **Level order:** a std::queue<const TreeNode*>; pop the front, record it, push its non-null left then right child.
- **Ownership:** every node is allocated with new in main.cpp/tests and belongs to exactly one tree. destroyTree deletes children first, then the node, and sets the caller's pointer to `nullptr`.

### Changes to the plan
- None so far. (Record any later change here with a date/commit.)

### Final design notes
- TreeExplorer.cpp keeps the three depth-first helpers in an anonymous namespace.
- Tree A and Tree B are built with explicit pointer links through a small makeNode helper in main.cpp; no BST insert is used.
- No lesson code was copied; if you adapt any, acknowledge it here.

## How to Compile

g++ -std=c++23 -Wall -Wextra -pedantic main.cpp TreeExplorer.cpp -o tree_explorer
g++ -std=c++23 -Wall -Wextra -pedantic -I. tests/student_tests.cpp TreeExplorer.cpp -o student_tests


## How to Run

./tree_explorer
./student_tests
python validate.py        # or python3 validate.py

On Windows PowerShell use .\tree_explorer.exe and .\student_tests.exe.

## Tests and Results

### Predictions vs. actual: Tree A and Tree B
Diagrams are in the assignment. Tree A root 50, leaves 20 40 60 80. Tree B root 10, leaves 5 and 15 (30 and 20 each have one child).
**Predictions (made before running — replace with your own work):**

| Result | Tree A predicted | Tree B predicted |
|---|---|---|
| Preorder | 50 30 20 40 70 60 80 | 10 30 5 20 15 |
| Inorder | 20 30 40 50 60 70 80 | 30 5 10 20 15 |
| Postorder | 20 40 30 60 80 70 50 | 5 30 15 20 10 |
| Level order | 50 30 70 20 40 60 80 | 10 30 20 5 15 |
| Nodes / Leaves | 7 / 4 | 5 / 2 |
| Height / Sum | 3 / 350 | 3 / 80 |

**Actual (program output):** identical to the predictions above for both trees; both roots print as null after destruction.

Worked trace (Tree B preorder): visit 10; go left, visit 30; 30 has no left, go right, visit 5; back up to 10, go right, visit 20; no left, go right, visit 15 → `10 30 5 20 15`.

### Student tests (tests/student_tests.cpp)

| # | Input / shape | Expected | Actual |
|---|---|---|---|
| 1 | Empty tree; `destroyTree` twice on null | all vectors empty, counts/height/sum 0, root stays null | pass |
| 2 | Singleton -4 | every traversal `-4`; nodes 1, leaves 1, height 1, sum -4 | pass |
| 3a | Left chain 1→2→3→4 (left pointers) | pre `1 2 3 4`, in `4 3 2 1`, post `4 3 2 1`, level `1 2 3 4`; 4 nodes, 1 leaf, h 4, sum 10 | pass |
| 3b | Right chain 1→2→3→4 (right pointers) | pre `1 2 3 4`, in `1 2 3 4`, post `4 3 2 1`, level `1 2 3 4`; 4, 1, h 4, sum 10 | pass |
| 4 | Root 7; left 0 (children -3, 7); right 7 (right child -3) | pre `7 0 -3 7 7 -3`, in `-3 0 7 7 7 -3`, post `-3 7 0 -3 7 7`, level `7 0 7 -3 7 -3`; 6 nodes, 3 leaves, h 3, sum 15 | pass |
| 5 | Repeated calls; edit a returned vector (change, append, clear) | next call and tree unchanged | pass |
| 6 | Destroy, rebuild `5(6,7)`, destroy | rebuilt tree: pre `5 6 7`, in `6 5 7`, post `6 7 5`; roots null each time | pass |
| 7 | Own tree: root 1; left 2 (4,5); right 3 (left child 6) | pre `1 2 4 5 3 6`, in `4 2 5 1 6 3`, post `4 5 2 6 3 1`, level `1 2 3 4 5 6`; 6, 3, h 3, sum 21 (node 3 has one child, so it is not a leaf) | pass |

Result: 67/67 checks passed.

Chain prediction: preorder and level order cannot tell the chains apart; inorder reverses for the left chain because the deepest node is visited first; postorder is the same for both because the deepest node always finishes first.

**Corrections made:** (record any real bugs you hit and fixed here; none recorded yet.)

### Memory check
FILL IN HONESTLY after running it yourself. Example: g++ -std=c++23 -g -fsanitize=address,undefined ... then run both programs; record "no errors/leaks reported" only if that is what you see. If unavailable, say so and add a manual new/delete trace for a small tree.

### Public validator
FILL IN after running python validate.py with the downloaded validator files.

## Analysis Questions
(Write these in your own words; the notes below are a starting outline.)

1. **Subtree at 30 (Tree A, children 20 and 40).** Preorder: visit 30, then 20, then 40 -> 30 20 40. Inorder: finish 20, visit 30, then 40 -> 20 30 40. Postorder: 20, 40, then 30 -> 20 40 30. The visit order changes because the node is handled at a different moment relative to its children. The sum is 90 in every case because each node is added exactly once regardless of order and addition is commutative.
2. **Tree B is not a BST.** Every node has at most two children, so it is a valid binary tree. It violates BST ordering because 5 sits in the right subtree of 30 but 5 < 30 (BST rule: right descendants must be larger). Inorder gives 30 5 10 20 15, which is not sorted, because inorder only produces sorted output when the BST ordering holds.
3. **Depth of 40.** Path 50 → 30 → 40 has 2 edges, so depth is 2 (edges from root). Height in this assignment counts levels (nodes on the longest root-to-leaf path), so Tree A has height 3; in edges it would be 2.
4. **Level order and FIFO.** Push the root. Repeatedly pop the front, record it, and push its children. Earlier nodes enter first so they leave first; children of earlier nodes queue behind later nodes of the same level, so a whole level is processed before the next. This is the same first-in-first-out behavior as the Assignment 2 queue.
5. **Complexity.** Depth-first traversals, counts, height, sum, and destruction visit each node once: O(n) time, O(h) call-stack space. Level order is O(n) time with O(w) queue space. The returned vector is O(n) and is separate from the stack/queue. A balanced tree has h about log₂ n; a chain has h = n, which risks stack overflow. Traversal needs no tabulation because there are no overlapping subproblems; each subtree is processed once.
6. **Postorder deletion and TreeNode*&.** Children must be deleted before the parent so the parent's child pointers are still readable. If the parent were deleted first, reading left/right afterward would be a use-after-free (undefined behavior) and the children could be leaked. TreeNode*& lets destroyTree set the caller's own pointer to nullptr, so no dangling pointer remains and a second call is safe.

## AI Use
AI assistance Claude was used to generate the implementation, tests, and a draft of this README. I reviewed/ran the code, rewrote the plan and predictions in my own words before relying on any output.
