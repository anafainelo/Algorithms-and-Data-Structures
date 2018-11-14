/*Ana Carolina Fainelo de Oliveira
  Trabalho de Grafos, PROF: Alneu
  Numero USP: 10284542to
  ICMC - 2018                        */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

//-----------------------------------------------------------------------------------------------------------------
GRAPH* readingInputs(){
	GRAPH* g;
	int n_nodes, n_edges;
	int node1, node2, weight, i;
	char command[5];

	//leio a quantidade de vertices e arestas:
	scanf(" %d %d", &n_nodes, &n_edges);

	//inicializo o grafo direcional que sera representado com matrix:
	g = initializeGraph(DIRECTIONAL, IS_MATRIX, n_nodes, n_edges);

	for(i = 0; i < g->n_edges; i++){
		scanf(" %d %d %d", &node1, &node2, &weight);   //lendo vertices incidentes
		insertInGraph(g, node1, node2, weight); //adicionando na lista
	}

	//LENDO OS COMANDOS ATÉ EOF
	while (scanf(" %d %d", &node1, &node2) != EOF){
		minimumPath(g, node1, node2);
	}

	return g;
}

//-----------------------------------------------------------------------------------------------------------------
int main(void){
	GRAPH* g = readingInputs();
	freeGraph(g);
	return 0;
}
