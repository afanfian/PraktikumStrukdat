//Schematown
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#define ul unsigned long
#define li long int

typedef struct bstnode_t 
{
    li key, weight, history;
    struct bstnode_t 
        *parent, *left, *right;
} BSTNode;
typedef struct bst_t 
{
    BSTNode *_root;
    unsigned int _size;
} BST;

BSTNode* __bst__createNode(li value, li weight) 
{
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->weight = weight;
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

BSTNode* __bst__insert(BSTNode *root, li value, ul weight) 
{
    if (root == NULL) 
        return __bst__createNode(value, weight);
    
    else {
        BSTNode *cur;
        if (value < root->key){
            cur = __bst__insert(root->left, value, weight);
            cur->parent = root;
            root->left = cur;
        }
        else if (value > root->key){
            cur = __bst__insert(root->right, value, weight);
            cur->parent = root;
            root->right = cur;
        }
        return root;
    }
}
BSTNode* __bst__search(BSTNode *root, li value) 
{
    while (root != NULL) 
    {
        if (value < root->key)
        {
            root = root->left;
        }
        else if (value > root->key)
        {
            root = root->right;
        }
        else
            return root;
    }
    return root;
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
bool bst_find(BST *bst, li value)
{
    BSTNode *temp = __bst__search(bst->_root, value);
    if (temp == NULL)
        return false;
    
    if (temp->key == value)
        return true;
    else
        return false;
}
BSTNode* bst_findNode(BST *bst, li value) 
{
    BSTNode *temp = __bst__search(bst->_root, value);
    if (temp != NULL)
        return temp;
    else return NULL;
}

void bst_insert(BST *bst, li value, li weight) 
{
    if (!bst_find(bst, value)) 
    {
        bst->_root = __bst__insert(bst->_root, value, weight);
        bst->_size++;
    }
}
int bst_isLeaf(BSTNode *root)
{
    return(root->left == NULL && root->right == NULL);
}
void bst_setHistory(BSTNode *root)
{
    if(root == NULL) return;
    root->history = 0;
    bst_setHistory(root->left);
    bst_setHistory(root->right);
}
void find_shortest(BSTNode *root, li curr_dist, li *distance)
{
    if(root == NULL) return;
    root->history = 1; 
    if(bst_isLeaf(root))
    {
        if(*distance == -1) *distance = curr_dist;
        else if(*distance > curr_dist) *distance = curr_dist;
        return;
    }
    if(root->parent != NULL && root->parent->history == 0) find_shortest(root->parent, curr_dist + root->weight,       distance);
    if(root->left   != NULL && root->left->history   == 0) find_shortest(root->left,   curr_dist + root->left->weight, distance);
    if(root->right  != NULL && root->right->history  == 0) find_shortest(root->right,  curr_dist + root->right->weight,distance);
    return;
}
int main()
{
    BST set; bst_init(&set);
    li N; scanf("%ld", &N);
    li root; scanf("%ld", &root);
    bst_insert(&set, root, 0);
    while (--N)
    {
        li value, weight; 
        scanf("%ld%ld", &value, &weight);
        bst_insert(&set, value, weight);
    }
    li T; scanf("%ld", &T);
    BSTNode *rootAd = NULL;
    while (T--)
    {
        bst_setHistory(set._root);
        li value; scanf("%ld", &value);
        rootAd = bst_findNode(&set, value);
        li distance = -1;
        find_shortest(rootAd, 0, &distance);
        printf("%ld ", distance);
    }
    printf("\n");
    return 0;
}
