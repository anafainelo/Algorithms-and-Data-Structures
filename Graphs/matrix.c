/*Ana Carolina Fainelo de Oliveira
  Trabalho de Grafos, PROF: Alneu
  Numero USP: 10284542
  ICMC - 2018                        */

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

//SECAO DA MATRIZ_______________________________________________________________________________________________________

/* Matriz: matrix[linha][coluna]

    0 1 2 3  < colunas 
  0 . . . .
  1 . . . .
  2 . . . .
  3 . . . . 

  ^
linhas 

*/

//-----------------------------------------------------------------------------------------------------------------
MATRIX* createMatrix(int n, char matrixType, void (*printValue)(valueType), void (*freeValue)(valueType), int(cmp)(valueType, valueType) ){
	int i, j;
	MATRIX* m;

	m = (MATRIX*) malloc(sizeof(MATRIX));

	m->size = n;
	m->matrixType = matrixType;
	m->printValue = printValue;
	m->freeValue = freeValue;
	m->cmp = cmp;


	//INICIALIZANDO A PROPRIA MATRIZ:
	m->matrix = (valueType**) malloc(n*sizeof(valueType*));
	for(i = 0; i < n; i++){
		m->matrix[i] = (valueType*) calloc(n, sizeof(valueType));
		for(j = 0; j < n; j++){
			//inicialmente, nao ha relacao ente linhas e colunas
			(m->matrix)[i][j] = EMPTY_POSITION; 
		}
	}

	return m;
}

//-----------------------------------------------------------------------------------------------------------------
int setMatrix(MATRIX* m, int line, int column, valueType value){
	int i = line;
	int j = column;

	if(m == NULL) return NON_EXISTING_MATRIX_V; //retorna que a matriz nao existe

	if(i >= m->size || i < 0) return LINE_OUT_OF_BOUNDS;   //retorna erro nas definicoes da linha
	if(j >= m->size || j < 0) return COLUMN_OUT_OF_BOUNDS; //retorna erro nas definicoes da coluna  

	/*A direcao da ligacao deve ser entendida como tendo origem no node na coluna
	(line) e indo para o node na linha (coluna) quando a matriz nao for transposta*/
	(m->matrix)[i][j] = value;
	
	//se a matriz for transposta, configuro o 'inverso' tbm:
	if(m->matrixType == 0) 
		(m->matrix)[j][i] = value;

	return ALL_FINE;
}

//-----------------------------------------------------------------------------------------------------------------
int insertInMatrix(MATRIX* m, int line, int column, valueType value){
	int r;
	r = setMatrix(m, line, column, value);
	return r;
}

//-----------------------------------------------------------------------------------------------------------------
int removeFromMatrix(MATRIX* m, int line, int column){
	int r;
	r = setMatrix(m, line, column, EMPTY_POSITION);
	return r;
}

//-----------------------------------------------------------------------------------------------------------------
valueType getMatrixValue(MATRIX* m, int line, int column){
	if(m == NULL) return INVALID_VALUE; 
	return (m->matrix)[line][column];
}

//-----------------------------------------------------------------------------------------------------------------
MATRIX* generateTransposedMatrix(MATRIX* m){
	int i, j;
	MATRIX* transposed;

	if(m == NULL) return NON_EXISTING_MATRIX; //retorno nulo caso a matriz base nao exista

	transposed = (MATRIX*) malloc(sizeof(MATRIX));

	transposed->size = m->size;
	transposed->matrixType = m->matrixType;
	transposed->printValue = m->printValue;
	transposed->freeValue = m->freeValue;
	transposed->cmp = m->cmp;

	//INICIALIZANDO MATRIZ TRANSPOSTA:
	transposed->matrix = (valueType**) malloc(m->size*sizeof(valueType*));
	for(i = 0; i < m->size; i++){
		transposed->matrix[i] = (valueType*) calloc(m->size, sizeof(valueType));
		for(j = 0; j < m->size; j++){
			//invertendo linha e coluna de m para passar para transposed
			(transposed->matrix)[i][j] = (transposed->matrix)[j][i]; 
		}
	}

	return transposed;
}
//-----------------------------------------------------------------------------------------------------------------
int* matrixSmallestValue(MATRIX* m){
	int i, j;
	int* smallest_coordinates;
	valueType smallest;

	if(m == NULL) return NON_EXISTING_MATRIX;

	smallest_coordinates = (int*) malloc(2*sizeof(int));
	
	smallest_coordinates[0] = smallest_coordinates[1] = 0;
	smallest = m->matrix[0][0];

	for(i = 0; i < m->size; i++){
		for(j = 0; j < m->size; j++){
			//se achar um valor menor, atualizo smallest
			if( m->cmp( (m->matrix)[i][j], smallest) < 0) {
				smallest = (m->matrix)[i][j];
				smallest_coordinates[0] = i;
				smallest_coordinates[1] = j;
			}
		}
	} 
	return smallest_coordinates;
}

