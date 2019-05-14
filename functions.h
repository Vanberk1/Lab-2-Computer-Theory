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
    PrintStack(stack);

    do {
        mainFile = SelectFile();
    } while(mainFile == NULL);

    char character = ' ', wrong = ' ', missing = ' ', last = ' ';
    int actualStage = 0; // posibles stages 0 or 1
    int line = 1;
    int balanced = 1;

    while((character = fgetc(mainFile)) != EOF) {
        printf("%c\n", character);
        if(character == '\n') {
            line++;
        }
        else {
            last = character;
        }

        if(actualStage == 0) {
            printf("flag\n");
            switch(character) {
                // Push cases
                case '{':
                    printf("flag2\n");
                    stack = Push(stack, '*'); // ¡¡¡¡ERROR when user choise s or S!!!!
                    printf("flag3\n");
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
                    }
                    else {
                        balanced = 0;
                    }
                    actualStage = 1;
                    break;
                case ')':
                    if(TopElement(stack) == '#') {
                        stack = Pop(stack);
                    }
                    else {
                        balanced = 0;
                    }
                    actualStage = 1;
                    break;
                case ']':
                    if(TopElement(stack) == '+') {
                        stack = Pop(stack);
                    }
                    else {
                        balanced = 0;
                    }
                    actualStage = 1;
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
                        balanced = 0;
                    }
                    break;
                case ')':
                    if(TopElement(stack) == '#') {
                        stack = Pop(stack);
                    }
                    else {
                        balanced = 0;
                    }
                    break;
                case ']':
                    if(TopElement(stack) == '+') {
                        stack = Pop(stack);
                    }
                    else {
                        balanced = 0;
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
        printf("flag4\n");
        PrintStack(stack);
        printf("\n");
        if(balanced != 1) {
            wrong = TopElement(stack);

            printf("top: %c\n", wrong);

            switch(wrong) {
                case '*':
                    missing = '}';
                    break;
                case '#':
                    missing = ')';
                    break;
                case '+':
                    missing = ']';
                    break;
                case 'z':
                    missing = last;
                default:
                    break;
            }

            printf("Tiene un error de balance de par%cntesis en la l%cnea %d. Se esperaba un: %c\n", 130, 161, line, missing);
            break;
        }
    }

    
    if(balanced) {
        printf("Los par%cntesis est%cn balanceados.\n", 130, 160);
    }

    EmptyStack(stack);
    fclose(mainFile);
}
