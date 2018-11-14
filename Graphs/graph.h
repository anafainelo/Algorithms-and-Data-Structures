/*Ana Carolina Fainelo de Oliveira
  Trabalho de Grafos, PROF: Alneu
  Numero USP: 10284542
  ICMC - 2018                        */

#ifndef _GRAPH
#define _GRAPH

#include "list.h"
#include "matrix.h"
#include "fila.h"
#include "pilha.h"

#define DIRECTIONAL 1
#define NON_DIRECTIONAL 0
#define IS_MATRIX 0
#define IS_LIST 1

//STRUCTS PARA CONTEUDO GUARDADO NA LISTA-----------------------------------------
typedef struct informations{ //contem as informacoes que estarao nos nodos da lista
	int id; //id do vertice
	int weight;
}INFO;

//STRUCT PRINCIPAL----------------------------------------------------------------
typedef struct graph{
	char graphType; //0 = grafo nao direcional, 1 = grafo direcional
	char repType;   //tipo de representacao do grafo: 0 = matriz, 1 = lista
	int n_nodes;    //numero de vertices do grafo
	int n_edges;    //numero de arestas do grafo
	void* myGraph; //sera um ponteiro MATRIX* ou LIST* dependendo da escolha do usuario
}GRAPH;

//FUNCOES__________________________________________________________________________

GRAPH* initializeGraph(char gt, char rt, int nn, int ne);
void printGraph(GRAPH* g);
void insertInGraph(GRAPH* g, int node1, int node2, int weight);
void removeFromGraph(GRAPH* g, int node1, int node2);
void printAdjacentNodes(GRAPH* g, int id);
int* lessWeightEdge(GRAPH* g);
void printLessWeightEdge(GRAPH* g);
void printTansposed(GRAPH* g);
void breadthFirstSearch(GRAPH* g, int begin, int end);
void depthFirstSearch(GRAPH* g, int begin, int end);
int* topologicalSorting(GRAPH* g);
void minimumSpanningTree(GRAPH* g, int root);
void minimumPath(GRAPH* g, int begin, int end);
void freeGraph(GRAPH* g);

#endif
