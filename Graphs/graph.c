/*Ana Carolina Fainelo de Oliveira
  Trabalho de Grafos, PROF: Alneu
  Numero USP: 10284542
  ICMC - 2018                        */

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//defines uteis para busca em largura
#define WHITE 0
#define GREY  1
#define BLACK 2

#define TRUE  1
#define FALSE 0

//*********************************************************************************************************************
//SECAO DA MATRIX
//*********************************************************************************************************************


void printInt(int value){
	printf("%d", value);
}

//-----------------------------------------------------------------------------------------------------------------
int compareInt(int value1, int value2){
	return value1 - value2;
}

//-----------------------------------------------------------------------------------------------------------------
//FUNCAO QUE RETORNA um vetor com o caminho de 'root' ATE 'end' AO CONTRARIO <<----
int* matrixBreadthFirstSearch(MATRIX* m, int root){
    /* SIGNIFICADO DAS CORES DOS NODES:
        WHITE: node do grafo ainda nao foi visitado
        GREY:  node visitado
        BLACK: node visitado e todos os seus adjacentes tambem
    */
	int i, currentNode;
	char color[m->size]; 		//vetor de cores para cada vertice
	int* previous;         		//vetor com os vertices anteriores de cada vertice
	FILA* queue = createQueue(); //fila para auxiliar no percorrimento do grafo

    previous = (int*) malloc(m->size*sizeof(int));

    //inicializando os vetores necessarios
    for(i = 0; i < m->size; i++){
        //defino a cor inicial de todos os nodes do grafo como brancos:
        color[i] = WHITE;
        //defino o id do node anterior de todos os nodes do grafo como -1(valor invalido)
        previous[i] = -1;
    }

    //adiciono a raiz  na fila (
	push(queue, root);
	color[root] = GREY;
	previous[root] = -2; //-2 marca a raiz no vetor

    //enquanto a fila nao estiver vazia, percorro o grafo
	while(isQueueEmpty(queue) == 0){
		//retiro o primeiro elemento da pilha
		currentNode = pop(queue);
		for(i = 0; i < m->size; i++){
		    //vejo apenas as posicoes com alguma conexao:

		    if( (m->matrix)[currentNode][i] != EMPTY_POSITION) {
                //caso este node ainda nao foi visitado:
                if(color[i] == WHITE) {
                    push(queue, i); //coloco na fila os filhos do node atual que ainda nao foram visitados
                    previous[i] = currentNode;  //marco que currentNode é o antecessor deste filho:
                    color[i] = GREY; //marco a cor desse filho como cinza
                }
		    }
        }
		color[currentNode] = BLACK; //marco a cor do node como preta (ja visitei ele e seus filhos)
	}

	return previous;
}

//--------------------------------------------------------------------------------------------------------------------
void matrixDFSrecursion(MATRIX* m, int currentNode, int size, char** color, int** previous, STACK* s){
    int i;

    //ao chegar em um node, o marco como cinza
    (*color)[currentNode] = GREY;

    for(i = 0; i < size; i++){
        //se o node filho nao doi percorrido:
        if((m->matrix)[currentNode][i] != EMPTY_POSITION && (*color)[i] == WHITE){
            (*previous)[i] = currentNode;
            matrixDFSrecursion(m, i, size, color, previous, s);
        }
    }
    //depois de percorrer todos os seus node, defino a cor do node atual como preta
    (*color)[currentNode] = BLACK;

    //adiciono node na pilha (util apenas para ordenacao topologica)
    if(s != NULL){
		stackPush(s, currentNode);
	}

}

//--------------------------------------------------------------------------------------------------------------------
//retorna o vetor de antecessores
int* matrixDepthFirstSearch(MATRIX* m, int root, STACK* s){
    int  i;
	char* color;   //vetor de cores para cada vertice
	int* previous; //vetor com os vertices anteriores de cada vertice

    color = (char*) malloc(m->size*sizeof(char));
    previous = (int*) malloc(m->size*sizeof(int));

    //inicializando os vetores necessarios
    for(i = 0; i < m->size; i++){
        //defino a cor inicial de todos os nodes do grafo como brancos:
        color[i] = WHITE;
        //defino o id do node anterior de todos os nodes do grafo como -1(valor invalido)
        previous[i] = -1;
    }
    //a raiz permanecera com previous sendo -2
    previous[root] = -2;
	for(i=0;i<m->size;i++){
		if(color[i] == WHITE)
			matrixDFSrecursion(m, i, m->size, &color, &previous, s);
    }
    free(color);
    return previous;

}

