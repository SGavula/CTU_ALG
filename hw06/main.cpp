// Source of AVL tree implementation in C++: https://www.programiz.com/dsa/avl-tree

#include <iostream>
#include <climits>
using namespace std;

struct Node {
  Node *parent = nullptr;
  Node *left;
  Node *right;
  int key;
  int height = 0;
  bool isDeleted = false;
  int maxDeletedChilds = 0;
};

struct Utils {
  Node *root;
  int depth;
  int balancedDepth;
  int numOfRot;
  int numOfCons;
  int numOfDeleted;
  int numberOfNodes;
  bool stop;
};

// Declarations of functions
bool checkIsDeleted(Node* node);
int max(int a, int b);
Node *newNode(int key);
bool isBSTUtil(Node* node, int minValue, int maxValue);
void printTree(Node* node, int depth);
void updateNumOfDeletedNodesToRoot(Node *node);
void updateNumOfDeletedNodesInCurrentNode(Node *node);
Node *rightRotate(Node *y, Utils *utils);
Node *leftRotate(Node *x, Utils *utils);
int getBalanceFactor(Node *N);
Node *insertNode(Node *node, int key, Utils *utils);
Node *nodeWithMimumValue(Node *node);
Node *nodeWithMaximumValue(Node *node);
void deleteNode(Node *node, int key, Utils *utils);
Node *removeNode(Node *node, int key, Utils *utils);
Node* findDeletedPostOrder(Node *node, Utils *utils);
void doConsolidation(Utils *utils);
int countNodes(Node* node);
int countDeletedNodesInTree(Node* node);

/* MAIN */
int main() {
  int numOfLines = 0;
  // Read and store first line
  int N;
  cin >> N;

  int key;
  int key_test;
  Node *root = NULL;
  cin >> key;
  root = newNode(key);

  // Init utils
  Utils *utils = new Utils;  // Create an instance of the Utils structure
  // Initialize the member variables
  utils->depth = -1;
  utils->balancedDepth = 0;
  utils->numOfRot = 0;
  utils->numOfCons = 0;
  utils->numOfDeleted = 0;
  utils->numberOfNodes = 1;
  utils->root = root;
  utils->stop = false;

  while (cin >> key) {
    numOfLines++;
    if (key >= 0) {
      root = insertNode(utils->root, key, utils);
      utils->root = root;
    } else {
      key_test = key;
      key = -key;
      deleteNode(utils->root, key, utils);
    }
    utils->balancedDepth = 1 + (utils->root->height / 2);

    if(utils->root->maxDeletedChilds >= utils->balancedDepth) {
      utils->numOfCons = utils->numOfCons + 1;
      while(utils->numOfDeleted != 0) {
        doConsolidation(utils);
        if(utils->stop == true) {
          break;
        }
        if(utils->root != nullptr) {
          utils->balancedDepth = 1 + (utils->root->height / 2);
        }
      }
      if(utils->stop == true) {
        break;
      }
    }
  }

  utils->depth = utils->root == nullptr ? -1 : utils->root->height;
  cout << utils->depth << " " << utils->numOfRot << " " << utils->numOfCons  << endl;
}

