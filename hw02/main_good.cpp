#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <cstdlib>
#include <climits>

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

void readNodesAndBoxes(int& numNodes, int& numOfBoxes, vector<int>& boxes) {
    cin >> numNodes >> numOfBoxes;

    boxes.resize(numOfBoxes);
    for (int i = 0; i < numOfBoxes; ++i) {
        cin >> boxes[i];
    }
}

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

int checkConditions(Node* leftChild, Node* rightChild) {
    if(leftChild != nullptr && leftChild->value == 0) return 1;
    if(rightChild != nullptr && rightChild->value == 0) return 1;
    return 0;
}

void backtrackBox() {
    
}

void solve(Node* root, Node* currentNode, Node* parentNode, int index, vector<int>& boxes, int& bestTreeBalance, int& bestTime, int n) {
    if(index == n) {
        int balance = 0;
        int time = 0;
        // cout << "##################" << endl;
        inorderSumBalance(root, balance);
        // if(balance != 96) {
        //     cout << balance << endl;
        // }
        inorderSumTime(root, time);
        // cout << "Time: " << time << endl;
        // if(balance == 143) {
        //     inorderTraversal(root);
        //     cout << "Balance: " << balance << " W: " << time << endl;
        // }
        if(balance < bestTreeBalance) {
            bestTreeBalance = balance;
            bestTime = time;
        }else {
            if(balance == bestTreeBalance) {
                if(time < bestTime) {
                    bestTreeBalance = balance;
                    bestTime = time;
                }
            }
        }

        return;
    }

    if(checkConditions(currentNode->left, currentNode->right) == 0) {
        if(currentNode->left == nullptr && currentNode->right == nullptr) {
            // Add box
            currentNode->value = currentNode->value + boxes[index];
            if(parentNode != nullptr) {
                currentNode->balance = abs(parentNode->value - currentNode->value);
            }
            if(currentNode->left != nullptr) {
                currentNode->left->balance = abs(currentNode->value - currentNode->left->value);
            }
            if(currentNode->right != nullptr) {
                currentNode->right->balance = abs(currentNode->value - currentNode->right->value);
            }
            currentNode->timeSum = currentNode->timeSum + currentNode->time;
            
            // Go to next box and start from root node
            solve(root, root, nullptr, index + 1, boxes, bestTreeBalance, bestTime, n);
            
            // Remove box
            currentNode->value = currentNode->value - boxes[index];
            if(parentNode != nullptr) {
                currentNode->balance = abs(parentNode->value - currentNode->value);
            }
            if(currentNode->left != nullptr) {
                currentNode->left->balance = abs(currentNode->value - currentNode->left->value);
            }
            if(currentNode->right != nullptr) {
                currentNode->right->balance = abs(currentNode->value - currentNode->right->value);
            }
            currentNode->timeSum = currentNode->timeSum - currentNode->time;
        }else {
            if(currentNode->value != 0) {
                
                // Add box
                currentNode->value = currentNode->value + boxes[index];
                if(parentNode != nullptr) {
                    currentNode->balance = abs(parentNode->value - currentNode->value);
                }
                if(currentNode->left != nullptr) {
                    currentNode->left->balance = abs(currentNode->value - currentNode->left->value);
                }
                if(currentNode->right != nullptr) {
                    currentNode->right->balance = abs(currentNode->value - currentNode->right->value);
                }
                currentNode->timeSum = currentNode->timeSum + currentNode->time;
                
                // Go to next box and start from root node
                solve(root, root, nullptr, index + 1, boxes, bestTreeBalance, bestTime, n);
                
                // Remove box
                currentNode->value = currentNode->value - boxes[index];
                if(parentNode != nullptr) {
                    currentNode->balance = abs(parentNode->value - currentNode->value);
                }
                if(currentNode->left != nullptr) {
                currentNode->left->balance = abs(currentNode->value - currentNode->left->value);
                }
                if(currentNode->right != nullptr) {
                    currentNode->right->balance = abs(currentNode->value - currentNode->right->value);
                }
                currentNode->timeSum = currentNode->timeSum - currentNode->time;
            }else {
                if(currentNode->left != nullptr) {
                    solve(root, currentNode->left, currentNode, index, boxes, bestTreeBalance, bestTime, n);
                }

                // Add box
                currentNode->value = currentNode->value + boxes[index];
                if(parentNode != nullptr) {
                    currentNode->balance = abs(parentNode->value - currentNode->value);
                }
                if(currentNode->left != nullptr) {
                    currentNode->left->balance = abs(currentNode->value - currentNode->left->value);
                }
                if(currentNode->right != nullptr) {
                    currentNode->right->balance = abs(currentNode->value - currentNode->right->value);
                }
                currentNode->timeSum = currentNode->timeSum + currentNode->time;
                // Go to next box and start from root node
                solve(root, root, nullptr, index + 1, boxes, bestTreeBalance, bestTime, n);
                // Remove box
                currentNode->value = currentNode->value - boxes[index];
                if(parentNode != nullptr) {
                    currentNode->balance = abs(parentNode->value - currentNode->value);
                }
                if(currentNode->left != nullptr) {
                    currentNode->left->balance = abs(currentNode->value - currentNode->left->value);
                }
                if(currentNode->right != nullptr) {
                    currentNode->right->balance = abs(currentNode->value - currentNode->right->value);
                }
                currentNode->timeSum = currentNode->timeSum - currentNode->time;        

                if(currentNode->right != nullptr) {
                    solve(root, currentNode->right, currentNode, index, boxes, bestTreeBalance, bestTime, n);
                }
            }
        }
    }else {
        if(currentNode->left != nullptr) {
            solve(root, currentNode->left, currentNode, index, boxes, bestTreeBalance, bestTime, n);
        }
        if(currentNode->right != nullptr) {
            solve(root, currentNode->right, currentNode, index, boxes, bestTreeBalance, bestTime, n);
        }

    }
}

/* MAIN */
int main() {
    int numNodes, numOfBoxes, bestTreeBalance, bestTime;
    int boxIndex = 0;
    
    vector<int> boxes;
    unordered_map<int, Node*> nodes;

    readNodesAndBoxes(numNodes, numOfBoxes, boxes);
    Node* root = buildTree(nodes);
    
    bestTreeBalance = INT_MAX;
    bestTime = INT_MAX;
    inorderSumTime(root, bestTime);
    solve(root, root, nullptr ,boxIndex, boxes, bestTreeBalance, bestTime, numOfBoxes);

    cout << bestTreeBalance << " " << bestTime << endl;
    // Clean up dynamically allocated memory
    for (auto& pair : nodes) {
        delete pair.second;
    }

    return 0;
}



/* Definitions of functions */
