#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
// source for some AVL code:
// https://www.geeksforgeeks.org/introduction-to-avl-tree/
int N;

typedef struct Node {
    int id;
    struct Node* left;
    struct Node* right;
    int height;
    int deletedChildren;
    bool isDeleted;
} Node;

typedef struct RebalancePair {
    Node* node;
    int consolidations;
    int rotations;
} RebalancePair;

int height(Node* N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int getBalance(Node* N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

Node* find(Node* root, int value)
{
    if (root == NULL)
    {
        return NULL;
    }
    Node* current = root;
    while (current->id != value)
    {
        if (value < current->id)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
        if (current == NULL)
        {
            return NULL;
        }
    }

    return current;
}

void fixNumOfDeletedChildren(Node* root)
{
    if (root == NULL)
    {
        return;
    }

    int numOfChildsLeft = (root->left) ? root->left->deletedChildren : 0;
    int numOfChildsRight = (root->right) ? root->right->deletedChildren : 0;

    root->deletedChildren = MAX(numOfChildsLeft, numOfChildsRight) + root->isDeleted;
}

Node* rightRotate(Node* y)
{
    Node* newRoot = y->left;
    Node* T2 = newRoot->right;

    // Perform rotation
    newRoot->right = y;
    y->left = T2;

    // Update heights
    y->height = MAX(height(y->left), height(y->right)) + 1;
    newRoot->height = MAX(height(newRoot->left), height(newRoot->right)) + 1;

    fixNumOfDeletedChildren(newRoot->left);

    fixNumOfDeletedChildren(newRoot->right);

    fixNumOfDeletedChildren(newRoot);

    // Return new root
    return newRoot;
}

Node* leftRotate(Node* leftChild)
{
    Node* newRoot = leftChild->right;
    Node* T2 = newRoot->left;

    // Perform rotation
    newRoot->left = leftChild;
    leftChild->right = T2;

    // Update heights
    leftChild->height = MAX(height(leftChild->left), height(leftChild->right)) + 1;
    newRoot->height = MAX(height(newRoot->left), height(newRoot->right)) + 1;


    fixNumOfDeletedChildren(newRoot->left);

    fixNumOfDeletedChildren(newRoot->right);

    fixNumOfDeletedChildren(newRoot);

    // Return new root
    return newRoot;
}
Node* minValueNode(Node* root)
{
    if (root == NULL)
    {
        return NULL;
    }
    Node* current = root;
    while (current->left != NULL)
    {
        current = current->left;
    }

    return current;
}

Node* maxValueNode(Node* root)
{
    if (root == NULL)
    {
        return NULL;
    }
    Node* current = root;
    while (current->right != NULL)
    {
        current = current->right;
    }

    return current;
}
int rotationsStandardInsert = 0;
Node* standardInsert(Node* root, Node* value)
{
    if (root == NULL)
    {
        return value;
    }

    if (value->id < root->id)
    {
        root->left = standardInsert(root->left, value);
        fixNumOfDeletedChildren(root);
    }
    else if (value->id > root->id)
    {
        root->right = standardInsert(root->right, value);
        fixNumOfDeletedChildren(root);
    }
    else
    {
        return root;
    }

    root->height = 1 + MAX(height(root->left), height(root->right));

    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && value->id < root->left->id)
    {
        rotationsStandardInsert++;
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && value->id > root->right->id)
    {
        rotationsStandardInsert++;
        return leftRotate(root);
    }
    // Left Right Case
    if (balance > 1 && value->id > root->left->id)
    {
        rotationsStandardInsert += 2;
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && value->id < root->right->id)
    {
        rotationsStandardInsert += 2;
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    fixNumOfDeletedChildren(root);
    return root;
}

Node* initChild(int value)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->id = value;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    newNode->deletedChildren = 0;
    newNode->isDeleted = false;

    return newNode;
}

int rotationsMyDelete = 0;
Node* rebalance(Node* root)
{

    // If the tree had only one node then return
    if (root == NULL)
        return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + MAX(height(root->left), height(root->right));

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
    {
        rotationsMyDelete++;
        return rightRotate(root);
    }

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        rotationsMyDelete += 2;
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
    {
        rotationsMyDelete++;
        return leftRotate(root);
    }

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        rotationsMyDelete += 2;
        return leftRotate(root);
    }

    return root;
}

Node* remove(struct Node* root, int key)
{
    if (root == NULL)
        return root;

    if (key < root->id)
    {
        root->left = remove(root->left, key);
        root->deletedChildren--;
    }
    else if (key > root->id)
    {
        root->right = remove(root->right, key);
        root->deletedChildren--;
    }
    else
    {

        if (root->left == NULL && root->right == NULL)
        {
            Node* temp = root;
            root = NULL;
            free(temp);
        }
        else if (root->left != NULL)
        {
            Node* maxChild = maxValueNode(root->left);
            root->id = maxChild->id;
            root->isDeleted = false;
            root->deletedChildren--;

            maxChild->isDeleted = true;
            root->left = remove(root->left, maxChild->id);
        }
        else if (root->right != NULL)
        {

            struct Node* temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->id = temp->id;
            root->isDeleted = temp->isDeleted;

            // Delete the inorder successor
            root->right = remove(root->right, temp->id);
            root->deletedChildren--;
        }
    }
    fixNumOfDeletedChildren(root);

    return rebalance(root);
}
bool foundLazyInsert = false;
int lazyInsert(Node* root, int value)
{
    if (root == NULL)
    {
        return 0;
    }

    if (root->id == value)
    {
        foundLazyInsert = true;
        if (root->isDeleted)
        {
            root->isDeleted = false;
            return --root->deletedChildren;
        }
        else
        {
            return root->deletedChildren;
        }
    }

    int numOfDeletedChildren = root->isDeleted;

    if (root->id > value)
    {
        numOfDeletedChildren = lazyInsert(root->left, value) + root->isDeleted;
        if (root->right)
            numOfDeletedChildren = MAX(numOfDeletedChildren, root->right->deletedChildren + root->isDeleted);
    }
    else
    {
        numOfDeletedChildren = lazyInsert(root->right, value) + root->isDeleted;
        if (root->left)
            numOfDeletedChildren = MAX(numOfDeletedChildren, root->left->deletedChildren + root->isDeleted);
    }

    root->deletedChildren = numOfDeletedChildren;

    return numOfDeletedChildren;
}

