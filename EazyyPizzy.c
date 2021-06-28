//Eazyy Pizzy
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

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
typedef struct pqueueNode_t 
{
    int data;
    struct pqueueNode_t *next;
} PQueueNode;
typedef struct pqueue_t 
{
    PQueueNode *_top;
    unsigned _size;
} PriorityQueue;
void pqueue_init(PriorityQueue *pqueue);
bool pqueue_isEmpty(PriorityQueue *pqueue);
void pqueue_push(PriorityQueue *pqueue, int value);
void pqueue_pop(PriorityQueue *pqueue);
int  pqueue_top(PriorityQueue *pqueue);
void slist_init(SinglyList *list) 
{
    list->_head = NULL;
    list->_size = 0;
}
bool slist_isEmpty(SinglyList *list) 
{
    return (list->_head == NULL);
}
void slist_pushBack(SinglyList *list, int value)
{
    SListNode *newNode = (SListNode*) malloc(sizeof(SListNode));
    if (newNode) 
    {
        list->_size++;
        newNode->data = value;
        newNode->next = NULL;
        
        if (slist_isEmpty(list)) 
            list->_head = newNode;
        else 
        {
            SListNode *temp = list->_head;
            while (temp->next != NULL) 
            temp = temp->next;
            temp->next = newNode;
        }
    }
}
void slist_popFront(SinglyList *list)
{
    if (!slist_isEmpty(list)) 
    {
        SListNode *temp = list->_head;
        list->_head = list->_head->next;
        free(temp);
        list->_size--;
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
void pqueue_init(PriorityQueue *pqueue)
{
    pqueue->_top = NULL;
    pqueue->_size = 0;
}

bool pqueue_isEmpty(PriorityQueue *pqueue) 
{
    return (pqueue->_top == NULL);
}
void pqueue_pushgenap(PriorityQueue *pqueue, int value)
{
    PQueueNode *temp = pqueue->_top;
    PQueueNode *newNode = \
    (PQueueNode*) malloc (sizeof(PQueueNode));
    newNode->data = value;
    newNode->next = NULL;
    if (pqueue_isEmpty(pqueue)) 
    {
        pqueue->_top = newNode;
        return;
    }

    if (value > pqueue->_top->data) 
    {
        newNode->next = pqueue->_top;
        pqueue->_top = newNode;
    }
    else 
    {
        while ( temp->next != NULL && 
        temp->next->data > value)
        temp = temp->next;
        newNode->next = temp->next;
        temp->next = newNode;
    }
}
void pqueue_pushganjil(PriorityQueue *pqueue, int value)
{
    PQueueNode *temp = pqueue->_top;
    PQueueNode *newNode = \
    (PQueueNode*) malloc (sizeof(PQueueNode));
    newNode->data = value;
    newNode->next = NULL;
    if (pqueue_isEmpty(pqueue)) 
    {
        pqueue->_top = newNode;
        return;
    }
    if (value < pqueue->_top->data) 
    {
        newNode->next = pqueue->_top;
        pqueue->_top = newNode;
    }
    else 
    {
        while ( temp->next != NULL && 
        temp->next->data < value)
        temp = temp->next;
        newNode->next = temp->next;
        temp->next = newNode;
    }
}
void pqueue_pop(PriorityQueue *pqueue)
{
    if (!pqueue_isEmpty(pqueue)) 
    {
        PQueueNode *temp = pqueue->_top;
        pqueue->_top = pqueue->_top->next;
        free(temp);
    }
}
int pqueue_top(PriorityQueue *pqueue) 
{
    if (!pqueue_isEmpty(pqueue))
        return pqueue->_top->data;
    else return 0;
}
int main(int argc, char const *argv[])
{
    PriorityQueue myPque_genap;
    PriorityQueue myPque_ganjil;
    SinglyList myList;
    pqueue_init(&myPque_ganjil);
    pqueue_init(&myPque_genap);
    slist_init(&myList);
    int tmp;
    while(1)
    {
        scanf("%d", &tmp);
        if(tmp == 0)break;
        if(tmp % 2 == 0)
        {
            pqueue_pushgenap(&myPque_genap, tmp);
        }
        else if(tmp%2!=0) pqueue_pushganjil(&myPque_ganjil,tmp);
    }
    while(!pqueue_isEmpty(&myPque_genap))
    {
        slist_pushBack(&myList, pqueue_top(&myPque_genap));
        pqueue_pop(&myPque_genap);
    }
    while(!pqueue_isEmpty(&myPque_ganjil))
    {
        slist_pushBack(&myList, pqueue_top(&myPque_ganjil));
        pqueue_pop(&myPque_ganjil);
    }
    while(!slist_isEmpty(&myList))
    {
        printf("%d\n", slist_front(&myList));
        slist_popFront(&myList);
    }
    return 0;
}