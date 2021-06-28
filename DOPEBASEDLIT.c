//DOPEBASEDLIT
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct stackNode_t 
{
    char ch;
    struct stackNode_t *next;
} StackNode;
typedef struct stack_t 
{
    StackNode *_top;
    unsigned _size;
} Stack;
void stack_init(Stack *stack);
bool stack_isEmpty(Stack *stack);
void stack_push(Stack *stack, char value);
void stack_pop(Stack *stack);
char stack_top(Stack *stack);
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
void stack_push(Stack *stack, char value) 
{
    StackNode *newNode = (StackNode*) malloc(sizeof(StackNode));
    if (newNode)
    {
        stack->_size++;
        newNode->ch = value;
        
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
char stack_top(Stack *stack) 
{
    if (!stack_isEmpty(stack)) 
    return stack->_top->ch;
    return 0;
}
unsigned stack_size(Stack *stack) 
{
    return stack->_size;
}
void cekpasangan(Stack *stack, char str[])
{
    Stack *temp = stack;
    char tmp;
    int tanda=0, len = strlen(str);
     for(int i=0;i<len;i++)
     {
        if(str[i]=='T' || str[i] == '1' || str[i]=='2')
        {
            stack_push(temp, str[i]);   
            continue;
        }
        if(stack_isEmpty(temp))  
        {
            printf("No way!\n");
            return;
        }
        if(str[i]=='C')
        {
            tmp = stack_top(temp);
            stack_pop(temp);
            if(tmp == '1' || tmp == '2')
            {
                printf("No way!\n");
                return;
            }
            else 
            {
                tanda=1;
            }
        }
        else if(str[i] == '9')
        {
            tmp = stack_top(temp);
            stack_pop(temp);
            if(tmp =='T' || tmp == '2')
            {
                printf("No way!\n");
                return;
            }
            else 
            {
                tanda=1;
            }
        }
        else if(str[i] == '0')
        {
            tmp = stack_top(temp);
            stack_pop(temp);
            if(tmp=='1' || tmp == 'T')
            {
                 printf("No way!\n");
                 return;
            }
            else 
            {
                 tanda=1;
            }
        }
    }
    if(tanda)
    {
        printf("DOPEBASEDLIT\n");
    }
}
int main(int argc, char const *argv[])
{   
    Stack myStack;
    char str[10010];
    scanf("%s", str);
    cekpasangan(&myStack,str);
}