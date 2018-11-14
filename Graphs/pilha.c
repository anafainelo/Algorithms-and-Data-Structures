#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

STACK* createStack(){
    STACK* p = (STACK*) malloc(sizeof(STACK));
    p->stack = (dataType*) malloc(sizeofstack * sizeof(dataType));
    p->top = -1;
    p->size = 0;
    return p;
}

int isStackEmpty(STACK* p) {
    if (p->top == -1)
        return 1;
    return 0;
}
int isStackFull(STACK* p) {
    if (p->top == sizeofstack -1)
        return 1;
    return 0;
}
//adiciona elementos a pilha
dataType stackPush(STACK* p, dataType elem) {
    if (isStackFull(p) == 0) {
        p->top++;
        p->size++;
        p->stack[p->top] = elem;
        return 0;
    }
    else return -1;
}

//retorna o ultimo elemento da pilha
dataType stackPull(STACK* p) {
    if (isStackEmpty(p) == 0)
        return p->stack[p->top];
    else return -1;
}
//remove elementos da pilha
dataType stackPop(STACK* p) {
    if (isStackEmpty(p) == 0) {
        p->top--;
        p->size--;
        return p->stack[p->top + 1];
    }
    else return -1;
}

int  getStackSize(STACK* p){
	if(p == NULL || p->stack == NULL) return -1;
	return p->size;
}

void freeStack (STACK* p) {
	free(p->stack);
}




