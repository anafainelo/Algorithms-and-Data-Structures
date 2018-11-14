/*Ana Carolina Fainelo de Oliveira
  Trabalho de Grafos, PROF: Alneu
  Numero USP: 10284542
  ICMC - 2018                        */

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

int isEmpty(LIST* l) {
	if (l->begin == NULL) return TRUE;
	return FALSE;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
LIST* createList(int (*cmp)(type, type), void (*printValue)(type), void (*freeValue)(type)) {
	LIST* l = (LIST*) malloc(sizeof(LIST));
	l->end = NULL;
	l->begin = NULL; 
	l->size= 0;
	l->cmp = cmp;
	l->printValue = printValue;
	l->freeValue = freeValue;
	return l;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
NODE* searchForNode(LIST* l, type key, int* where){

	NODE* previous = l->begin; //node anterior ao que quero remover
	NODE* thisNode; //node que quero remover

	//se a lista nao esxistir, retorno NULL:
	if(l == NULL) return NULL;

	//se a chave esta no primeiro node:
	if(l->cmp(key, l->begin->value) == 0) (*where) = BEGINNING;
	
	else {
		//caso contrario, percorro a lista procurando a chave...
		while(previous->next != NULL && l->cmp(previous->next->value, key) != 0)
			previous = previous->next;
		thisNode = previous->next;	

		//se a chave nao existir:
		if(thisNode == NULL) return NULL;

		//se a chave estiver no ultimo node:
		if(thisNode == l->end) (*where) = END;
		//se a chave existir e nao estiver nem no comeco nem no final da lista:
		else (*where) = MIDDLE; 
	}	

	return previous;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
int addElem(LIST* l, type v) {
	NODE* thisNode, *previous;
	NODE* aux;
	int r; //guarda o retorno de l->cmp
	
	//se a lista for invalida
	if (l == NULL) return NO_LIST;

	//caso a lista esteja vazia:
	if (isEmpty(l) == TRUE) {
		l->end = l->begin = (NODE*) malloc(sizeof(NODE));
		l->begin->value = v;
		l->end->next = NULL;
		l->size++;
		return 0;
	}

	//caso nao esteja vazia:
	thisNode = (NODE*) malloc(sizeof(NODE));
	thisNode->value = v;
	aux = previous = l->begin;

	//percorro a lista ate achar a posicao correta para o node
	while(  aux!= NULL && (r = l->cmp(v, aux->value)) > 0){
		previous = aux;
		aux = aux->next;
	}

	//SE A INSERCAO FOR NO COMECO DA LISTA
	if(aux == l->begin){
		//se eu encontrar um elemento repetido, o excluo para adicinar o novo node:
		if(r == 0){
			l->size--;
			thisNode->next = aux->next;
			if(l->freeValue != NULL) l->freeValue(aux->value);
			free(l->begin);
		}
		//caso contrario, so adiciono o novo node na lista
		else thisNode->next = aux;
		
		l->begin = thisNode;
	}	

	//SE A INSERCAO FOR NO FINAL DA LISTA
	else if(aux == NULL){
		l->end->next = thisNode;
		thisNode->next = NULL;
		l->end = thisNode;
	}

	//SE A INSERCAO FOR NO MEIO DA LISTA
	else{
		previous->next = thisNode;

		//se eu encontrar um elemento repetido, o excluo para adicinar o novo node:
		if(r == 0){
			l->size--;
			thisNode->next = aux->next;
			if(l->freeValue != NULL) l->freeValue(aux->value);
			free(aux);
		}
		else{
			thisNode->next = aux;
		}
	}

	//incremento a variavel que indica a quantidade de elementos da lista
	l->size++;

	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
int rmElem(LIST* l, type v) {
	int where; //indica onde esta 'v' na lista: comeco, meio ou final
	NODE* previous;// node anterior ao que tem o valor que eu quero
	NODE* thisNode;
 
	//nao posso remover elementos de uma lista invalida ou vazia:
	if(l == NULL || isEmpty(l) == TRUE) return NO_LIST;

	//caso a lista exista, procuro o 'value' desejado
	previous = searchForNode(l, v, &where);

	//se previous for NULL, o elemento procurado nao existe:
	if(previous == NULL) return NO_NODE;

	//se o valor existir, vejo se ele esta no primeiro node... 
	if (where == BEGINNING){
		//...se sim, o removo
		thisNode = l->begin;
		l->begin = l->begin->next;
	}

	else if(where == END) {
		thisNode = l->end;
		l->end = previous;
		l->end->next = NULL;
	}
	else if(where == MIDDLE) {
		thisNode = previous->next;
		previous->next = thisNode->next; 
	}

	//decremento a variavel que indica a quantidade de elementos da lista
	l->size--;

	//dou free no conteudo do node: A fazer

	//dou free no node
	free(thisNode);
	thisNode = NULL;
	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
int listSize(LIST* l){
	if(l == NULL) return -1;
	return l->size;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
type accessPosition(LIST* l, int n){
	int i, size = listSize(l);
	NODE* node;

	if(size == 0 || size == -1 || size-1 < n) return INV_VALUE;

	node = l->begin;
	for(i = 0; i < n; i++){
		node = node->next;
  	}
	return node->value;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
type* getNodeValues(LIST* l){
	int i;
	NODE* aux;
	type* value;

	if(l == NULL) return NULL;
	if(isEmpty(l) == TRUE) return NULL;

	value = (type*) malloc(l->size*sizeof(type));
	aux = l->begin;
	for(i = 0; i < l->size; i++){
		value[i] = aux->value;
		aux = aux->next;
	}
	return value;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
int printList(LIST* l){
	int i;
	NODE* aux;

	if(l == NULL) return NO_LIST;
	else if(l->begin == NULL) return NO_NODE;

	aux = l->begin;
	for(i = 0; i < l->size; i++){
		if(l->printValue != NULL) l->printValue(aux->value);
		printf(" ");
		aux = aux->next;
	}

	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void freeList(LIST* l) {
	NODE* aux, * aux2;
	//Se existe lista e ela e nao vazia:
	if(l != NULL && isEmpty(l) == FALSE) {
		aux = l->begin;
		while (aux != NULL) {
			aux2 = aux->next;
			if(l->freeValue != NULL) l->freeValue(aux->value); 
			free(aux);
			aux = aux2;
		}
	}
	free(l);
}