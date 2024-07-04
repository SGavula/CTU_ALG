#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;

struct Node {
    int key;
    int branch;
    Node *parent;
    Node *left;
    Node *right;

    Node(int k, Node *parent) : key(k), branch(-1), parent(parent), left(nullptr), right(nullptr) {};
};

// Struct Node is in the utils struct
struct Utils {
    int branchLength;
    Node *root;
    int counter = 0;

    Utils(int branchLength, Node *root) : branchLength(branchLength), root(root) {};
};

// Declarations of functions
void printTree(Node* node, int depth);
Node* createNewNode(int key, Node* parentNode);
Node* createBalancedSubtree(vector<Node>& balancedNodes, int start, int end);
void fixBalanced(Node *node, Node *balancedRoot, Node *oldParent, Utils *utils);
void make_inorder(Node *node, vector<Node> &balancedNodes, Node *&child, Utils *utils);
void balanceBranch(Node *node, Utils *utils);
int findMinValue(Node* root);
void update(Node *node, Utils *utils);
void insert(Node *newNode, Node *node, Utils *utils);
void deleteNode(Node *node, int key, Utils *utils);
void deleteNodeWithoutUpdate(Node *node, int key, Utils *utils);
Node *returnChild(Node *node, int key, Utils *utils);
void processOperations(int k);

/* MAIN */
int main() {
    int K, N;
    cin >> K >> N;

    processOperations(K);

    return 0;
}

// Definitions of functions
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

Node* createNewNode(int key, Node* parentNode) {
    return new Node(key, parentNode);
}

Node* createBalancedSubtree(vector<Node>& balancedNodes, Node* parent, int start, int end) {
    if (start > end) {
        return nullptr;
    }

    int mid = start + (end - start) / 2;
    Node* root = createNewNode(balancedNodes[mid].key, parent);
    root->left = createBalancedSubtree(balancedNodes, root, start, mid - 1);
    root->right = createBalancedSubtree(balancedNodes, root, mid + 1, end);

    return root;
}

void fixBalanced(Node *node, Node *balancedRoot, Node *oldParent, Utils *utils) {
    if(oldParent == nullptr) {
        utils->root = balancedRoot;
    } else if(oldParent->left == node) {
        oldParent->left = balancedRoot;
    } else {
        oldParent->right = balancedRoot;
    }
}

void make_inorder(Node *node, vector<Node> &balancedNodes, Node *&child, Utils *utils) {
    if(node == nullptr) {
        return;
    }

    if(node->branch == utils->branchLength) {
        // Add last node in branch
        balancedNodes.push_back(*node);
        if(node->left != nullptr) {
            child = node->left;
        } else {
            child = node->right;
        }
    } else {
        make_inorder(node->left, balancedNodes, child, utils);
        balancedNodes.push_back(*node);
        make_inorder(node->right, balancedNodes, child, utils);
    }
};

void balanceBranch(Node *node, Utils *utils) {
    if(node->branch != 1) {
        balanceBranch(node->parent, utils);
    } else {
        Node *oldParent = node->parent;
        vector<Node> balancedNodes;
        Node *child = nullptr;
        make_inorder(node, balancedNodes, child, utils);
        Node *balancedRoot = createBalancedSubtree(balancedNodes, nullptr,0, balancedNodes.size() - 1);
        if(child != nullptr) {
            insert(child, balancedRoot, utils);
        }
        update(balancedRoot, utils);
        balancedRoot->parent = oldParent;
        fixBalanced(node, balancedRoot, oldParent, utils);
    }
}

void update(Node *node, Utils *utils) {
    if(node == nullptr) {
        return;
    }

    if(node->left != nullptr && node->right != nullptr) {
        node->branch = 0;
    } else {
        if(node->parent != nullptr) {
            node->branch = node->parent->branch + 1;
            // cout << node->key << " " << node->branch << endl;
            if(node->branch  == utils->branchLength) {
                balanceBranch(node, utils);
                utils->counter++;
                return;
            }
        } else {
            node->branch = 1;
        }
    }

    update(node->left, utils);
    update(node->right, utils);
}