//--------------------------------------------------------------------------------------------------------------------
int* matrixMST(MATRIX* m, int root){
	int* previous = (int*) malloc(m->size*sizeof(int));  //vetor de antecessores
	char visited[m->size]; // (boolean) para saber se todas as conexoes de um node ja foram visitadas
	char v[m->size];
	int i, j, min, minIndex, nVisited = 0;
	int prev = root;


	//inicializando vetores:
	for(i = 0; i < m->size; i++){
		previous[i] = -1;    // Todos os nodes inicialmete possuem node anterior como invalido (-1)
		visited[i] = 0; //INicialmente nenhum node foi visitado
        v[i] = -1;
	}

	//se ainda existe nodes para serem analisados:
	while(nVisited != m->size-1){
        visited[prev] = 1;
        v[nVisited] = prev;
		nVisited++;
        min = INT_MAX;

		for(i = 0; i < m->size; i++){
            if(visited[i] == 1){
                for(j = 0; j < m->size; j++){
                    if((m->matrix)[i][j] < min && visited[j] == 0){
                        prev = i;
                        min = (m->matrix)[i][j];
                        minIndex = j;
                    }
                }//end for
            }
		}//end for

		previous[minIndex] = prev;
		if( prev < minIndex) printf("(%d,%d) ", prev, minIndex);
		else  printf("(%d,%d) ", minIndex, prev);
		prev = minIndex;
	}

	return previous;
}
//--------------------------------------------------------------------------------------------------------------------
void mdVerify(MATRIX* m, int currentNode, int* distance, int*previous, char* visited){
    int dist, i;

    //percorrendo todas as conexoes do node atual
    for(i = 0; i < m->size; i++){
        if(m->matrix[currentNode][i] != INT_MAX && visited[i] != TRUE){ //se houver conexao
            dist =  distance[currentNode] + m->matrix[currentNode][i];
            if(distance[i] == INT_MAX || dist < distance[i]) {
                distance[i] = dist;
                previous[i] = currentNode;
            }
        }
    }
    visited[currentNode] = TRUE;
}

//--------------------------------------------------------------------------------------------------------------------
int* matrixDijkstra(MATRIX* m, int root){
    int* distance = (int*) malloc((m->size)*sizeof(int));
    char* visited = (char*) malloc((m->size)*sizeof(char));
    int* previous = (int*) malloc((m->size)*sizeof(int));
    int min, i;
    int currentNode = root;
    char found = TRUE;

    //inicializando vetores:
    for(i = 0; i < m->size; i++){
        previous[i] = -1;
        distance[i] = INT_MAX;
        visited[i] = FALSE;
    }
    distance[root] = 0; //root distance from root
    previous[root] = -2;


    while(found == TRUE){
        mdVerify(m, currentNode, distance, previous, visited);

        min = INT_MAX;
        found = FALSE;

        for(i = 0; i < m->size; i++){
            if(distance[i] < min && visited[i] == FALSE){
                found = TRUE;
                min = distance[i];
                currentNode = i;
            }
        }
    }

    free(distance);
    free(visited);
    return previous;
}

//*********************************************************************************************************************
//SECAO DA LISTA (muitas destas funcoes estao em graph.c por serem especificas de grafos e nao do TAD lista
//*********************************************************************************************************************


//funcao que compara o conteudo de info, ou seja, verifica na lista se eu achei o vertice que queria:
int compareInfo(type a, type b){
	INFO*c = (INFO*)a;
	INFO*d = (INFO*)b;

	//conteudos iguais, retorno 0
	//a < b retorno negativo
	//a > b retorno positivo
	return ((c->id) - (d->id));
}

