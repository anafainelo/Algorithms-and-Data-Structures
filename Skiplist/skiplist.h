#ifndef _SKIPLIST_H

#define _SKIPLIST_H
#define FAIL 1
#define SUCCESS 0
#define LIMIT_HEIGHT 10
#define INVALID_VALUE NULL

typedef void* type;

typedef struct node NODE;
struct node {
	type value;
	NODE* down;
	NODE* right;	
};

typedef struct skiplist{
	NODE* topLeft;
	int height; //altura
	NODE* previous; //usado na busca, previous Node;
}SKIPLIST;

//cria a skiplist e retorna seu ponteiro
SKIPLIST* createSkiplist();
//RETORNOS: SUCCESS: elemento encontrado, FAIL: elemento nao exite 
int searchElement(SKIPLIST* sl, type x, type* val, int (*cmp)(void*,void*));
//RETORNOS: SUCCESS: elemento inserido, FAIL: elemento ja exite
int insertElement(SKIPLIST* sl, type x, int (*cmp)(type, type));
//RETORNOS: SUCCESS: elemento encontrado e removido, FAIL: elemento nao exite
int removeElement(SKIPLIST* sl, type x, int (*cmp)(void*,void*), void (*freeContent)(type));
//libera a lista
void freeSkiplist(SKIPLIST* sl, void (*freeContent)(type));
//RETORNO: o node com o primeiro elemento maior que x
NODE* firstNodeOfItsGroup(SKIPLIST* sl, type x, int (*cmp)(void*,void*));

#endif