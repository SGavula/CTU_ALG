#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct TreeNode {
    int val;
    int depth = 0;
    int path = 0;
    int opt = 1;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/* Declarations of functions */
TreeNode* buildTree(vector<int>& preorder, int& index, int minValue, int maxValue);
TreeNode* buildTree(vector<int>& preorder);
void deleteTree(TreeNode* node);
void printInorder(TreeNode* node);
void solve(TreeNode *node);

/* MAIN */
int main() {
    int n;
    cin >> n;
    // Load nodes of tree to vector list
    vector<int> preorder(n);
    for (int i = 0; i < n; ++i) {
        cin >> preorder[i];
    }

    TreeNode* root = buildTree(preorder);
    solve(root);
    // Print solution
    cout << root->opt << endl;
    // Clean allocated memory
    deleteTree(root);
    return 0;
}

/* Definitions of functions */
TreeNode* buildTree(vector<int>& preorder, int& index, int minValue, int maxValue) {
    if (index >= preorder.size()) {
        return nullptr;
    }

    int currentValue = preorder[index];
    if (currentValue < minValue || currentValue > maxValue) {
        return nullptr;
    }

    TreeNode* newNode = new TreeNode(currentValue);
    index++;

    newNode->left = buildTree(preorder, index, minValue, currentValue - 1);
    newNode->right = buildTree(preorder, index, currentValue + 1, maxValue);

    return newNode;
}

TreeNode* buildTree(vector<int>& preorder) {
    int index = 0;
    return buildTree(preorder, index, INT_MIN, INT_MAX);
}

void deleteTree(TreeNode* node) {
    if (node == nullptr) {
        return;
    }

    // first delete both subtrees
    deleteTree(node->left);
    deleteTree(node->right);

    // then delete the node
    delete(node);
}

void printInorder(TreeNode* node) {
    if (node == nullptr) {
        return;
    }
    cout << node->val << " ";
    printInorder(node->left);
    printInorder(node->right);
}

void solve(TreeNode *node) {
    if (node == nullptr) {
        return;
    }

    // Dive into children
    solve(node->left);
    solve(node->right);
    
    // Get children property of child exit, if not put into variable default value
    int leftDepth = node->left != nullptr ? node->left->depth : 0;
    int leftPath = node->left != nullptr ? node->left->path + 1 : 0;
    int rightDepth = node->right != nullptr ? node->right->depth : 0;
    int rightPath = node->right != nullptr ? node->right->path + 1 : 0;

    if(node->left != nullptr || node->right != nullptr) {
        // Get depth
        node->depth = max(leftDepth, rightDepth) + 1;
        // Get path
        node->path = leftPath + rightPath;
        // Get optimal solution
        if(node->left == nullptr) {
            node->opt = node->right->opt + 1;
        }else if(node->right == nullptr) {
            node->opt = node->left->opt + 1;
        }else {
            int leftOpt = node->left->opt + node->right->depth + 2;
            int rightOpt = node->right->opt + node->left->depth + 2;
            node->opt = max(leftOpt, rightOpt);
        }
    }
}