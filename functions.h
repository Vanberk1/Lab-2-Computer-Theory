#include "stack.h"
#include <string.h>

FILE* SelectFile() {
    char* fileName = (char*) malloc(sizeof(char));
    printf("Ingrese nombre de archivo: ");
    scanf("%s", fileName);

    FILE* file;
    file = fopen(fileName, "r");
    if(file == NULL) {
        printf("El archivo no existe. \n");
    }

    return file;
}

void ReadLines() {
    char* parentheses = (char*) malloc(sizeof(char)); // if take off explodes wtf
    FILE* mainFile;

    Stack stack = NULL;
    stack = AddNode('z'); // Initial character of the stack

    do {
        mainFile = SelectFile();
    } while(mainFile == NULL);

    char character = ' ', missing = ' ';
    int actualStage = 0;
    int line = 1;
    int correct = 0;

    while((character = fgetc(mainFile)) != EOF &&
          actualStage != 2 && actualStage != 3 && actualStage != 4 &&
          actualStage != 5 && actualStage != 6 && actualStage != 7) {
        if(character == '\n') {
            line++;
        }

        if(actualStage == 0) {
            //printf("flag\n");
            switch(character) {
                // Push cases
                case '{':
                    //printf("flag2\n");
                    stack = Push(stack, '*'); // ¡¡¡¡ERROR when user choise s or S!!!!
                    //printf("flag3\n");
                    break;
                case '(':
                    stack = Push(stack, '#');
                    break;
                case '[':
                    stack = Push(stack, '+');
                    break;

                // Pop cases
                case '}':
                    if(TopElement(stack) == '*') {
                        stack = Pop(stack);
                        actualStage = 1;
                    }
                    else {
                        actualStage = 7;
                    }
                    break;
                case ')':
                    if(TopElement(stack) == '#') {
                        stack = Pop(stack);
                        actualStage = 1;
                    }
                    else {
                        actualStage = 5;
                    }
                    break;
                case ']':
                    if(TopElement(stack) == '+') {
                        stack = Pop(stack);
                        actualStage = 1;
                    }
                    else {
                        actualStage = 6;
                    }
                    break;
                default:
                    break;
            }
        }
        else if(actualStage == 1) {
            switch(character) {
                // Pop cases
                case '}':
                    if(TopElement(stack) == '*') {
                        stack = Pop(stack);
                    }
                    else {
                        actualStage = 4;
                    }
                    break;
                case ')':
                    if(TopElement(stack) == '#') {
                        stack = Pop(stack);
                    }
                    else {
                        actualStage = 2;
                    }
                    break;
                case ']':
                    if(TopElement(stack) == '+') {
                        stack = Pop(stack);
                    }
                    else {
                        actualStage = 3;
                    }
                    break;

                // Push cases
                case '{':
                    stack = Push(stack, '*');
                    actualStage = 0;
                    break;
                case '(':
                    stack = Push(stack, '#');
                    actualStage = 0;
                    break;
                case '[':
                    stack = Push(stack, '+');
                    actualStage = 0;
                    break;
                default:
                    break;
            }
        }

    }
    //PrintStack(stack);
    //printf("\n");
    char top = TopElement(stack);

    //printf("top: %c\n", top);

    switch(actualStage) {
        // Error stages
        case 2:
            missing = '('; break;
        case 3:
            missing = '['; break;
        case 4:
            missing = '{'; break;
        case 5:
            missing = '('; break;
        case 6:
            missing = '['; break;
        case 7:
            missing = '{'; break;

        case 1:
            if(top == 'z') {
                printf("Los par%cntesis est%cn balanceados.\n", 130, 160);
                correct = 1;
            }
            else if(top == '#') { // checking the top of the list
                missing = ')';
            }
            else if(top == '*') {
                missing = '}';
            }
            else if(top == '+') {
                missing = ']';
            }
            break;
        case 0:
            if(top == '#') {
                missing = ')';
            }
            else if(top == '*') {
                missing = '}';
            }
            else if(top == '+') {
                missing = ']';
            }
            break;
        default:
            break;
    }

    if(!correct)
        printf("Tiene un error de balance de par%cntesis en la l%cnea %d. Se esperaba un: %c\n", 130, 161, line, missing);

    EmptyStack(stack);
    fclose(mainFile);
}