void insert(Node *newNode, Node *node, Utils *utils) {
    if(node == nullptr) {
        utils->root = newNode;
        return;
    }
    
    if(newNode->key < node->key) {
        if(node->left == nullptr) {
            newNode->parent = node;
            node->left = newNode;
            update(node, utils);
            return;
        }else {
            insert(newNode, node->left, utils);
        }
    } else if(newNode->key > node->key) {
        if(node->right == nullptr) {
            newNode->parent = node;
            node->right = newNode;
            update(node, utils);
            return;
        }else {
            insert(newNode, node->right, utils);
        }
    }
}

void deleteNode(Node *node, int key, Utils *utils) {
    if(key < node->key) {
        if(node->left->key == key) {
            node->left = returnChild(node->left, key, utils);
            if(node->left != nullptr) {
                node->left->parent = node;
                update(node, utils);
            }else {
                if(node->parent != nullptr) {
                    update(node->parent, utils);
                }else {
                    update(node, utils);
                }
            }
        }else {
            deleteNode(node->left, key, utils);
        }
    }else if(key > node->key) {
        if(node->right->key == key) {
            node->right = returnChild(node->right, key, utils);
            if(node->right != nullptr) {
                node->right->parent = node;
                update(node, utils);
            }else {
                if(node->parent != nullptr) {
                    update(node->parent, utils);
                }else {
                    update(node, utils);
                }
            }
        }else {
            deleteNode(node->right, key, utils);
        }
    } else {
        if(node->left != nullptr && node->right != nullptr) {
            int minValue = findMinValue(node->right);
            utils->root->key = minValue;
            if(minValue == utils->root->right->key) {
                if(utils->root->right->left == nullptr && utils->root->right->right == nullptr) {
                    utils->root->right = nullptr;
                } else {
                    utils->root->right = utils->root->right->right;
                    utils->root->right->parent = utils->root;
                }
            }else {
                deleteNodeWithoutUpdate(utils->root->right, minValue, utils);
            }
        }else {
            if(node->left == nullptr && node->right == nullptr) {
                utils->root = nullptr;
            } 
            if(node->left != nullptr) {
                utils->root = utils->root->left;
            }
            if(node->right != nullptr) {
                utils->root = utils->root->right;
            }
        }
    }
};

void deleteNodeWithoutUpdate(Node *node, int key, Utils *utils) {
    if(key < node->key) {
        if(node->left->key == key) {
            node->left = returnChild(node->left, key, utils);
            if(node->left != nullptr) {
                node->left->parent = node;
            }
        }else {
            deleteNode(node->left, key, utils);
        }
    }else if(key > node->key) {
        if(node->right->key == key) {
            node->right = returnChild(node->right, key, utils);
            if(node->right != nullptr) {
                node->right->parent = node;
            }
        }else {
            deleteNode(node->right, key, utils);
        }
    }
};

Node *returnChild(Node *node, int key, Utils *utils) {
    if(node->left == nullptr) {
        return node->right;
    }else if(node->right == nullptr) {
        return node->left;
    }else {
        int minValue = findMinValue(node->right);
        node->key = minValue;
        if(node->right->key == minValue) {
            if(node->right->right == nullptr) {
                node->right = nullptr;
            }else {
                node->right = node->right->right;
                node->right->parent = node;
            }
        } else {
            deleteNodeWithoutUpdate(node->right, minValue, utils);
        }
        return node;
    }
};

int findMinValue(Node* root) {
    Node* current = root;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current->key;
}

void processOperations(int k) {
    vector<int> testVector;
    int branchLength = pow(2, k)-1;

    Node* root = nullptr;

    // Loaded values
    char operation;
    int key = 0;
    cin >> operation >> key;
    root = createNewNode(key, nullptr);
    Utils *utils = new Utils(branchLength, root);

    while (cin >> operation >> key) {
        if (operation == 'I') {
            Node *newNode = createNewNode(key, nullptr);
            insert(newNode, utils->root, utils);
        } else if (operation == 'D') {
            deleteNode(utils->root, key, utils);
        }
    }

    cout << utils->counter << endl;
    delete utils;
}

