//Tinggi Pol
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
 
typedef struct AVLNode_t
{
    int data;
    struct AVLNode_t *left,*right;
    int height;
}AVLNode;
 
typedef struct AVL_t
{
    AVLNode *_root;
    unsigned int _size;
}AVL;
 
AVLNode* _avl_createNode(int value) {
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    newNode->data = value;
    newNode->height=1;
    newNode->left = newNode->right = NULL;
    return newNode;
}
 
AVLNode* _search(AVLNode *root, int value) {
    while (root != NULL) {
        if (value < root->data)
            root = root->left;
        else if (value > root->data)
            root = root->right;
        else
            return root;
    }
    return root;
}
 
int _getHeight(AVLNode* node){
    if(node==NULL) return 0;
    return node->height;
}
 
int _max(int a,int b){
    return (a > b)? a : b;
}
 
AVLNode* _rightRotate(AVLNode* pivotNode) {
 
    AVLNode* newParrent=pivotNode->left;
    pivotNode->left=newParrent->right;
    newParrent->right=pivotNode;
 
    pivotNode->height=_max(_getHeight(pivotNode->left),
                      _getHeight(pivotNode->right))+1;
    newParrent->height=_max(_getHeight(newParrent->left),
                       _getHeight(newParrent->right))+1;
 
    return newParrent;
}
 
AVLNode* _leftRotate(AVLNode* pivotNode) {
 
    AVLNode* newParrent=pivotNode->right;
    pivotNode->right=newParrent->left;
    newParrent->left=pivotNode;
 
    pivotNode->height=_max(_getHeight(pivotNode->left),
                      _getHeight(pivotNode->right))+1;
    newParrent->height=_max(_getHeight(newParrent->left),
                       _getHeight(newParrent->right))+1;
 
    return newParrent;
}
 
AVLNode* _leftCaseRotate(AVLNode* node){
    return _rightRotate(node);
}
 
AVLNode* _rightCaseRotate(AVLNode* node){
    return _leftRotate(node);
}
 
AVLNode* _leftRightCaseRotate(AVLNode* node){
    node->left=_leftRotate(node->left);
    return _rightRotate(node);
}
 
AVLNode* _rightLeftCaseRotate(AVLNode* node){
    node->right=_rightRotate(node->right);
    return _leftRotate(node);
}
 
int _getBalanceFactor(AVLNode* node){
    if(node==NULL)
        return 0;
    return _getHeight(node->left)-_getHeight(node->right);
}
 
AVLNode* _insert_AVL(AVL *avl,AVLNode* node,int value) {
 
    if(node==NULL) // udah mencapai leaf
        return _avl_createNode(value);
    if(value < node->data)
        node->left = _insert_AVL(avl,node->left,value);
    else if(value > node->data)
        node->right = _insert_AVL(avl,node->right,value);
 
    node->height= 1 + _max(_getHeight(node->left),_getHeight(node->right));
 
    int balanceFactor=_getBalanceFactor(node);
 
    if(balanceFactor > 1 && value < node->left->data) // skewed kiri (left-left case)
        return _leftCaseRotate(node);
    if(balanceFactor > 1 && value > node->left->data) //
        return _leftRightCaseRotate(node);
    if(balanceFactor < -1 && value > node->right->data)
        return _rightCaseRotate(node);
    if(balanceFactor < -1 && value < node->right->data)
        return _rightLeftCaseRotate(node);
 
    return node;
}
 
AVLNode* _findMinNode(AVLNode *node) {
    AVLNode *currNode = node;
    while (currNode && currNode->left != NULL)
        currNode = currNode->left;
    return currNode;
}
 
