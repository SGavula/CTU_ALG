#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <cstdlib>

using namespace std;

struct Node {
    int nodeIdx;
    int time;
    int timeSum = 0;
    int value = 0;
    int balance = 0;
    vector<int> banBoxes;
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
    cout << "Index: " << root->nodeIdx << " Time:" << root->time << endl;
    inorderTraversal(root->right);
}


void readNodesAndBoxes(int& numNodes, int& boxesArr, vector<int>& boxes) {
    cin >> numNodes >> boxesArr;
    cout << "Number of nodes: " << numNodes << endl;
    cout << "Number of boxes: " << boxesArr << endl;

    boxes.resize(boxesArr);
    for (int i = 0; i < boxesArr; ++i) {
        cin >> boxes[i];
    }

    cout << "Items in array: ";
    for (int i = 0; i < boxesArr; ++i) {
        cout << boxes[i] << " ";
    }
    cout << endl;
}

Node* buildTree(unordered_map<int, Node*>& nodes) {
    int firstNode, secondNode, time;
    cin >> firstNode >> secondNode >> time;
    Node* root = new Node(firstNode, 0);
    root->left = new Node(secondNode, time);

    nodes[firstNode] = root;
    nodes[secondNode] = root->left;

    while (cin >> firstNode >> secondNode >> time) {
        cout << firstNode << " " << secondNode << " " << time << endl;
        Node* parent = nodes[firstNode];
        Node* child = new Node(secondNode, time);

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

int checkValueInBanBoxes(int boxIndex, int& banBoxes) {
    for(int i = 0; i < banBoxes.size(); ++i) {
        if(banBoxes[i] == boxIndex) {
            return 1;
        }
    }
    return 0;
}

void solve(Node* root, Node* actualNode, int boxIndex, int& boxesArr, int parentValue) {
    if(boxIndex == boxesArr.size()) {
        boxIndex--;
        actualNode->value = actualNode-value - boxesArr[boxIndex];
        actualNode->timeSum = actualNode->time * actualNode->value;
        actualNode->balance = abs(actualNode->value - parentValue);
        solve(root, root, boxIndex, boxesArr, parentValue);
    }

    if(checkConditions(root->left, root->right) == 0) {
        cout << "I CAN put my box here." << endl;
        actualNode->value = actualNode->value + boxesArr[boxIndex];
        actualNode->timeSum = actualNode->time * actualNode->value;
        actualNode->balance = abs(actualNode->value - parentValue);
        numbers.push_back(boxIndex);
        boxIndex++;
        solve(root, actualNode, boxIndex, boxesArr, parentValue)
        // return;
    }else {
        cout << "I CANNOT put my box here." << endl;
        if(checkValueInBanBoxes(boxIndex, actualNode->left->banBoxes) == 0) {
            solve(actualNode->left, boxIndex, boxesArr, actualNode->value);
        }
        if(checkValueInBanBoxes(boxIndex, actualNode->right->banBoxes) == 0) {
            solve(actualNode->right, boxIndex, boxesArr, actualNode->value);
        }

    }
    // cout << "Left child: " << root->left->box << "Right child: " << root->right->box << endl;
}

/* MAIN */
int main() {
    int numNodes, boxesArr;
    int boxIndex = 0;
    vector<int> boxes;
    unordered_map<int, Node*> nodes;

    readNodesAndBoxes(numNodes, boxesArr, boxes);
    Node* root = buildTree(nodes);

    cout << "Inorder Traversal of the binary search tree: " << endl;
    inorderTraversal(root);

    solve(root, root, boxIndex, boxesArr, 0);

    // Clean up dynamically allocated memory
    for (auto& pair : nodes) {
        delete pair.second;
    }

    return 0;
}



/* Definitions of functions */
