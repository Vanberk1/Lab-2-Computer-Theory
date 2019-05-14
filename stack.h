#include <stdio.h>
#include <stdlib.h>

/*
    Stack node data struct;
*/
typedef struct node {
    char data;
    struct node* next;
} Node;

typedef Node* Stack; // Stack is a type value that has a group of nodes

/*
    AddNode function recives an character and creates a node
    with its data as x parameter and the next pointer to null.
    Returns the complete node with Stack type value.
*/

Stack AddNode(char x)
{
    Stack aux;
    aux = (Node*)malloc(sizeof(Node));

    aux->data = x;
    aux->next = NULL;

    return aux;
}
// e.g. Stack stack = AddNode() --> This line of code inialize a stack with a node that has a 0 in its data.

/*
    Push function recives a Stack and and character, then creates a node
    and puts it at the top of the Stack.
    Returns the same Stack modified.
*/
Stack Push(Stack stack, char x) {
    Stack nNode;
    nNode = AddNode(x);
    
    nNode->next = stack;
    stack = nNode;
    nNode = NULL;

    return stack;
}
/* e.g. Stack stack = NULL;
        stack = Push(stack, 'x') --> These lines of code add a node to the top of the stack with a x character in its data.
*/

/*
    Pop function recives a Stack and deletes the element on the top of Stack.
*/
Stack Pop(Stack stack) {
    Stack nNode;

    if(stack != NULL) {
        nNode = stack;
        stack = stack->next;
        nNode->next = NULL;
        free(nNode);
    }

    return stack;
}
/* e.g. Stack stack = NULL;
        stack = Pop(stack) --> These lines of code remove the element on the top of the stack.
*/

/*
    TopElement function returns the top element on the stack, if the stack is null return the empty character \0.
*/

char TopElement(Stack stack) {
    char elem = '\0';
    if(stack != NULL) {
        elem = stack->data;
    }

    return elem;
}

/*
    StackLength
*/
int StackLength(Stack stack) {
    int count = 0;
    Stack aux = stack;

    while(aux != NULL) {
        count++;
        aux = aux->next;
    }

    return count;
}
// e.g. int StackLength = StackLength(Stack) --> This line of code stores in a variable the number of nodes that the Stack has.

/*
    ValueAt function recives a Stack and an integer what is it a position in the Stack.
    Returns the value of the data field in the correspondent node to the index parameter.
*/
char ValueAt(Stack stack, int index) {
    Stack aux = stack;
    int i = 0;

    while(i < index) {
        aux = aux->next;
        i++;
    }

    return aux->data;
}
// e.g. int number = ValueAt(Stack, 2) --> This line of code stores in a variable de data of the node at the third position of the Stack.

/*
    PrintStack function print the complete stack.
*/
void PrintStack(Stack stack) {
    Stack aux = stack;

    while(aux != NULL) {
        printf("%c ", aux->data);
        aux = aux->next;
    }

    aux = NULL;
}

void EmptyStack(Stack stack) {
    Stack aux;
   
    while (stack != NULL) {
        aux = stack;
        stack = stack->next;
        aux->next = NULL;
        free(aux);
    }
}





