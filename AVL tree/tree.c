#include <stdlib.h>
#include <stdio.h>
#include "tree.h"


//------------------------------------------------------------------------------------------------------------------------------
int max(int a, int b){
	return (a > b) ? a : b;
}
//------------------------------------------------------------------------------------------------------------------------------
int height(NODE* node){
	if(node == NULL) return 0;
	else return node->height;
}

//------------------------------------------------------------------------------------------------------------------------------
NODE* createNode(type x){
	NODE* node = (NODE*) malloc(sizeof(NODE));
	node->value = x;
	node->left = NULL;
	node->right = NULL;
	node->height = 1; //altura inicial;
}
//------------------------------------------------------------------------------------------------------------------------------
TREE* createTree(int (*compare)(type, type), void (*printV)(type), void (*freeV)(type)){
	TREE* t = (TREE*) malloc(sizeof(TREE));
	t->cmp  = compare;
	t->freeValue = freeV;
	t->printValue = printV;
	t->root = NULL;
	return t;
}

//------------------------------------------------------------------------------------------------------------------------------
int isEmpty(TREE* t){
	if(t->root == NULL) return 1;
	return 0;
}
//------------------------------------------------------------------------------------------------------------------------------
void print(NODE* aux, void (*printValue)(type)){
	if(aux == NULL) return;
	print(aux->left, printValue);
	printValue(aux->value);	
	printf("(%d) ", aux->height);	
	print(aux->right, printValue);
	return;
}

