//Semi Balanced
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct bstnode_t 
{
    long long key;
    struct bstnode_t \
        *left, *right;
} BSTNode;
typedef struct bst_t 
{
    BSTNode *_root;
    long long _size;
} BST;

BSTNode* __bst__createNode(long long value) 
{
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}
BSTNode* __bst__insert(BSTNode *root, long long value) 
{
    if (root == NULL) 
        return __bst__createNode(value);

    if (value < root->key)
        root->left = __bst__insert(root->left, value);
    else if (value > root->key)
        root->right = __bst__insert(root->right, value);
    
    return root;
}
BSTNode* __bst__search(BSTNode *root, int value) 
{
    while (root != NULL) 
    {
        if (value < root->key)
            root = root->left;
        else if (value > root->key)
            root = root->right;
        else
            return root;
    }
    return root;
}
BSTNode* __bst__findMinNode(BSTNode *node) 
{
    BSTNode *currNode = node;
    while (currNode && currNode->left != NULL)
        currNode = currNode->left;
    
    return currNode;
}
BSTNode* __bst__remove(BSTNode *root, int value) 
{
    if (root == NULL) return NULL;

    if (value > root->key) 
        root->right = __bst__remove(root->right, value);
    else if (value < root->key) 
        root->left = __bst__remove(root->left, value);
    else 
    {
        
        if (root->left == NULL) 
        {
            BSTNode *rightChild = root->right;
            free(root);
            return rightChild;
        }
        else if (root->right == NULL) 
        {
            BSTNode *leftChild = root->left;
            free(root);
            return leftChild;
        }

        BSTNode *temp = __bst__findMinNode(root->right);
        root->key     = temp->key;
        root->right   = __bst__remove(root->right, temp->key);
    }
    return root;
}
void __bst__preorder(BSTNode *root) 
{
    if (root) 
    {
        printf("%lld ", root->key);
        __bst__preorder(root->left);
        __bst__preorder(root->right);
    }
}
void __bst__postorder(BSTNode *root) 
{
    if (root) 
    {
        __bst__postorder(root->left);
        __bst__postorder(root->right);
        printf("%lld ", root->key);
    }
}
void bst_init(BST *bst) 
{
    bst->_root = NULL;
    bst->_size = 0u;
}
bool bst_isEmpty(BST *bst) 
{
    return bst->_root == NULL;
}
bool bst_find(BST *bst, long long value) 
{
    BSTNode *temp = __bst__search(bst->_root, value);
    if (temp == NULL)
        return false;
    
    if (temp->key == value)
        return true;
    else
        return false;
}
void bst_insert(BST *bst, long long value) 
{
    if (!bst_find(bst, value)) 
    {
        bst->_root = __bst__insert(bst->_root, value);
        bst->_size++;
    }
}
void bst_remove(BST *bst, long long value) 
{
    if (bst_find(bst, value)) 
    {
        bst->_root = __bst__remove(bst->_root, value);
        bst->_size--;
    }
}
void bst_preorder(BST *bst)
{
    __bst__preorder(bst->_root);
}
void bst_postorder(BST *bst) 
{
    __bst__postorder(bst->_root);
}
void __bst__midpoint(BST *bst,  long long ni[], int low, int high)
 {

    if (low<=high)
    {
    int mid = (low + high)/2;
    bst_insert(bst, ni[mid]); 
    __bst__midpoint(bst, ni, low, mid-1);
    __bst__midpoint(bst, ni, mid+1, high);
    }
}
int main()
{
    BST set;
    bst_init(&set);
    int n;
    long long  *ni;
    scanf("%d", &n);
    ni=(long long*)malloc(n*sizeof(long long));
    for(int i=0; i<n; i++) 
    {
        scanf("%lld", &ni[i]);
    }
    __bst__midpoint(&set, ni, 0, n-1);
    bst_preorder(&set);
    printf("\n");
    bst_postorder(&set);
    printf("\n");
    return 0;
}