AVLNode* _remove_AVL(AVLNode* node,int value){
    if(node==NULL)
        return node;
    if(value > node->data)
        node->right=_remove_AVL(node->right,value);
    else if(value < node->data)
        node->left=_remove_AVL(node->left,value);
    else{
        AVLNode *temp;
        if((node->left==NULL)||(node->right==NULL)){
            temp=NULL;
            if(node->left==NULL) temp=node->right;
            else if(node->right==NULL) temp=node->left;
 
            if(temp==NULL){
                temp=node;
                node=NULL;
            }
            else
                *node=*temp;
 
            free(temp);
        }
        else{
            temp = _findMinNode(node->right);
            node->data=temp->data;
            node->right=_remove_AVL(node->right,temp->data);
        }
    }
 
    if(node==NULL) return node;
 
    node->height=_max(_getHeight(node->left),_getHeight(node->right))+1;
 
    int balanceFactor= _getBalanceFactor(node);
 
    if(balanceFactor>1 && _getBalanceFactor(node->left)>=0)
        return _leftCaseRotate(node);
 
    if(balanceFactor>1 && _getBalanceFactor(node->left)<0)
        return _leftRightCaseRotate(node);
 
    if(balanceFactor < -1 && _getBalanceFactor(node->right)<=0)
        return _rightCaseRotate(node);
 
    if(balanceFactor < -1 && _getBalanceFactor(node->right)>0)
        return _rightLeftCaseRotate(node);
 
    return node;
}
void avl_init(AVL *avl) 
{
    avl->_root = NULL;
    avl->_size = 0u;
}
bool avl_isEmpty(AVL *avl)
{
    return avl->_root == NULL;
}
bool avl_find(AVL *avl, int value)
 {
    AVLNode *temp = _search(avl->_root, value);
    if (temp == NULL)
        return false;
 
    if (temp->data == value)
        return true;
    else
        return false;
}
void avl_insert(AVL *avl,int value)
{
    if(!avl_find(avl,value))
    {
        avl->_root=_insert_AVL(avl,avl->_root,value);
        avl->_size++;
    }
 
}
void avl_remove(AVL *avl,int value)
{
    if(avl_find(avl,value))
    {
        avl->_root=_remove_AVL(avl->_root,value);
        avl->_size--;
    }
 
}
void preorder(AVLNode *root) 
{
    if (root) 
    {
        preorder(root->left);
        printf("%d ", root->data);
        preorder(root->right);
    }
}
int afan(AVLNode *temp)
{
    if(temp==NULL) 
    {
        return 0;
    }
    else 
    {
        return 1+ afan(temp->left)+ afan(temp->right);
    }
    return -1;
}
AVLNode* findnode(AVLNode *root, int value) 
{
    while (root != NULL)
    {
        if (value < root->data)
            root = root->left;
        else if (value > root->data)
            root = root->right;
        else
            return root;
    }
    return root;
}
unsigned long long y [999999];
unsigned long long z;
void leftnode(AVLNode *root, int value) 
{
    while (root != NULL)
    {
        if (root->height == value) 
        {
            printf("%d ", root->data); 
            y[z] = root->data; 
            z++;
            root = root->left;
        }
        else root = root->left;
    }
}
void rightnode(AVLNode *root, int value) 
{
    while (root != NULL)
    {
        if (root->height == value) 
        {
            printf("%d ", root->data); 
            y[z] = root->data; 
            z++; 
            root = root->right;
        }
        else root = root->right;
    }
}
unsigned long long x;
void order1(AVLNode *root , int k)
{
    if (root == NULL) 
    {
        return;
    }
    if (k == 0)
    {
        printf("%d ", root->data);
        return ;
    }
    else
    {
        order1(root->left, k - 1) ;
        order1(root->right, k - 1) ;
    }
}
void order2(AVLNode *root , int k)
{
    if (root == NULL)
    {
        return;
    }
    if (k == 0)
    {
        x = x + root->data;
        return ;
    }
    else
    {
        order2(root->left, k - 1) ;
        order2(root->right, k - 1) ;
    }
}
int main()
{
    AVL kieri;
    avl_init(&kieri);
    unsigned long long Q, index ;
    scanf("%llu", &Q);
    for(int i=0; i<Q; i++)
    {
        unsigned long long Q1, Q2;
        scanf("%llu", &Q1);
        scanf("%llu", &Q2);
        if (Q1 == 1) 
        {
            avl_insert(&kieri, Q2); 
            index++;
        }
        else if (Q1 == 2)
        {
            order1(kieri._root, Q2-1);
            printf("\n");
        }
        else 
        {
            order2(kieri._root, Q2-1); 
            printf("%llu\n", x);
            z=0; 
            x=0;
        }
    }
}