//------------------------------------------------------------------------------------------------------------------------------
int printTree(TREE* t){
	if(t->root == NULL) return ERROR;
	//printando em ordem crescente:
	print(t->root, t->printValue);
	printf("\n");
	return SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------
NODE* rightRotation(NODE* node){
/*
	node           L 
	 /              \
	L     ----->    node 
	 \               /
	  R             R
*/	
	NODE* L = node->left;
	NODE* R = L->right;

	L->right = node;
	node->left = R;

	//recalculando alturas;
	node->height = max(height(node->left), height(node->right))+1;
	L->height = max(height(L->left), height(L->right))+1;

	return L;
}

//------------------------------------------------------------------------------------------------------------------------------
NODE* leftRotation(NODE* node){		
/*
	node           R
	  \           /
	   R ---->   node
	  /			   \							
	 L               L
*/

	NODE* R = node->right;
	NODE* L = R->left;

	R->left = node;
	node->right = L;

	//recalculando alturas;
	node->height = max(height(node->left), height(node->right))+1;
	R->height = max(height(R->left), height(R->right))+1;

	return R;
}	

//------------------------------------------------------------------------------------------------------------------------------
NODE* balanceNode(NODE* node, int balanceFactor){
	//calculation balance factor 	
	int leftBF;
	int rightBF;

	if(node->left != NULL) leftBF  = height(node->left->left) - height(node->left->right);
	if(node->right!= NULL) rightBF = height(node->right->left) - height(node->right->right); 
	
	//left left case
	if(balanceFactor > 1 && leftBF >= 0) {
		return rightRotation(node);
	}
	//right right case
	if(balanceFactor < -1 && rightBF < 0) {
		return leftRotation(node);
	}	
	//left right case
	if(balanceFactor > 1 && leftBF <= 0){
		node->left = leftRotation(node->left);
		return rightRotation(node);
	}
	//right left case
	if(balanceFactor < -1 && rightBF > 0){
		node->right = rightRotation(node->right);
		return leftRotation(node);
	}

	//retorno o node nao modificado
	return node;
}

//------------------------------------------------------------------------------------------------------------------------------
NODE* inserting(TREE* t, NODE* node ,type v, int* check){
	int balanceFactor, L, R;
	int CMP; 

	if(node == NULL) return( createNode(v) );

	CMP = t->cmp(v, node->value); 
	//se v for menor que o valor do node atual:
	if(CMP < 0)
		node->left = inserting(t, node->left, v, check);
	//se v for maior que o valor do node atual:
	else if(CMP > 0)
		node->right = inserting(t, node->right, v, check);
	//se v for igual ao valor do node atual:
	else {
		(*check) = ERROR; //indico o erro (tentativa de inserir elemento que ja esta na arvore)
		return node;
	}

	L = height(node->left); 
	R = height(node->right);

	//atualizando a altura do node;	
	node->height = max(L, R)+1;
	//calculando  o fator de balanceamento do node:
	balanceFactor =  L - R;

	return balanceNode(node, balanceFactor);
}

//------------------------------------------------------------------------------------------------------------------------------
int insertElement(TREE* t, type v){
	int check = SUCCESS;
	t->root = inserting(t, t->root, v, &check);
	return check;
}

//------------------------------------------------------------------------------------------------------------------------------
NODE* findingReplacement(NODE* node, type* replaceValue){
	int L, R, balanceFactor;
	NODE* aux;
	if(node->right != NULL) 
		node->right = findingReplacement(node->right, replaceValue);
	else {
		(*replaceValue) = node->value;
		aux = node->left;
		free(node);
		return aux;
	}

	L = height(node->left);
	R = height(node->right);

	node->height = max(L, R)+1;
	balanceFactor = L - R;

	return balanceNode(node, balanceFactor);
}


//------------------------------------------------------------------------------------------------------------------------------
NODE* removing(TREE* t, NODE* node, type v, int* check){
	int CMP;
	int L, R, replaceValue;
	int balanceFactor;
	NODE* aux;
	type trash;
	
	if(node == NULL) {
		(*check) = ERROR;
		return node;
	}

	CMP = t->cmp(v, node->value); 
	if (CMP < 0)
		node->left = removing(t, node->left, v, check);
	else if(CMP > 0)
		node->right = removing(t, node->right, v, check);
	
	//caso eu encontre o valor que eu quero, o salvo
	else {
		//NODE COM NENHUM FILHO:
		if(node->left == NULL && node->right == NULL){
			if(t->freeValue != NULL) t->freeValue(node->value);
			free(node);
			return NULL;
		}
		//NODE COM 1 FILHO (A ESQUERDA):
		if(node->left != NULL && node->right == NULL){
			if(t->freeValue != NULL) t->freeValue(node->value);
			aux = node->left;
			free(node);	
			return aux;
		}
		//NODE COM 1 FILHO (A DIREITA):
		if(node->left == NULL && node->right != NULL){
			if(t->freeValue != NULL) t->freeValue(node->value);
			aux = node->right;
			free(node);	
			return aux;	
		}

		//NODE COM 2 FILHOS:
		if(node->left != NULL && node->right != NULL){
			trash = node->value;
			node->left = findingReplacement(node->left, &replaceValue);
			if(t->freeValue != NULL) t->freeValue(trash);
			node->value = replaceValue;
		}
	}

	L = height(node->left);
	R = height(node->right);

	node->height = max(L, R)+1;
	balanceFactor = L - R;

	return balanceNode(node, balanceFactor);

}

//------------------------------------------------------------------------------------------------------------------------------
int removeElement(TREE* t, type v){
	int check = SUCCESS;
	t->root = removing(t, t->root, v, &check);
	return check;
}	

//------------------------------------------------------------------------------------------------------------------------------
int searchElement(TREE* t, type v, type* x){
	int CMP;
	NODE* this = t->root;

	while(this != NULL && (CMP = t->cmp(v, this->value)) != 0){
		if(CMP < 0) this = this->left;
		else this = this->right;
	}

	if (this == NULL) return ERROR;
	else (*x) = this->value;
	return SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------
void givingFree(TREE* t, NODE* node){
	if(node == NULL) return;
	givingFree(t, node->left);
	givingFree(t, node->right);

	if(t->freeValue != NULL) t->freeValue(node->value);
	free(node);
	return;
}	

//------------------------------------------------------------------------------------------------------------------------------
void freeTree(TREE* t){
	givingFree(t, t->root);
	free(t);
}