// Definitions of functions
bool checkIsDeleted(Node* node) {
  if(node == nullptr) {
    return true;
  }

  if(node->isDeleted == true) {
    return false;
  }

  return checkIsDeleted(node->left) && checkIsDeleted(node->right);
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

// New node creation
Node *newNode(int key) {
  Node *node = new Node();
  node->key = key;
  node->parent = nullptr;
  node->left = nullptr;
  node->right = nullptr;
  node->height = 0;
  node->isDeleted = false;
  node->maxDeletedChilds = 0;
  return node;
} 

bool isBSTUtil(Node* node, int minValue, int maxValue) {
    if (node == nullptr) {
        return true;  // An empty tree is a BST
    }

    // Check the current node's value against the allowed range
    if (node->key < minValue || node->key > maxValue) {
        cout <<  node->key << endl;
        return false;
    }

    // Recursively check the left and right subtrees with updated ranges
    return isBSTUtil(node->left, minValue, node->key - 1) &&
           isBSTUtil(node->right, node->key + 1, maxValue);
}

void printTree(Node* node, int depth) {
    const int INDENTATION = 4; // Adjust the indentation level as needed

    if (node != nullptr) {
        // Traverse the right subtree
        printTree(node->right, depth + 1);

        // Print the current node's key with indentation
        for (int i = 0; i < depth * INDENTATION; ++i) {
            std::cout << ' ';
        }
        int parentKey = node->parent != nullptr ? node->parent->key : -1;
        // std::cout << "(" << node->key << " | " << node->height << " | " << node->isDeleted << " | " << node->maxDeletedChilds <<")" << std::endl;
        // std::cout << "(" << node->key << " | " << node->maxDeletedChilds << " | Parent: " << parentKey << ")" << std::endl;
        std::cout << "(" << node->key << " | " << node->maxDeletedChilds << " | " << node->isDeleted  <<  ")" << std::endl;
        // std::cout << "(" << node->key << " | " << node->height<< ")" << std::endl;
        // std::cout << "(" << node->key << " | " << node->isDeleted << ")" << std::endl;
        // std::cout << node->key << std::endl;

        // Traverse the left subtree
        printTree(node->left, depth + 1);
    }
}

void updateNumOfDeletedNodesToRoot(Node *node) {
  while(node != nullptr) {
    int maxFromDeletedChilds = 0;
    
    if(node->left != nullptr && node->right != nullptr) {
      maxFromDeletedChilds = max(node->left->maxDeletedChilds, node->right->maxDeletedChilds);
    } else if(node->left != nullptr) {
      maxFromDeletedChilds = node->left->maxDeletedChilds;
    }else if(node->right != nullptr) {
      maxFromDeletedChilds = node->right->maxDeletedChilds;
    }

    if(node->isDeleted == true) {
      node->maxDeletedChilds = maxFromDeletedChilds + 1;
    } else {
      node->maxDeletedChilds = maxFromDeletedChilds;
    }
    node = node->parent;
  }
};

void updateNumOfDeletedNodesInCurrentNode(Node *node) {
  if(node == nullptr) {
    return;
  }

  int maxFromDeletedChilds = 0;
  
  if(node->left != nullptr && node->right != nullptr) {
    maxFromDeletedChilds = max(node->left->maxDeletedChilds, node->right->maxDeletedChilds);
  } else if(node->left != nullptr) {
    maxFromDeletedChilds = node->left->maxDeletedChilds;
  }else if(node->right != nullptr) {
    maxFromDeletedChilds = node->right->maxDeletedChilds;
  }

  if(node->isDeleted == true) {
    node->maxDeletedChilds = maxFromDeletedChilds + 1;
  } else {
    node->maxDeletedChilds = maxFromDeletedChilds;
  }
};

// Rotate right
Node *rightRotate(Node *y, Utils *utils) {
  Node *yParent = y->parent;
  Node *x = y->left;
  x->parent = yParent;
  Node *T2 = x->right;
  x->right = y;
  y->parent = x;
  y->left = T2;
  if(y->left != nullptr) {
    y->left->parent = y;
  }
  int yLeftHeight = y->left != nullptr ? y->left->height : -1;
  int yRightHeight = y->right != nullptr ? y->right->height : -1;
  x->right->height = max(yLeftHeight, yRightHeight) + 1;
  
  int xLeftHeight = x->left != nullptr ? x->left->height : -1;
  int xRightHeight = x->right != nullptr ? x->right->height : -1;
  x->height = max(xLeftHeight, xRightHeight) + 1;
  updateNumOfDeletedNodesInCurrentNode(y);
  updateNumOfDeletedNodesInCurrentNode(x);
  utils->numOfRot = utils->numOfRot + 1;
  return x;
}

// Rotate left
Node *leftRotate(Node *x, Utils *utils) {
  Node *xParent = x->parent;
  Node *y = x->right;
  y->parent = xParent;
  Node *T2 = y->left;
  y->left = x;
  x->parent = y;
  x->right = T2;
  if(x->right != nullptr) {
    x->right->parent = x;
  } 

  int xLeftHeight = x->left != nullptr ? x->left->height : -1;
  int xRightHeight = x->right != nullptr ? x->right->height : -1;
  y->left->height = max(xLeftHeight, xRightHeight) + 1;
  
  int yLeftHeight = y->left != nullptr ? y->left->height : -1;
  int yRightHeight = y->right != nullptr ? y->right->height : -1;
  y->height = max(yLeftHeight, yRightHeight) + 1;
  updateNumOfDeletedNodesInCurrentNode(x);
  updateNumOfDeletedNodesInCurrentNode(y);
  utils->numOfRot = utils->numOfRot + 1;
  return y;
}

// Get the balance factor of each node
int getBalanceFactor(Node *N) {
  if (N == NULL) {
    return 0;
  }
  int leftHeight = N->left != nullptr ? N->left->height : -1;
  int rightHeight = N->right != nullptr ? N->right->height : -1;
  return leftHeight- rightHeight;
}

// Insert a node
Node *insertNode(Node *node, int key, Utils *utils) {
  // Find the correct postion and insert the node
  if (node == NULL) {
    utils->numberOfNodes = utils->numberOfNodes + 1;
    return newNode(key);
  }
  
  if (key < node->key) {
    node->left = insertNode(node->left, key, utils);
    node->left->parent = node;
    updateNumOfDeletedNodesInCurrentNode(node);
  } else if (key > node->key) {
    node->right = insertNode(node->right, key, utils);
    node->right->parent = node;
    updateNumOfDeletedNodesInCurrentNode(node);
  } else {
    if(node->isDeleted == true) {
      node->isDeleted = false;
      utils->numOfDeleted = utils->numOfDeleted - 1;
      updateNumOfDeletedNodesToRoot(node);
    }
    return node;
  }

  // Update the balance factor of each node and
  // balance the tree
  int leftHeight = node->left != nullptr ? node->left->height : -1;
  int rightHeight = node->right != nullptr ? node->right->height : -1;
  node->height = 1 + max(leftHeight, rightHeight);
  int balanceFactor = getBalanceFactor(node);
  if (balanceFactor > 1) {
    // Left subtree
    if (key < node->left->key) {
      return rightRotate(node, utils);
    } else if (key > node->left->key) {
      node->left = leftRotate(node->left, utils);
      updateNumOfDeletedNodesInCurrentNode(node);
      return rightRotate(node, utils);
    }
  }
  if (balanceFactor < -1) {
    // Right subtree
    if (key > node->right->key) {
      return leftRotate(node, utils);
    } else if (key < node->right->key) {
      node->right = rightRotate(node->right, utils);
      updateNumOfDeletedNodesInCurrentNode(node);
      return leftRotate(node, utils);
    }
  }
  updateNumOfDeletedNodesInCurrentNode(node);
  return node;
}

// Node with minimum value
Node *nodeWithMimumValue(Node *node) {
  Node *current = node;
  while (current->left != NULL) {
    current = current->left;
  }
  return current;
}

Node *nodeWithMaximumValue(Node *node) {
  Node *current = node;
  while (current->right != NULL) {
    current = current->right;
  }
  return current;
}

void deleteNode(Node *node, int key, Utils *utils) {
  // Find the node and delete it
  if (node == NULL) {
    return;
  }
  if (key < node->key) {
    deleteNode(node->left, key, utils);
  } else if (key > node->key) {
    deleteNode(node->right, key, utils);
  } else {
    if(node->isDeleted == false) {
      node->isDeleted = true;
      utils->numOfDeleted = utils->numOfDeleted + 1;
    }
  }
  updateNumOfDeletedNodesInCurrentNode(node);
}

// Delete a node
Node *removeNode(Node *node, int key, Utils *utils) {
  // Find the node and delete it
  if (node == nullptr) {
    return node;
  }
  if (key < node->key) {
    node->left = removeNode(node->left, key, utils);
    updateNumOfDeletedNodesInCurrentNode(node);
  }
  else if (key > node->key) {
    node->right = removeNode(node->right, key, utils);
    updateNumOfDeletedNodesInCurrentNode(node);
  }
  else {
    // key == node key
    if(node->left == nullptr && node->right == nullptr) {
      utils->numberOfNodes = utils->numberOfNodes - 1;
      utils->numOfDeleted = utils->numOfDeleted - 1;
      return nullptr;
    } else if(node->left != nullptr) {
      // Go to the muximum right in left child
      Node *temp = nodeWithMaximumValue(node->left);
      node->key = temp->key;
      node->isDeleted = false;
      node->left = removeNode(node->left, temp->key, utils);
      updateNumOfDeletedNodesInCurrentNode(node);
    } else {
      // Go to the muximum left in right child
      Node *temp = nodeWithMimumValue(node->right);
      node->key = temp->key;
      node->isDeleted = false;
      node->right = removeNode(node->right, temp->key, utils);
      updateNumOfDeletedNodesInCurrentNode(node);
    }
  }

  if (node == nullptr) {
    return node;
  }
  // Update the balance factor of each node and balance the tree
  int leftHeight = node->left != nullptr ? node->left->height : -1;
  int rightHeight = node->right != nullptr ? node->right->height : -1;
  node->height = 1 + max(leftHeight, rightHeight);
  int balanceFactor = getBalanceFactor(node);
  if (balanceFactor > 1) {
    if (getBalanceFactor(node->left) >= 0) {
      // cout << "Make right rotation on node: " << node->key << endl;
      return rightRotate(node, utils);
    } else {
      node->left = leftRotate(node->left, utils);
      updateNumOfDeletedNodesInCurrentNode(node);
      return rightRotate(node, utils);
    }
  }
  if (balanceFactor < -1) {
    if (getBalanceFactor(node->right) <= 0) {
      return leftRotate(node, utils);
    } else {
      node->right = rightRotate(node->right, utils);
      updateNumOfDeletedNodesInCurrentNode(node);
      return leftRotate(node, utils);
    }
  }
  // Decrease the number of maxDeletedChilds
  updateNumOfDeletedNodesInCurrentNode(node);
  return node;
}

Node* findDeletedPostOrder(Node *node, Utils *utils) {
  Node *deletedNode = nullptr;
  
  if(node == nullptr || node->maxDeletedChilds == 0) {
    return nullptr;
  }

  // Go left
  deletedNode = findDeletedPostOrder(node->left, utils);
  if(deletedNode != nullptr) {
    return deletedNode;
  }

  // Go right
  deletedNode = findDeletedPostOrder(node->right, utils);
  
  if(node->isDeleted == true && deletedNode == nullptr) {
    return node;
  }

  return deletedNode;
}

void doConsolidation(Utils *utils) {
  Node* deletedNode = findDeletedPostOrder(utils->root, utils);
  if(deletedNode != nullptr) {
    utils->root = removeNode(utils->root, deletedNode->key, utils);
    if(utils->root != nullptr) {
      updateNumOfDeletedNodesInCurrentNode(utils->root);
    }
  }else {
    utils->stop = true;
    cout << "No node for remove" << endl;
  }
}

int countNodes(Node* node) {
    if (!node) {
        return 0;
    }
    return 1 + countNodes(node->left) + countNodes(node->right);
}

int countDeletedNodesInTree(Node* node) {
    if (!node) {
        return 0;
    }
    if(node->isDeleted == true) {
      return 1 + countNodes(node->left) + countNodes(node->right);
    }else {
      return countNodes(node->left) + countNodes(node->right);
    }
}

