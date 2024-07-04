#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <cstdlib>
#include <climits>

#define NEXT_CHILD(child) if(child != nullptr) solve(root, child, currentNode, index, boxes, bestTreeBalance, bestTime, n);

using namespace std;

struct Node {
    int nodeIdx;
    int time;
    int timeSum = 0;
    int value = 0;
    int balance = 0;
    Node* left;
    Node* right;
    Node* parent;

    Node(int idx, int time) : nodeIdx(idx), time(time), left(nullptr), right(nullptr), parent(nullptr) {}
};

/* Declarations of functions */
Node* buildTree(unordered_map<int, Node*>& nodes);
void readNodesAndBoxes(int& numNodes, int& numOfBoxes, vector<int>& boxes);
void inorderTraversal(Node* root);
void inorderSumBalance(Node* root, int& treeBalance);
void inorderSumTime(Node* root, int& treeTime);
int checkIfBoxCanBeStored(Node* leftChild, Node* rightChild);   
void calculateBalance(Node* currentNode, Node* parentNode);
void addBox(Node* currentNode, Node* parentNode, int index, vector<int>& boxes);
void removeBox(Node* currentNode, Node* parentNode, int index, vector<int>& boxes);
void backtrackBox(Node* root, Node* currentNode, Node* parentNode, int index, vector<int>& boxes, int& bestTreeBalance, int& bestTime, int n);
void evaluateBalanceAndTime(Node* root, int& bestTreeBalance, int& bestTime);
void solve(Node* root, Node* currentNode, Node* parentNode, int index, vector<int>& boxes, int& bestTreeBalance, int& bestTime, int n);

/* MAIN */
int main() {
    int numNodes, numOfBoxes, bestTreeBalance, bestTime;
    int boxIndex = 0;
    vector<int> boxes;
    unordered_map<int, Node*> nodes;

    // Read input and build tree from loaded input
    readNodesAndBoxes(numNodes, numOfBoxes, boxes);
    Node* root = buildTree(nodes);
    
    bestTreeBalance = INT_MAX;
    bestTime = INT_MAX;
    // Generating all solutions and perform backtraking
    solve(root, root, nullptr ,boxIndex, boxes, bestTreeBalance, bestTime, numOfBoxes);

    // Print output
    cout << bestTreeBalance << " " << bestTime << endl;

    // Clean up dynamically allocated memory
    for (auto& pair : nodes) {
        delete pair.second;
    }

    return 0;
}

/* Definitions of functions */
Node* buildTree(unordered_map<int, Node*>& nodes) {
    int firstNode, secondNode, time;
    cin >> firstNode >> secondNode >> time;
    Node* root = new Node(firstNode, 0);
    root->left = new Node(secondNode, time);

    nodes[firstNode] = root;
    nodes[secondNode] = root->left;

    while (cin >> firstNode >> secondNode >> time) {
        Node* parent = nodes[firstNode];
        Node* child = new Node(secondNode, parent->time + time);

        // Determine whether to attach the new node as left or right child
        if (parent->left == nullptr) {
            parent->left = child;
        } else if (parent->right == nullptr) {
            parent->right = child;
        }

        // Update the nodes map with the new node
        nodes[secondNode] = child;
    }
    return root;
}

void readNodesAndBoxes(int& numNodes, int& numOfBoxes, vector<int>& boxes) {
    cin >> numNodes >> numOfBoxes;

    boxes.resize(numOfBoxes);
    for (int i = 0; i < numOfBoxes; ++i) {
        cin >> boxes[i];
    }
}

void inorderTraversal(Node* root) {
    if (root == nullptr) {
        return;
    }

    inorderTraversal(root->left);
    cout << "Index: " << root->nodeIdx << " Value:" << root->value << " Time: " << root->time << " TimeSum: " << root->timeSum << endl;
    inorderTraversal(root->right);
}

void inorderSumBalance(Node* root, int& treeBalance) {
    if (root == nullptr) {
        return;
    }

    inorderSumBalance(root->left, treeBalance);
    treeBalance = treeBalance + root->balance;
    inorderSumBalance(root->right, treeBalance);
}

void inorderSumTime(Node* root, int& treeTime) {
    if (root == nullptr) {
        return;
    }

    inorderSumTime(root->left, treeTime);
    treeTime = treeTime + root->timeSum;
    inorderSumTime(root->right, treeTime);
}

void calculateBalance(Node* currentNode, Node* parentNode) {
    if(parentNode != nullptr) {
        currentNode->balance = abs(parentNode->value - currentNode->value);
    }
    if(currentNode->left != nullptr) {
        currentNode->left->balance = abs(currentNode->value - currentNode->left->value);
    }
    if(currentNode->right != nullptr) {
        currentNode->right->balance = abs(currentNode->value - currentNode->right->value);
    }
}

// Add box to the node and calculate time and balance
void addBox(Node* currentNode, Node* parentNode, int index, vector<int>& boxes) {
    currentNode->value = currentNode->value + boxes[index];
    calculateBalance(currentNode, parentNode);
    currentNode->timeSum = currentNode->timeSum + currentNode->time;
}

// Remove box from the node and calculate time and balance again
void removeBox(Node* currentNode, Node* parentNode, int index, vector<int>& boxes) {
    currentNode->value = currentNode->value - boxes[index];
    calculateBalance(currentNode, parentNode);
    currentNode->timeSum = currentNode->timeSum - currentNode->time;
}

void backtrackBox(Node* root, Node* currentNode, Node* parentNode, int index, vector<int>& boxes, int& bestTreeBalance, int& bestTime, int n) {
    addBox(currentNode, parentNode, index, boxes);
    // Go to next box and start from root node
    solve(root, root, nullptr, index + 1, boxes, bestTreeBalance, bestTime, n);
    removeBox(currentNode, parentNode, index, boxes);
}

void evaluateBalanceAndTime(Node* root, int& bestTreeBalance, int& bestTime) {
    int balance = 0;
    int time = 0;
    inorderSumBalance(root, balance);
    inorderSumTime(root, time);
    if(balance == bestTreeBalance) {
        if(time < bestTime) {
            bestTreeBalance = balance;
            bestTime = time;
        }
    }
    if(balance < bestTreeBalance) {
        bestTreeBalance = balance;
        bestTime = time;
    }
}

int checkIfBoxCanBeStored(Node* leftChild, Node* rightChild) {
    if(leftChild != nullptr && leftChild->value == 0) return 1;
    if(rightChild != nullptr && rightChild->value == 0) return 1;
    return 0;
}

void solve(Node* root, Node* currentNode, Node* parentNode, int index, vector<int>& boxes, int& bestTreeBalance, int& bestTime, int n) {
    if(index == n) {
        evaluateBalanceAndTime(root, bestTreeBalance, bestTime);
        return;
    }

    if(checkIfBoxCanBeStored(currentNode->left, currentNode->right) == 0) {
        if(currentNode->left == nullptr && currentNode->right == nullptr) {
            backtrackBox(root, currentNode, parentNode, index, boxes, bestTreeBalance, bestTime, n);
        }else {
            if(currentNode->value != 0) {
                backtrackBox(root, currentNode, parentNode, index, boxes, bestTreeBalance, bestTime, n);
            }else {
                NEXT_CHILD(currentNode->left);
                backtrackBox(root, currentNode, parentNode, index, boxes, bestTreeBalance, bestTime, n);
                NEXT_CHILD(currentNode->right);
            }
        }
    }else {
        NEXT_CHILD(currentNode->left);
        NEXT_CHILD(currentNode->right);
    }
}