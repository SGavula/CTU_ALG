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

    solve(node->left);
    solve(node->right);

    int leftDepth = (node->left != nullptr) ? node->left->depth : -1;
    int rightDepth = (node->right != nullptr) ? node->right->depth : -1;
    int leftPath = node->left != nullptr ? node->left->path + 1 : 0;
    int rightPath = node->right != nullptr ? node->right->path + 1 : 0;
    int leftOpt = (node->left != nullptr) ? node->left->opt : 0;
    int rightOpt = (node->right != nullptr) ? node->right->opt : 0;

    node->depth = max(leftDepth, rightDepth) + 1;
    node->path = leftPath + rightPath;
    
    if (node->left != nullptr && node->right != nullptr) {
        node->opt = max(rightOpt + leftDepth + 2, leftOpt + rightDepth + 2);
    } else if (node->left != nullptr) {
        node->opt = leftOpt + rightDepth + 2;
    } else if (node->right != nullptr) {
        node->opt = rightOpt + leftDepth + 2;
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> preorder(n);
    for (int i = 0; i < n; ++i) {
        cin >> preorder[i];
    }

    TreeNode* root = buildTree(preorder);
    solve(root);
    cout << root->opt << endl;
    deleteTree(root);
    return 0;
}
