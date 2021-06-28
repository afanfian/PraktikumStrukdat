//Tinggi Ina
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct bstnode_t 
{
    int key;
    struct bstnode_t \
        *left, *right;
} BSTNode;
typedef struct bst_t 
{
    BSTNode *_root;
    int _size;
} BST;

BSTNode* __bst__createNode(int value) 
{
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}
BSTNode* __bst__insert(BSTNode *root, int value) 
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
int __bst__preorder(BSTNode *root) 
{
    if (root) 
    { 
        return 1 + __bst__preorder(root->left) +
        __bst__preorder(root->right);
    }
    return 0;
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
bool bst_find(BST *bst, int value) 
{
    BSTNode *temp = __bst__search(bst->_root, value);
    if (temp == NULL)
        return false;
    
    if (temp->key == value)
        return true;
    else
        return false;
}
void bst_insert(BST *bst, int value) 
{
    if (!bst_find(bst, value)) 
    {
        bst->_root = __bst__insert(bst->_root, value);
        bst->_size++;
    }
}
void bst_preorder(BST *bst) 
{
    __bst__preorder(bst->_root);
}
void bst_Child(BST *bst, int value) 
{
    int child;
    BST child2;
    bst_init(&child2);
    BSTNode *temp = __bst__search(bst->_root, value);
    child2._root = temp;
    child = __bst__preorder(child2._root);
    child = child-1; 
    printf("%d\n", child);
}
int main()
{
    BST set;
    bst_init(&set);
    int JumlahNode, ni, Q, node;
    scanf("%d", &JumlahNode);
    for(int j=0; j<JumlahNode; j++)
    {
        scanf("%d", &ni);
        bst_insert(&set, ni);
    }
    scanf("%d", &Q);
    for(int j=0; j<Q; j++)
    {
        scanf("%d", &node);
        if(bst_find(&set, node) != 0)
        {
            bst_Child(&set, node);
        }
        else 
        {
            printf("Tidak ditemukan\n");
        }
    }    
    return 0;
}