//-----------------------------------------------------------------------------------------------------------------
void freeInfo(type value){
	INFO* i;

	if(value == NULL) return;

	i = (INFO*)value;
	free(i);
}

//-----------------------------------------------------------------------------------------------------------------
void printInfo(type value){
	INFO* i = (INFO*)value;

	if(i == NULL) return;
	printf("%d(%d)", i->id, i->weight);
}

//-----------------------------------------------------------------------------------------------------------------
void insertInList(LIST** l, int node1, int node2, int weight, char graphType){
	//crio aqui o conteudo que sera armazenado no node da lista:
	INFO* info = (INFO*) malloc(sizeof(INFO));
	INFO* info2;

	info->weight = weight;
	info->id = node2;

	addElem(l[node1] , (void*)info);

	//se o grafo NAO for direcional (e a conexao nao for do node com ele proprio) , configuro o 'inverso' tbm:
	if(graphType == NON_DIRECTIONAL && node1 != node2){
		info2 = (INFO*) malloc(sizeof(INFO));
		info2->weight = weight;
		info2->id = node1;

		addElem(l[node2], (void*)info2);
	}
}

//-----------------------------------------------------------------------------------------------------------------
void removeFromList(LIST** l, int node1, int node2, char graphType){
	/*crio uma struct com o valor de id que quero remover para list.c conseguir comparar o valor dos id's dos
	vertices atraves de compare */
	INFO* info = (INFO*) malloc(sizeof(INFO));

	info->id = node2;
	rmElem(l[node1], (void*)info);

	//se o grafo NAO for direcional, configuro o 'inverso' tbm:
	if(graphType == NON_DIRECTIONAL){
		info->id = node1;
		rmElem(l[node2], (void*)info);
	}
}
//-----------------------------------------------------------------------------------------------------------------
LIST** createVectorOfLists(int size){
	int i;
	LIST** l;

	l = (LIST**) malloc(size*sizeof(LIST*));
	for(i = 0; i < size; i++){
		l[i] = createList(compareInfo, printInfo, freeInfo);
	}
	return l;
}

//-----------------------------------------------------------------------------------------------------------------
void printTransposedList(GRAPH* g){ //ESTA FUNCAO NAO ESTA NO TAD DE LISTA POR SER ESPECIFICA
	int i, j, size;                 //PARA ESTE PROGRAMA DE GRAFOS
	INFO* info;

	LIST** l = createVectorOfLists(g->n_nodes);

	//crio uma lista transposta para depois imprimi-la
	for(i = 0; i < g->n_nodes; i++){
		size = listSize(((LIST**)g->myGraph)[i]);
		for(j = 0; j < size; j++){
			//vou acessando cada posicao da lista
			info = accessPosition((((LIST**)g->myGraph)[i]), j);
			insertInList(l, info->id, i, info->weight, g->graphType);
		}
	}

	//imprimindo:
	for(i = 0; i < g->n_nodes; i++) {
		printf("%d. ", i);
		printList(l[i]);
		printf("\n");
	}

	for(i = 0; i < g->n_nodes; i++) freeList(l[i]);
	free(l);
}



//*********************************************************************************************************************
//FUNCOES GERAIS
//*********************************************************************************************************************

 GRAPH* initializeGraph(char gt, char rt, int nn, int ne){
 	LIST** l;
 	GRAPH* g = (GRAPH*) malloc(sizeof(GRAPH));
 	g->graphType = gt;
	g->repType = rt;
	g->n_nodes = nn;
	g->n_edges = ne;

	if(rt == IS_MATRIX) g->myGraph = (void*) createMatrix(nn, gt, printInt, NULL, compareInt);

	else if(rt == IS_LIST) {
		/* crio um vetor de listas, sendo que o indice do vetor corresponde ao id do vertice 'DONO' da lista,
		ou seja, cada vertice tera uma lista que representa suas ligacoes e o peso destas*/

		g->myGraph = (void*) createVectorOfLists(g->n_nodes);
	}

 	return g;
 }

