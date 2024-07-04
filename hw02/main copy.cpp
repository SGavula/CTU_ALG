#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>

using namespace std;

struct Node {
    int node_idx;
    int time;
    int time_sum = 0;
    int box = 0;
    int balance = 0;
    vector<int> banBoxes;
    Node* left;
    Node* right;

    Node(int idx, int time) : node_idx(idx), time(time), left(nullptr), right(nullptr) {}
};

/* Declarations of functions */

void inorderTraversal(Node* root) {
    if (root == nullptr) {
        return;
    }

    inorderTraversal(root->left);
    cout << "Index: " << root->idx << " Time:" << root->time << endl;
    inorderTraversal(root->right);
}

/* MAIN */
int main() {
    int numNodes, boxesNum;
    cin >> numNodes >> boxesNum;

    cout << "Number of nodes: " << numNodes << endl;
    cout << "Number of boxes: " << boxesNum << endl;

    vector<int> boxes(boxesNum);
    for (int i = 0; i < boxesNum; ++i) {
        cin >> boxes[i];
    }

    cout << "Items in array: ";
    for (int i = 0; i < boxesNum; ++i) {
        cout << boxes[i] << " ";
    }
    cout << endl;

    int firstNode, secondNode, time;
    cin >> firstNode >> secondNode >> time;
    Node* root = new Node(firstNode, 0);
    root->left = new Node(secondNode, time);

    unordered_map<int, Node*> nodes;
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

    cout << "Inorder Traversal of the binary search tree: " << endl;
    inorderTraversal(root);


    return 0;
}


/* Definitions of functions */
