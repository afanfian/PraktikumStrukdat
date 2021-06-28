// Main Kartu Yuk!
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct stackNode_t 
{
    int data;
    struct stackNode_t *next;
} 
StackNode;
typedef struct stack_t 
{
    StackNode *_top;
    unsigned _size;
} 
Stack;
void stack_init(Stack *stack);
bool stack_isEmpty(Stack *stack);
void stack_push(Stack *stack, int value);
void stack_pop(Stack *stack);
int stack_top(Stack *stack);
int stack_max(Stack *stack);
int stack_min(Stack *stack);
int stack_difference(Stack *stack);
unsigned stack_size(Stack *stack);
void stack_init(Stack *stack) 
{
    stack->_size = 0;
    stack->_top = NULL;
}
bool stack_isEmpty(Stack *stack) 
{
    return (stack->_top == NULL);
}
void stack_push(Stack *stack, int value) 
{
    StackNode *newNode = (StackNode*) malloc(sizeof(StackNode));
    if (newNode) 
    {
        stack->_size++;
        newNode->data = value;
        
        if (stack_isEmpty(stack)) newNode->next = NULL;
        else newNode->next = stack->_top;

        stack->_top = newNode;
    }
}
void stack_pop(Stack *stack) 
{
    if (!stack_isEmpty(stack)) 
    {
        StackNode *temp = stack->_top;
        stack->_top = stack->_top->next;
        free(temp);
        stack->_size--;
    }
}
int stack_top(Stack *stack) 
{
    if (!stack_isEmpty(stack)) 
        return stack->_top->data;
    return 0;
}
int stack_difference(Stack *stack) 
{
    int max1, min2, difference;
    max1=stack_max(stack);
    min2=stack_min(stack);
    if (!stack_isEmpty(stack))
    {
        difference = max1 - min2;
    }
    return difference;
    return 0;
}
int stack_max(Stack *stack) 
{
    StackNode *temp = stack->_top;
    StackNode *temp2 = stack->_top->next;
    if (!stack_isEmpty(stack))
    { 
        while(temp2 != NULL)
        {
            if(temp->data < temp2->data)
            {
                temp = temp2;
            }
            temp2 = temp2->next;
        }
    }
    free(temp2);
    return temp->data;
    return 0;
}
int stack_min(Stack *stack) 
{
    StackNode *temp = stack->_top;
    StackNode *temp2 = stack->_top->next;
    if (!stack_isEmpty(stack))
    { 
        while(temp2 != NULL)
        {
            if(temp->data > temp2->data)
            {
                temp = temp2;
            }
            temp2 = temp2->next;
        }
    }
    free(temp2);
    return temp->data;
    return 0;
}
unsigned stack_size(Stack *stack)
{
    return stack->_size;
}
int main(int argc, char const *argv[])
{
    Stack myStack;
    stack_init(&myStack);
    char sizenumber[1001];
    int i, bilangan, angka;
    scanf("%d", &bilangan);
    for (i = 0; i < bilangan; i++)
    {
        scanf("%s", sizenumber);
        if(sizenumber[0]=='p' && sizenumber[3]=='h')
        {
            scanf("%d", &angka);
            stack_push(&myStack, angka);
        }
        else if(sizenumber[0]=='t' && sizenumber[2]=='p')
        {
            printf("%d\n", stack_top(&myStack));
        }
        else if(sizenumber[0]=='p' && sizenumber[2]=='p')
        {
            stack_pop(&myStack);
        }
        else if(sizenumber[0]=='m' && sizenumber[2]=='x')
        {
             printf("%d\n", stack_max(&myStack));
        }
        else if(sizenumber[0]=='m' && sizenumber[2]=='n')
        {
             printf("%d\n", stack_min(&myStack));
        }
        else if(sizenumber[0]=='d' && sizenumber[9]=='e')
        {
            printf("%d\n", stack_difference(&myStack));
        }
    }
    return 0;
}