//-----------------------------------------------------------------------------------------------------------------
int printMatrix(MATRIX* m){
	int i, j;

	if(m == NULL) return NON_EXISTING_MATRIX_V; //retorno caso matriz nao exista

	for(i = 0; i < m->size; i++){
		for(j = 0; j <  m->size; j++){
			if( (m->matrix)[i][j] != EMPTY_POSITION){ 
				if (m->printValue != NULL) m->printValue((m->matrix)[i][j]);
				printf(" ");
			}
			else printf(". ");
		}
		printf("\n");
	}

	return ALL_FINE;
}

//-----------------------------------------------------------------------------------------------------------------
int printTansposedMatrix(MATRIX* m){
 	int i, j;

	if(m == NULL) return NON_EXISTING_MATRIX_V; //retorno caso matriz nao exista

	for(i = 0; i < m->size; i++){
		for(j = 0; j <  m->size; j++){
			if( (m->matrix)[j][i] != EMPTY_POSITION){ 
				if (m->printValue != NULL) m->printValue((m->matrix)[j][i]);
				printf(" ");
			}
			else printf(". ");
		}
		printf("\n");
	}

	return ALL_FINE;
}

//-----------------------------------------------------------------------------------------------------------------
int printRelatedIndexes(MATRIX* m, int line){
	int j;

	if(m == NULL) return NON_EXISTING_MATRIX_V;

	//printo os id's das colunas que tem alguma relacao com a linha 'line'
	for(j = 0; j < m->size; j++){
		if( (m->matrix)[line][j] != EMPTY_POSITION){
			printf("%d ", j);
		}
	}
	printf("\n");

	return ALL_FINE;
}

//-----------------------------------------------------------------------------------------------------------------
MATRIX* copyMatrix(MATRIX* m){
	int i, j;
	MATRIX* m2;
	
	m2 = (MATRIX*) malloc(sizeof(MATRIX));

	//COPIANDO INFORMACOS PARA NOVA MATRIZ
	m2->size = m->size;
	m2->matrixType = m->matrixType;
	m2->printValue = m->printValue;
	m2->freeValue = m->freeValue;
	m2->cmp = m->cmp;
	
	//INICIALIZANDO A PROPRIA MATRIZ COM OS VALORES NA MATRIZ QUE QUERO COPIAR:
	m2->matrix = (valueType**) malloc(m2->size*sizeof(valueType*));
	for(i = 0; i < m2->size; i++){
		m2->matrix[i] = (valueType*) calloc(m2->size, sizeof(valueType));
		for(j = 0; j < m2->size; j++){
			(m2->matrix)[i][j] = (m->matrix)[i][j]; 
		}
	}
	return m2;
}

//-----------------------------------------------------------------------------------------------------------------
int freeMatrix(MATRIX* m){
	int i, j; 

	if(m == NULL) return NON_EXISTING_MATRIX_V;

	for(i = 0; i < m->size; i++){
		for(j = 0; j < m->size; j++) {
			if(m->freeValue != NULL) m->freeValue((m->matrix)[i][j]);
		}
		free(m->matrix[i]);
	}
	free(m);

	return ALL_FINE;
}

