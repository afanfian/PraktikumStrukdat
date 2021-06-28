//Gerbang Pol
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct snode_t 
{
    int data;
    struct snode_t *next;
} SListNode;
typedef struct slist_t 
{
    unsigned _size;
    SListNode *_head;
} SinglyList;
void slist_init(SinglyList *list) 
{
    list -> _head = NULL;
    list -> _size = 0;
}
bool slist_isEmpty(SinglyList *list) 
{
    return (list -> _head == NULL);
}
void slist_pushBack(SinglyList *list, int value)
{   
    SListNode *newNode = (SListNode*) malloc(sizeof(SListNode));
    if (newNode) 
    {
        list -> _size++;
        newNode -> data = value;
        newNode -> next = NULL;
        if (slist_isEmpty(list)) 
        {
            list -> _head = newNode;
        }
        else 
        {
            SListNode *temp = list->_head;
            while (temp -> next != NULL) 
            temp = temp -> next;
            temp -> next = newNode;
        }
    }
}
void slist_popFront(SinglyList *list)
{
    if (!slist_isEmpty(list)) 
    {
        SListNode *temp = list -> _head;
        list -> _head = list -> _head -> next;
        free(temp);
        list -> _size--;
    }
}
int slist_front(SinglyList *list)
{
    if (!slist_isEmpty(list)) 
    {
        return list->_head->data;
    }
    return 0;
}
int main() 
{
    SinglyList myList;
    slist_init(&myList);
    int del = slist_front(&myList);
    int a, b, c=0, volka;
    int sum = 0;
    scanf("%d", &a);
    scanf("%d", &b);
    for(int a = 1; a <= b; a++)
    {
        scanf("%d", &volka);
        if (a <= b)
        {
            slist_pushBack(&myList, volka);
            sum = sum + volka;
            c = sum;
        }
        else if (a > b) 
        {
            slist_pushBack(&myList, volka);
            sum = sum + volka;
            slist_popFront(&myList);
            sum = sum - del;
            if (sum <= c) 
            {
               c = sum;
            }
        }      
    }
    printf("%d\n", c);
    return 0;
}