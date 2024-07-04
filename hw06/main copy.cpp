// AVL tree implementation in C++

#include <iostream>
#include <climits>
using namespace std;

struct Node {
  Node *parent = nullptr;
  Node *left;
  Node *right;
  int key;
  int height;
  bool isDeleted = false;
  int maxDeletedChilds = 0;
};

struct Utils {
  Node *root;
  int depth;
  int balancedDepth;
  int numOfRot;
  int numOfCons;
};

// Functions

bool checkParentChildRelationShip(Node* node) {
  if(node == nullptr) {
    return true;
  }

  if(node->left != nullptr) {
    if(node->left->parent->key != node->key) {
      return false;
    }
  }

  if(node->right != nullptr) {
    if(node->right->parent->key != node->key) {
      return false;
    }
  }

  return checkParentChildRelationShip(node->left) && checkParentChildRelationShip(node->right);
}

bool checkIsDeleted(Node* node) {
  if(node == nullptr) {
    return true;
  }

  if(node->isDeleted == true) {
    return false;
  }

  return checkIsDeleted(node->left) && checkIsDeleted(node->right);
}

// Calculate height
int height(Node *N) {
  if (N == NULL) {
    return 0;
  }
  return N->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

// New node creation
Node *newNode(int key) {
  Node *node = new Node();
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
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
        // std::cout << "(" << node->key << " | " << node->height<< ")" << std::endl;
        std::cout << "(" << node->key << " | " << node->isDeleted << ")" << std::endl;
        // std::cout << node->key << std::endl;

        // Traverse the left subtree
        printTree(node->left, depth + 1);
    }
}

void updateNumOfDeletedNodes(Node *node) {
  // cout << "Hello from update deleted nodes" << endl;
  while(node != nullptr) {
    // cout << "Update node: " << node->key << endl;
    int maxFromDeletedChilds = 0;
    
    if(node->left != nullptr && node->right != nullptr) {
      maxFromDeletedChilds = max(node->left->maxDeletedChilds, node->right->maxDeletedChilds);
    } else if(node->left != nullptr) {
      maxFromDeletedChilds = node->left->maxDeletedChilds;
    }else if(node->right != nullptr) {
      maxFromDeletedChilds = node->right->maxDeletedChilds;
    }

    if(node->isDeleted == true) {
      // cout << "It is working" << endl;
      node->maxDeletedChilds = maxFromDeletedChilds + 1;
    } else {
      node->maxDeletedChilds = maxFromDeletedChilds;
    }
    node = node->parent;
  }
};

