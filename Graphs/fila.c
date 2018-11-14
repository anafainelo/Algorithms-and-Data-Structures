/*Ana Carolina Fainelo de Oliveira
  Trabalho de Grafos, PROF: Alneu
  Numero USP: 10284542
  ICMC - 2018                        */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "fila.h"
#define N 1024


//-----------------------------------------------------------------------------
FILA* createQueue() {
    FILA* f = (FILA*) malloc(sizeof(FILA));
	f->fim = 0;
	f->inicio = 0;
	f->total = 0;
	f->numeros = (int*) malloc(N*sizeof(int));
	return f;
}

//-----------------------------------------------------------------------------
int isQueueEmpty(FILA* f) {
	if (f->total == 0) return 1;
	else return 0;
}

//-----------------------------------------------------------------------------
int isQueueFull(FILA* f) {
	if (f->total == N) return 1;
	else return 0;
}


//-----------------------------------------------------------------------------
//retorna -1 caso isFull == 1
int push(FILA* f, int num) {
	if (isQueueFull(f) == 0) {
		if (f->fim == N) f->fim == 0;
		f->numeros[f->fim] = num;
		f->fim++;
		f->total++;
		return 0;
	}
	else return -1;
}

//-----------------------------------------------------------------------------
int pop(FILA* f) {
    int num;
	if (isQueueEmpty(f) == 0) {
		if (f->inicio == N) f->inicio = 0;
		num = f->numeros[f->inicio];
		f->inicio++;
		f->total--;
		return num;
	}
	return -1;
}

