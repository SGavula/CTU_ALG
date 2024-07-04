#include <iostream>
#include <climits>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>

#define BLUE 2
 
using namespace std;

struct TreeNode {
  int idx;
  int color;
  int optimalDepth;
  int optimalPath;
  int result;
  TreeNode* parent;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int i, int c) : idx(i), color(c), left(nullptr), right(nullptr) {}
};
 
// Declarations of functions
void printInorder(TreeNode* node) {
    if (node == nullptr) {
        return;
    }
    printInorder(node->left);
    cout << node->idx << " ";
    printInorder(node->right);
} 

void printTree(TreeNode* node, int depth) {
    const int INDENTATION = 4; // Adjust the indentation level as needed

    if (node != nullptr) {
        // Traverse the right subtree
        printTree(node->right, depth + 1);

        // Print the current node's key with indentation
        for (int i = 0; i < depth * INDENTATION; ++i) {
            cout << ' ';
        }
        cout << "(" << node->idx << ", " << node->color << ")" << std::endl;
        // std::cout << node->key << std::endl;

        // Traverse the left subtree
        printTree(node->left, depth + 1);
    }
}

TreeNode* buildTree(vector<int> inputTree) {
  int idx = 0;
  int color = inputTree[idx];
  TreeNode* newNode = new TreeNode(idx, color);
  newNode->parent = nullptr;

  queue<TreeNode*> q;
  q.push(newNode);

  
  while(!q.empty()) {
    TreeNode* current = q.front();
    q.pop();

    // cout << "Current index: " << current->idx << endl;
    // cout << "Current color: " << current->color << endl;

    if(current->color != BLUE) {
      // cout << "Hello" << endl;
      
      idx = idx + 1;
      color = inputTree[idx];
      TreeNode* leftNewNode = new TreeNode(idx, color);
      current->left = leftNewNode;
      leftNewNode->parent = current;
      q.push(leftNewNode);

      // Create right child
      idx = idx + 1;
      color = inputTree[idx];
      TreeNode* rightNewNode = new TreeNode(idx, color);
      current->right = rightNewNode;
      rightNewNode->parent = current;
      q.push(rightNewNode);
    }

  }

  return newNode;
}

void solve(TreeNode *node) {
    if (node == nullptr) {
        return;
    }

    // Dive into children
    solve(node->left);
    solve(node->right);

    if(node->parent == nullptr) {
      // node->optimalDepth = node->left->optimalDepth + node->right->optimalDepth + 1;
      // if((node->left->color == node->color) && (node->right->color == node->color)) {
      if (node->left && node->right && (node->left->color == node->color) && (node->right->color == node->color)) {
        node->optimalPath = max(node->left->optimalPath, node->right->optimalPath);
      } else {
        int optimalPathChilds = max(node->left->optimalPath, node->right->optimalPath);
        int optimalPathComp = node->left->optimalDepth + node->right->optimalDepth + 1;
        node->optimalPath = max(optimalPathChilds, optimalPathComp);
        // cout << endl;
        // cout << "Optimal Path Childs: " << optimalPathChilds << endl;
        // cout << "Optimal Path Comp: " << optimalPathComp << endl;
        // cout << "Optimal path max: " << max(node->left->optimalPath, node->right->optimalPath) << endl;
        // cout << "Optimal path: " << node->optimalPath << endl;
        // cout << "Optimal depth: " << node->optimalDepth << endl;
      }
      
      return;
    }

    if(node->left == nullptr) {
      // Blue node
      node->optimalDepth = 1;
      node->optimalPath = 1;
      return;
    } else if(node->color != node->parent->color) {
      // if(node->idx == 81) {
      //   cout << "Super" << endl;
      // }
      // Colors are not same --> take maximum from node left depth and node right depth and increase by 1 
      node->optimalDepth = max(node->left->optimalDepth, node->right->optimalDepth) + 1;
    } else {
      // Node and parent colors are same
      if((node->left->color == node->color) && (node->right->color == node->color)) {
        node->optimalDepth = 0;
      } else if(node->left->color == node->color) {
        // Color of left child is same as color of node
        node->optimalDepth = node->right->optimalDepth + 1;
      } else if(node->right->color == node->color) {
        // Color of right child is same as color of node
        // if(node->idx == 49) {
        //   cout << "Hello: " << node->left->optimalDepth << endl;
        // }
        node->optimalDepth = node->left->optimalDepth + 1;
      } else {
        // Colors are different from node color
        node->optimalDepth = max(node->left->optimalDepth, node->right->optimalDepth) + 1;
      }
    }

    // Calculate optimal path
    if((node->left->color == node->color) && (node->right->color == node->color)) {
      node->optimalPath = max(node->left->optimalPath, node->right->optimalPath);
      // cout << endl;
      // cout << "Index: " << node->idx << endl;
      // cout << "Optimal path: " << node->optimalPath << endl;
      // cout << "Optimal depth: " << node->optimalDepth << endl;
    } else {
      // node->optimalPath = node->left->optimalDepth + node->right->optimalDepth + 1;
      int optimalPathChilds = max(node->left->optimalPath, node->right->optimalPath);
      int optimalPathComp = node->left->optimalDepth + node->right->optimalDepth + 1;
      node->optimalPath = max(optimalPathChilds, optimalPathComp);
      // cout << endl;
      // cout << "Index: " << node->idx << endl;
      // cout << "Optimal Path Childs: " << optimalPathChilds << endl;
      // cout << "Optimal Path Comp: " << optimalPathComp << endl;
      // cout << "Optimal path: " << node->optimalPath << endl;
      // cout << "Optimal depth: " << node->optimalDepth << endl;
      // cout << "Left optimal depth: " << node->left->optimalDepth << endl;
      // cout << "right optimal depth: " << node->right->optimalDepth << endl;
    }

    // if(node->idx == 81 || node->idx == 121 || node->idx == 122) {
    //   cout << "Node: " << node->idx << endl;
    //   cout << "Optimal depth: " << node->optimalDepth << endl;
    //   cout << "Optimal path: " << node->optimalPath << endl;
    //   cout << "Parent: " << node->parent->idx << endl;
    //   cout << "Node color: " << node->color << endl;
    //   cout << "Node left color: " << node->left->color << " " << node->left->idx << endl;
    //   cout << "Node right color: " << node->right->color << endl;
    //   cout << endl;
    // }
}

/* MAIN */
int main() {
  int n;
  cin >> n;
  // Load nodes of tree to vector list
  vector<int> inputTree(n);
  for (int i = 0; i < n; ++i) {
      cin >> inputTree[i];
  }

  // for (int i = 0; i < n; ++i) {
  //   printf("%i ", inputTree[i]);
  // }

  // cout << endl;
  // cout << endl;

  TreeNode* root = buildTree(inputTree);

  // printInorder(root);
  // cout << endl;

  //Solving
  solve(root);
  // printTree(root, 0);
  // cout << "Root optimal path: " << root->optimalPath << endl;
  cout << root->optimalPath << endl;

  return 0;
}
 
// Definitions of functions