//-----------------------------------------------------------------------------------------------------------------
void printGraph(GRAPH* g){
 	int i;

 	//caso seja matriz:
 	if(g->repType == IS_MATRIX) printMatrix((MATRIX*)g->myGraph);

 	//caso seja lista:
	else if(g->repType == IS_LIST) {
		for(i = 0; i < g->n_nodes; i++) {
			printf("%d. ", i);
			printList( ((LIST**)g->myGraph)[i]);
			printf("\n");
		}
	}
}
//-----------------------------------------------------------------------------------------------------------------
void insertInGraph(GRAPH* g, int node1, int node2, int weight){
	//caso seja matriz:
	if(g->repType == IS_MATRIX) insertInMatrix((MATRIX*)g->myGraph, node1, node2, weight);

	//caso seja lista:
	else if(g->repType == IS_LIST) insertInList((LIST**)g->myGraph, node1, node2, weight, g->graphType);
}

//-----------------------------------------------------------------------------------------------------------------
void removeFromGraph(GRAPH* g, int node1, int node2){
	//caso seja matriz:
	if(g->repType == IS_MATRIX) removeFromMatrix((MATRIX*)g->myGraph, node1, node2);

	//caso seja lista:
	else if(g->repType == IS_LIST) removeFromList((LIST**)g->myGraph, node1, node2, g->graphType);
}

//-----------------------------------------------------------------------------------------------------------------
void printAdjacentNodes(GRAPH* g, int id){
	int i, size;
	INFO** info;

	//Se o grafo estiver em lista (funcao nao esta no TAD por ser muito especifica para este programa)
	if(g->repType == IS_LIST){
		//chamo a funcao que verifica o tamanho da lista:
		size = listSize( ((LIST**)g->myGraph)[id] );
		//chamo a funcao que retorna os valores na lista em um vetor de size posicoes:
		info = (INFO**)getNodeValues(((LIST**)g->myGraph)[id]);

		//imprimo na tela os id's das arestas adjacentes:
		for(i = 0; i < size; i++){
			printf("%d ", (info[i])->id);
		}
		printf("\n");
	}

	//se o grafo estiver em  matriz
	else printRelatedIndexes((MATRIX*)g->myGraph, id);

	return;
}
//-----------------------------------------------------------------------------------------------------------------
int* lessWeightEdge(GRAPH* g){
	//RETORNO AS COORDENADAS DA ARESTA DE MENOR PESO <---
	int i, j, size;
	int* smallest_c;
	int lwe = INT_MAX; //less weight edge value
	INFO* info;

	//Se o grafo estiver em lista (funcao nao esta no TAD de lista pois e muito especifica para esse programa)
	if(g->repType == IS_LIST){
		smallest_c = (int*) malloc(2*sizeof(int));

		for(i = 0; i < g->n_nodes; i++){
			size = listSize(((LIST**)g->myGraph)[i]);
			for(j = 0; j < size; j++){
				//vou acessando cada posicao da lista
				info = accessPosition((((LIST**)g->myGraph)[i]), j);
				if(info->weight < lwe){
					//atualizo o menor valor 'lwe' e as coordenadas deste na matriz:
					lwe = info->weight;
					smallest_c[0] = i;
					smallest_c[1] = info->id;
				}
			}
		}
		return smallest_c;
	}

	//se o grafo estiver em lista
	else {
		return matrixSmallestValue((MATRIX*)g->myGraph);
 	}

}
//-----------------------------------------------------------------------------------------------------------------
void printLessWeightEdge(GRAPH* g){
	int* coordinate;

	if(g == NULL) return;

	coordinate = lessWeightEdge(g);
	printf("%d %d\n", coordinate[0], coordinate[1]);
	free(coordinate);
}
//-----------------------------------------------------------------------------------------------------------------
void printTansposed(GRAPH* g){
	if(g->repType == IS_MATRIX)printTansposedMatrix((MATRIX*)g->myGraph);
	else printTransposedList(g);
}

//-----------------------------------------------------------------------------------------------------------------
/*acha um caminho do node 'a' para o node 'b' ('a' --> 'b') com base em um vetor de antecessores (que quando foi
    gerado considerou 'a' como root) <<---- OBS: nao mudar as funcoes que determinam 'previous'*/
