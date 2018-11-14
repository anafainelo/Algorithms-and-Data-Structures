/*Ana Carolina Fainelo de Oliveira
  Trabalho de Grafos, PROF: Alneu
  Numero USP: 10284542
  ICMC - 2018                        */

#ifndef _FILA
#define _FILA

typedef struct listinhaaa {
	int inicio, fim, total;
	int* numeros;
}FILA;
//cria a fila e retorna ponteiro:
FILA* createQueue();

//adiciona elemento na fila e retorna 0 ou retorna -1 caso a fila esteja vazia:
int push(FILA* f, int num);

//remove da pilha e retorna o que foi retirado ou -1 caso a fila esteja vazia:
int pop(FILA* f);

//retorna 1 se a fila estiver vazia e 0 caso contrario:
int isQueueEmpty(FILA* f);

//retorna 1 caso a fila estiver cheia e 0 caso contrario:
int isQueueFull (FILA* f);

#endif