RebalancePair insert(Node* root, int value)
{
    RebalancePair pair;
    pair.node = root;
    pair.consolidations = 0;
    pair.rotations = 0;

    foundLazyInsert = false;
    // int deletedChildren = (root) ? root->deletedChildren : 0;
    lazyInsert(root, value);
    // if (deletedChildren != ((root) ? root->deletedChildren : 0) && foundLazyInsert == false)
    // {
    //     printf("major fuckup %d\n", value);
    // }

    if (foundLazyInsert)
    {
        return pair;
    }

    Node* newRoot = standardInsert(root, initChild(value));

    pair.node = newRoot;
    pair.rotations = rotationsStandardInsert;
    rotationsStandardInsert = 0;

    return pair;
}
//returns how many children are newly delted
int toDelete = 0;
int delete(Node* root, int value)
{
    if (root == NULL)
        return 0;

    if (root->isDeleted && root->id == value)
        return root->deletedChildren;

    if (root->id == value)
    {
        root->isDeleted = true;
        toDelete++;
        return ++root->deletedChildren;
    }

    int numOfDeletedChildren = root->isDeleted;

    if (root->id > value)
    {
        numOfDeletedChildren = delete(root->left, value) + root->isDeleted;
        if (root->right)
            numOfDeletedChildren = MAX(numOfDeletedChildren, root->right->deletedChildren + root->isDeleted);
    }
    else
    {
        numOfDeletedChildren = delete(root->right, value) + root->isDeleted;
        if (root->left)
            numOfDeletedChildren = MAX(numOfDeletedChildren, root->left->deletedChildren + root->isDeleted);
    }
    root->deletedChildren = numOfDeletedChildren;

    return numOfDeletedChildren;
}

static inline int getDepth(Node* root)
{
    if (root == NULL)
    {
        return -1;
    }
    else
    {
        return root->height - 1;
    }
}

Node* findFirstDeletedPostOrder(Node* root)
{
    if (root == NULL || root->deletedChildren == 0)
    {
        return NULL;
    }

    Node* left = NULL, * right = NULL;

    if ((left = findFirstDeletedPostOrder(root->left)))
    {
        return left;
    }
    else if ((right = findFirstDeletedPostOrder(root->right)))
    {
        return right;
    }

    // post order first should always have no deleted children
    if (left == NULL && right == NULL && root->isDeleted)
    {
        return root;
    }

    return NULL;
}

void cleanTree(Node* root)
{
    if (root == NULL)
    {
        return;
    }
    root->deletedChildren = 0;
    cleanTree(root->left);
    cleanTree(root->right);
    free(root);
}

void clearDeletedInTree(Node* root)
{
    if (root == NULL)
    {
        return;
    }

    clearDeletedInTree(root->left);
    clearDeletedInTree(root->right);
    root->isDeleted = false;
    root->deletedChildren = 0;
}

RebalancePair reconsolidate(Node* root)
{
    RebalancePair pair;
    pair.node = root;
    pair.consolidations = 0;
    pair.rotations = 0;

    if (root == NULL || root->deletedChildren < floor((float)getDepth(root) / 2) + 1)
        return pair;

    pair.consolidations++;

    Node* firstNodeToRemove = NULL;

    for (int i = 0; i < toDelete && (firstNodeToRemove = findFirstDeletedPostOrder(pair.node)); i++)
    {
        rotationsMyDelete = 0;
        pair.node = remove(pair.node, firstNodeToRemove->id);
        pair.rotations += rotationsMyDelete;
    }
    toDelete = 0;
    //assert(checkIfTreeIsCompletelyDeleted(pair.node));
    //clearDeletedInTree(pair.node);

    return pair;
}

int main()
{
    scanf("%d\n", &N);

    Node* root = NULL;

    int val = 0, rotations = 0, consolidations = 0;

    for (int i = 1; i <= N && scanf("%d", &val) == 1; i++)
    {
        if (val > 0)
        {
            RebalancePair resultInsert = insert(root, val);
            root = resultInsert.node;
            rotations += resultInsert.rotations;
            consolidations += resultInsert.consolidations;

        }
        else
        {
            delete (root, -val);
        }

        // if (root)
        //     printf("%d \n", root->deletedChildren);
        // else
        //     printf("%d \n", 0);

        RebalancePair result = reconsolidate(root);
        root = result.node;
        consolidations += result.consolidations;
        // if (result.consolidations > 0)
        //     printf("reconsolidated\n");
        rotations += result.rotations;

        if (i < N)
            scanf("\n");
    }



    printf("%d %d %d\n", getDepth(root), rotations, consolidations);
    return 0;
}