int* findPath(int* previous, int a, int b, int size, int* pathSize){
	int i, currentNode;
	int* path;

	path = (int*) malloc(size*sizeof(int));
	currentNode = b;
	i = 0;

	//vou voltando de 'b' ate 'a'
    while(previous[currentNode] != -1 && previous[currentNode] != -2){
        path[i] = currentNode;
        currentNode = previous[currentNode];
        i++;
    }
    path[i] = a;

	//se eu nao cheguei na raiz:
	if(previous[currentNode] == -1){
        free(path);
        return NULL;
    }

    (*pathSize) = i+1;
    return path;
}

//BUSCA EM LARGURA (AMPLITUDE)-------------------------------------------------------------------------------------
void breadthFirstSearch(GRAPH* g, int begin, int end){
     int* previous;
     int* path;
     int pathSize, i;

	 if(g->repType == IS_MATRIX) { //Por enquanto, funciona apenas com matriz

        previous = matrixBreadthFirstSearch((MATRIX*)g->myGraph, begin);
        path = findPath(previous, begin, end, ((MATRIX*)g->myGraph)->size, &pathSize );

 //       if(path != NULL){
 //           for(i = pathSize -1; i >= 0; i--){
 //               printf("%d ", path[i]);
 //           }
 //           free(path);
 //       }
 //       printf("\n");

        free(previous);
    }
}

//BUSCA EM PROFUNDIADAE ------------------------------------------------------------------------------------------
void depthFirstSearch(GRAPH* g, int begin, int end){
     int* previous;
     int* path;
     int pathSize, i;

	 if(g->repType == IS_MATRIX) { //Por enquanto, funciona apenas com matriz

        previous = matrixDepthFirstSearch((MATRIX*)g->myGraph, begin, NULL);
        path = findPath(previous, begin, end, ((MATRIX*)g->myGraph)->size, &pathSize );

//        if(path != NULL){
//           for(i = pathSize -1; i >= 0; i--){
//                printf("%d ", path[i]);
//            }
//            free(path);
//        }
//       printf("\n");

         free(previous);
    }

}

//-----------------------------------------------------------------------------------------------------------------
int* topologicalSorting(GRAPH* g){
	STACK* s = createStack();
	int* sorting;
	int i, size;

	//Por enquanto, funciona apenas com matriz em DFS
	if(g->repType == IS_MATRIX) {
		matrixDepthFirstSearch((MATRIX*)g->myGraph, 0, s);

		size = getStackSize(s);
		sorting = (int*) malloc(size*sizeof(int));
		for(i = 0; i < size; i++){
			sorting[i] = stackPop(s);
			printf("%d ", sorting[i]);
		}
		printf("\n");
	}

	freeStack(s);
	return sorting;
}
//-----------------------------------------------------------------------------------------------------------------
void minimumSpanningTree(GRAPH* g, int root){

	//Por enquanto, funciona apenas com matriz em DFS
	if(g->repType == IS_MATRIX) {
        matrixMST((MATRIX*)g->myGraph, root);
	}

	//dar free em previous na main
}
//-----------------------------------------------------------------------------------------------------------------
void minimumPath(GRAPH* g, int begin, int end){
    int* previous;
    int* path = NULL;
    int i, pathSize;

    if(g->repType == IS_MATRIX){
        previous = matrixDijkstra((MATRIX*)g->myGraph, begin);
        path = findPath(previous, begin, end, ((MATRIX*)g->myGraph)->size, &pathSize );

        if(path != NULL){
           for(i = pathSize -1; i >= 0; i--){
                printf("%d ", path[i]);
            }
            free(path);
        }
        printf("\n");

        free(previous);
    }
}

//-----------------------------------------------------------------------------------------------------------------
void freeGraph(GRAPH* g){
	int i;

	//caso seja matriz:
	if(g->repType == IS_MATRIX) freeMatrix((MATRIX*)g->myGraph);

	//caso seja lista:
	else {
		for(i = 0; i < g->n_nodes; i++) freeList(((LIST**)g->myGraph)[i]);
		free((LIST**)g->myGraph);
	}
	free(g);
}

