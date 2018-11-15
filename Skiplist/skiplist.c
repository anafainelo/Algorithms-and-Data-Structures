/*Ana Carolina Fainelo de Oliveira
  Algoritimos e Estrutura de Dados 
  Dicionario com Skiplist
  ICMC-USP 2017                     */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "skiplist.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------
NODE* createNode(type x){
	NODE* newNode = (NODE*) malloc(sizeof(NODE));
	newNode->value = x;
	newNode->right = NULL;
	newNode->down = NULL;
	return newNode;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------
void createNewLevel(SKIPLIST* sl){
	sl->height++;
	NODE* newLeft = createNode(INVALID_VALUE);
	newLeft->down = sl->topLeft;
	sl->topLeft = newLeft;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------
SKIPLIST* createSkiplist(){
	int i;
	SKIPLIST* sl = (SKIPLIST*) malloc(sizeof(SKIPLIST));
	sl->height = 0;
	sl->topLeft = NULL;
	for(i = 0; i < LIMIT_HEIGHT; i++) 
		createNewLevel(sl);

	return sl;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------
NODE* firstNodeOfItsGroup(SKIPLIST* sl, type x, int (*cmp)(void*,void*)){
	int level, CMP = 1;
	NODE* currentNode = sl->topLeft;
	sl->previous == NULL;

	for(level = sl->height; currentNode->down != NULL; level--){
		//procuro nessa linha:
		while(currentNode->right != NULL && (CMP = cmp(x, currentNode->right->value) ) < 0)
	 		currentNode = currentNode->right;
		currentNode = currentNode->down;
	}
	while(currentNode->right != NULL && (CMP = cmp(x, currentNode->right->value) ) < 0)
			currentNode = currentNode->right;
	return currentNode->right; 
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------
int searchElement(SKIPLIST* sl, type x, type* val, int (*cmp)(void*,void*)){
	int level, CMP = 1;
	NODE* currentNode = sl->topLeft;
	sl->previous == NULL;

	for(level = sl->height; currentNode != NULL; level--){
		//procuro nessa linha:
		while(currentNode->right != NULL && (CMP = cmp(x, currentNode->right->value) ) < 0)
	 		currentNode = currentNode->right;

		//se eu achei o node que quero:
		if(CMP == 0){
			(*val) = currentNode->right->value;
			sl->previous = currentNode;
			return SUCCESS;
		}
		currentNode = currentNode->down;
	}
	return FAIL;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------
int howHight(SKIPLIST* sl){
	int nodeHeight = 0;
	int coin = 1;

	//enquanto cair cara na moeda(1), meu node tera mais um nivel
	while(coin == 1 && nodeHeight != LIMIT_HEIGHT){
		nodeHeight++;
		coin = rand()%2;
	}
	return nodeHeight;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------
void inserting(NODE* leftNode, NODE* upNode, NODE* newNode){
	NODE* aux;
	//inserindo novo node na horizontal e vertical:
	aux = leftNode->right;
	leftNode->right = newNode;
	if (upNode != NULL) upNode->down = newNode;
	newNode->right = aux;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------
int insertElement(SKIPLIST* sl, type x, int (*cmp)(type, type)){
	int level, nodeHeight, CMP = 1;
	type aux;
	NODE* currentNode = sl->topLeft;
	NODE* upNode = NULL;
	NODE* newNode = NULL;

	//verifico se o elemento ja existe na lista, se sim, retorno erro:
	if(searchElement(sl, x, &aux, cmp) == SUCCESS) return FAIL;

	//defino quantos niveis ele ocupara(se ocupar mais niveis do que os que ja existem a funcao aumenta a altura da skiplist):
	nodeHeight = howHight(sl);

	//loop separado ate chegar na linha em que iniciarei a insercao
	for(level = sl->height; level > nodeHeight; level--){
		//vou pra direita ate achar onde 'x' se encaixa nessa linha:
		while(currentNode->right != NULL && (CMP = cmp(x, currentNode->right->value) ) < 0)
			currentNode = currentNode->right;
		currentNode = currentNode->down;
	}

	//a partir desse nivel, o elemento comeca a ser inserido na skiplist
	for( ; currentNode != NULL; level--){
		//vou pra direita ate  achar onde 'x' se encaixa nessa linha:
		while(currentNode->right != NULL && (CMP = cmp(x, currentNode->right->value) ) < 0)
			currentNode = currentNode->right;
		//insiro o elemento nessa linha
		newNode = createNode(x);
		inserting(currentNode, upNode, newNode);
		upNode = newNode;	 		
		currentNode = currentNode->down;
	}
	return SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------
void removing(SKIPLIST* sl){
	NODE* aux;
	//redefinindo os ponteiros da skiplist:
	aux = sl->previous->right;
	sl->previous->right = sl->previous->right->right;
	free(aux);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------
int removeElement(SKIPLIST* sl, type x, int (*cmp)(void*,void*), void (*freeContent)(type)) {
	int CMP = 1;
	type aux = NULL; //na verdade aux esta aqui para a funcao funcionar, pois e util em outros *.c quando o node guarda um ponteiro;
	
	//verifico se o elemento que quero remover ja exite:
	if(searchElement(sl, x, &aux, cmp) == FAIL) return FAIL;
	//se nao existir comeco a remocao:
	else{
		aux = sl->previous->right->value;

		removing(sl);
		sl->previous = sl->previous->down;
		while (sl->previous != NULL){
			while(sl->previous->right != NULL && (CMP = cmp(x, sl->previous->right->value) ) < 0)
				sl->previous = sl->previous->right;
			if(CMP == 0)
				removing(sl);
			sl->previous = sl->previous->down;
		}
		freeContent(aux);
	}
	return SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------
void freeSkiplist(SKIPLIST* sl, void (*freeContent)(type)){
	NODE* aux = sl->topLeft, *aux2 = sl->topLeft;
	NODE*down;
	
	if (sl == NULL || sl->topLeft == NULL) return;

	//liberandoNodes:
	while(aux->down != NULL){
		down = aux->down;
		while(aux != NULL){
			aux2 = aux->right; // love you
			free(aux);
			aux = aux2;
		}
		aux = down;
	}
	//liberando ultima linha e conteudos:
	aux2 = aux->right;
	free(aux);
	aux = aux2;
	while(aux != NULL){
		aux2 = aux->right; // love you
		free(aux->value);
		free(aux);
		aux = aux2;
	}
	free(sl);
}