void updateNumOfDeletedNodes1(Node *node) {
  // cout << "Hello from update deleted nodes" << endl;
  // cout << "Update node: " << node->key << endl;
  int maxFromDeletedChilds = 0;
  
  if(node->left != nullptr && node->right != nullptr) {
    maxFromDeletedChilds = max(node->left->maxDeletedChilds, node->right->maxDeletedChilds);
  } else if(node->left != nullptr) {
    maxFromDeletedChilds = node->left->maxDeletedChilds;
  }else if(node->right != nullptr) {
    maxFromDeletedChilds = node->right->maxDeletedChilds;
  }

  if(node->isDeleted == true) {
    // cout << "It is working" << endl;
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
  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;
  updateNumOfDeletedNodes(x);
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
  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;
  updateNumOfDeletedNodes(y);
  utils->numOfRot = utils->numOfRot + 1;
  return y;
}

// Get the balance factor of each node
int getBalanceFactor(Node *N) {
  if (N == NULL) {
    return 0;
  }
  return height(N->left) - height(N->right);
}

// Insert a node
Node *insertNode(Node *node, int key, Utils *utils) {
  // Find the correct postion and insert the node
  if (node == NULL) {
    return newNode(key);
  }
  
  if (key < node->key) {
    node->left = insertNode(node->left, key, utils);
    node->left->parent = node;
  } else if (key > node->key) {
    node->right = insertNode(node->right, key, utils);
    node->right->parent = node;
  } else {
    if(node->isDeleted == true) {
      node->isDeleted = false;
      updateNumOfDeletedNodes(node);
    }
    return node;
  }

  // Update the balance factor of each node and
  // balance the tree
  node->height = 1 + max(height(node->left), height(node->right));
  int balanceFactor = getBalanceFactor(node);
  if (balanceFactor > 1) {
    // Left subtree
    // utils->numOfRot = utils->numOfRot + 1;
    if (key < node->left->key) {
      return rightRotate(node, utils);
    } else if (key > node->left->key) {
      node->left = leftRotate(node->left, utils);
      return rightRotate(node, utils);
    }
  }
  if (balanceFactor < -1) {
    // Right subtree
    // utils->numOfRot = utils->numOfRot + 1;
    if (key > node->right->key) {
      return leftRotate(node, utils);
    } else if (key < node->right->key) {
      node->right = rightRotate(node->right, utils);
      return leftRotate(node, utils);
    }
  }
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

void deleteNode(Node *node, int key) {
  // Find the node and delete it
  if (node == NULL) {
    return;
  }
  if (key < node->key) {
    deleteNode(node->left, key);
  } else if (key > node->key) {
    deleteNode(node->right, key);
  } else {
    node->isDeleted = true;
    updateNumOfDeletedNodes1(node);
  } 
  updateNumOfDeletedNodes1(node);
}

// Delete a node
Node *removeNode(Node *node, int key, Utils *utils) {
  // Find the node and delete it
  if (node == nullptr) {
    return node;
  }
  if (key < node->key) {
    node->left = removeNode(node->left, key, utils);
  }
  else if (key > node->key) {
    node->right = removeNode(node->right, key, utils);
  }
  else {
    // key == node key
    if(node->left == nullptr && node->right == nullptr) {
      return nullptr;
    } else if(node->left != nullptr) {
      // Go to the left child
      // Go maximum right
      Node *temp = nodeWithMaximumValue(node->left);
      node->key = temp->key;
      node->isDeleted = false;
      node->left = removeNode(node->left, temp->key, utils);
      // Dont need to update parents
    } else {
      Node *temp = nodeWithMimumValue(node->right);
      node->key = temp->key;
      node->isDeleted = false;
      node->right = removeNode(node->right, temp->key, utils);
      // Dont need to update parents
    }
  }

  if (node == nullptr) {
    return node;
  }
  // cout << "BEFORE ROTATIONS" << endl;
  // printTree(utils->root, 0);
  // Update the balance factor of each node and
  // balance the tree
  node->height = 1 + max(height(node->left), height(node->right));
  int balanceFactor = getBalanceFactor(node);
  if (balanceFactor > 1) {
    if (getBalanceFactor(node->left) >= 0) {
      return rightRotate(node, utils);
    } else {
      node->left = leftRotate(node->left, utils);
      return rightRotate(node, utils);
    }
  }
  if (balanceFactor < -1) {
    if (getBalanceFactor(node->right) <= 0) {
      return leftRotate(node, utils);
    } else {
      node->right = rightRotate(node->right, utils);
      return leftRotate(node, utils);
    }
  }
  return node;
}

Node* findDeletedPostOrder(Node *node, Utils *utils) {
  Node *deletedNode = nullptr;

  if(node->left != nullptr) {
    deletedNode = findDeletedPostOrder(node->left, utils);
    if(deletedNode != nullptr) {
      return deletedNode;
    }
  }

  if(node->right != nullptr) {
    deletedNode = findDeletedPostOrder(node->right, utils);
    if(deletedNode != nullptr) {
      return deletedNode;
    }
  }

  if(node->isDeleted == true) {
    return node;
  }
  node->maxDeletedChilds = 0;
  return nullptr;
}

void doConsolidation(Utils *utils) {
  Node* deletedNode = findDeletedPostOrder(utils->root, utils);
  cout << "Node for delete: " << deletedNode->key << endl;
  // if(deletedNode != nullptr) {
  //   utils->root = removeNode(utils->root, deletedNode->key, utils);
  // }
}

int main() {
  // Read and store first line
  int N;
  cin >> N;

  int key;
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
  utils->root = root;

  while (cin >> key) {
      // cout << key << endl;
      if (key >= 0) {
        // cout << "Inset operation: " << key << endl;
        root = insertNode(utils->root, key, utils);
        // Update the root bacause in rotation root can be changed
        utils->root = root;
      } else {
        key = -key;
        deleteNode(utils->root, key);
        // cout << "Deleted node: " << key << endl;
        // printTree(utils->root, 0);
      }
      utils->depth = (utils->root->height - 1);
      utils->balancedDepth = 1 + (utils->depth / 2);
      // cout << "Depth of tree: " << utils->depth << endl;
      // cout << "Balanced depth of tree: " << utils->balancedDepth << endl;
      if(utils->root->maxDeletedChilds >= utils->balancedDepth) {
        // cout << "CONSOLIDATE THE TREE" << endl;
        utils->numOfCons = utils->numOfCons + 1;
        doConsolidation(utils);
        if(checkIsDeleted(utils->root) == false) {
          cout << "Something goes wrong" << endl;
          printTree(utils->root, 0);
          break;
        };
      }

  }

  // if(checkParentChildRelationShip(utils->root) == false) {
  //   break;
  // }
  
  // printTree(utils->root, 0);
  utils->depth = utils->root == nullptr ? -1 : (utils->root->height - 1);
  cout << "Depth of tree: " << utils->depth << endl;
  cout << "Number of rotations: " << utils->numOfRot << endl;
  cout << "Number of consolidations: " << utils->numOfCons << endl;
}

//TODO: in rotation root can be changed