//Indice del BST
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct bstnode_t 
{
    unsigned long long  key;
    struct bstnode_t \
        *left, *right;
} BSTNode;
typedef struct bst_t 
{
    BSTNode *_root;
    unsigned long long _size;
} BST;

BSTNode* __bst__createNode(unsigned long long  value) 
{
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}
BSTNode* __bst__insert(BSTNode *root, unsigned long long value) 
{
    if (root == NULL) 
        return __bst__createNode(value);

    if (value < root->key)
        root->left = __bst__insert(root->left, value);
    else if (value > root->key)
        root->right = __bst__insert(root->right, value);
    
    return root;
}
BSTNode* __bst__search(BSTNode *root, unsigned long long  value) 
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
unsigned long long k,counter;//target, counter
void __bst__inorder(BSTNode *root) 
{
    if (root) 
    {
        __bst__inorder(root->left);
        counter++;
        if(k==root->key)
        {
            printf("%llu\n", counter);
        }
        __bst__inorder(root->right);
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
bool bst_find(BST *bst, long long int value) 
{
    BSTNode *temp = __bst__search(bst->_root, value);
    if (temp == NULL)
        return false;
    
    if (temp->key == value)
        return true;
    else
        return false;
}
void bst_insert(BST *bst, long long int value) 
{
    if (!bst_find(bst, value)) 
    {
        bst->_root = __bst__insert(bst->_root, value);
        bst->_size++;
    }
}
void bst_inorder(BST *bst) 
{
    __bst__inorder(bst->_root);
}
int main()
{
    BST set;
    bst_init(&set);
    unsigned long long T;
    unsigned long long q,x;
    scanf("%llu",&T);
    for(int i=0; i<T; i++)
    {
    scanf("%llu", &q);
    scanf("%llu", &x);
    counter=0;
        if(q==0)
        {
            bst_insert(&set,x);
        }
        else
        {
            if(bst_find(&set,x))
            {
                k=x;
                bst_inorder(&set);
            }
            else 
            {
                printf("Data not found\n");
            }
        }
    }
    return 0;
}