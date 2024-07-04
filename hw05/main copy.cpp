#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Utils {
    int branchLength;
    Node *root;

    Utils(int branchLength, Node *root) : branchLength(branchLength), root(root) {};
};

struct Node {
    int key;
    int branch;
    Node *parent;
    Node *left;
    Node *right;

    Node(int k, Node *parent) : key(k), branch(-1), parent(parent), left(nullptr), right(nullptr) {};
};


Node* createNewNode(int key, Node* parentNode) {
    return new Node(key, parentNode);
}

void printTree(Node* node, int depth) {
    const int INDENTATION = 4; // Adjust the indentation level as needed

    if (node != nullptr) {
        // Traverse the right subtree
        printTree(node->right, depth + 1);

        // Print the current node's key with indentation
        for (int i = 0; i < depth * INDENTATION; ++i)
            std::cout << ' ';
        std::cout << "(" << node->key << ", " << node->branch << ")" << std::endl;
        // std::cout << node->key << std::endl;

        // Traverse the left subtree
        printTree(node->left, depth + 1);
    }
}

// void make_inorder(Node *node, vector<Node> &balancedNodes, Node *child, Utils *utils) {
//     if(node == nullptr) {
//         return;
//     }

//     if(node->branch == utils->branchLength) {
//         // Add last node in branch
//         balancedNodes.push_back(*node);
//         if(node->left != nullptr) {
//             child = node->left;
//         } else {
//             child = node->right;
//         }
//     } else {
//         make_inorder(node->left, balancedNodes, child, utils);
//         balancedNodes.push_back(*node);
//         make_inorder(node->right, balancedNodes, child, utils);
//     }
// };

// Node* createBalancedSubtree(const std::vector<Node>& balancedNodes, int start, int end) {
//     if (start > end) {
//         return nullptr;
//     }

//     int mid = start + (end - start) / 2;
//     Node* root = createNewNode(balancedNodes[mid].key, balancedNodes[mid].parent);
//     root->left = createBalancedSubtree(balancedNodes, start, mid - 1);
//     root->right = createBalancedSubtree(balancedNodes, mid + 1, end);

//     return root;
// }

// void fixBalanced(Node *node, Node *balancedRoot, Node *oldParent, Utils *utils) {
//     if(oldParent == nullptr) {
//         utils->root = balancedRoot;
//     } else if(oldParent->left == node) {
//         oldParent->left = balancedRoot;
//     } else {
//         oldParent->right = balancedRoot;
//     }
// }

// void balanceBranch(Node *node, Utils *utils) {
//     if(node->branch != 1) {
//         balanceBranch(node->parent);
//     } else {
//         Node *oldParent = node.parent;
//         vector<Node> balancedNodes;
//         Node *child = nullptr;
//         make_inorder(node, &balancedNodes, child);
//         Node *balancedRoot = createBalancedSubtree(balancedNodes, 0, balancedNodes.size() - 1);
//         if(child != nullptr) {
//             insert(child, balancedRoot, utils);
//         }
//         update(balancedRoot, utils);
//         balancedRoot->parent = oldParent;
//         fixBalanced();

//     }
// }

// void update(Node *node, Utils *utils) {
//     // || node->branch == 0
//     if(node == nullptr) {
//         return;
//     }

//     if(node->left != nullptr && node->right != nullptr) {
//         node->branch = 0;
//     } else {
//         if(node->parent != nullptr) {
//             node->branch = node->parent->branch +1;
//             if(node->branch  == utils->branchLength) {
//                 // TODO: balance branch
//                 balanceBranch(node, utils);
//                 // TODO: return
//             }
//         }
//     }

//     update(node->left, utils);
//     update(node->right, utils);
// }

// void insert(Node *newNode, Node *node, Utils *utils) {
//     if(newNode->key < node->key) {
//         if(node->left == nullptr) {
//             // Add parent
//             newNode->parent = node;
//             node->left = newNode;
//             //TODO: update
//             update(node, utils);
//             // printf("Hello\n");
//             return;
//         }else {
//             insert(newNode->key, node->left, utils);
//         }
//     } else {
//         if(node->right == nullptr) {
//             newNode->parent = node;
//             node->right = newNode;
//             //TODO: update
//             update(node, utils);
//             return;
//         }else {
//             insert(newNode->key, node->right, utils);
//         }
//     }
// }

// int findMinValue(Node* root) {
//     Node* current = root;
//     while (current->left != nullptr) {
//         current = current->left;
//     }
//     return current.key;
// }

int processOperations(int k) {
    int branchLength = pow(2, k)-1;
    printf("Branch length: %d\n", branchLength);

    Node* root = nullptr;

    // Loaded values
    char operation;
    int key = 0;
    int bareBranchCount = 0;
    cin >> operation >> key;
    root = createNewNode(key, nullptr);
    Utils *utils = new Utils(branchLength, root);

    // while (cin >> operation >> key) {
    //     if (operation == 'I') {
    //         // printf("Operation insert: %c\n", operation);
    //         // printf("Key insert: %d\n", key);
    //         Node *newNode = createNewNode(key, nullptr);
    //         insert(newNode, root, utils);
    //     } else if (operation == 'D') {
    //         // printf("Operation delete: %c\n", operation);
    //         // printf("Key delete: %d\n", key);
    //         // root = deleteNode(root, key);
    //     }
    // }

    // PRINT TREE
    printTree(root, 0);

    return bareBranchCount;
}

int main() {
    int K, N;
    cin >> K >> N;

    printf("K: %d\n", K);
    printf("N: %d\n", N);

    int result = processOperations(K);
    // cout << result << endl;

    return 0;
}
