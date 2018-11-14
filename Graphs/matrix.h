/*Ana Carolina Fainelo de Oliveira
  Trabalho de Grafos, PROF: Alneu
  Numero USP: 10284542
  ICMC - 2018                        */

#ifndef _MY_MATRIX
#define _MY_MATRIX

#include <limits.h>

//valores de retorno:
#define EMPTY_POSITION         INT_MAX
#define LINE_OUT_OF_BOUNDS     1
#define COLUMN_OUT_OF_BOUNDS   2
#define ALL_FINE               0
#define NON_EXISTING_MATRIX    NULL
#define NON_EXISTING_MATRIX_V  1

#define INVALID_VALUE          INT_MIN


typedef int valueType;


typedef struct myMatrix{
	valueType** matrix;  //propria matriz (INT_MAX na linha 'x' coluna 'y' indica que nao ha relacao)
	int size;            //indica o tamanho da martriz: (size X size)
	char matrixType;     //1: matriz nao transposta, 0: matriz transposta
	void (*printValue)(valueType);    //ponteiro para funcao para comparar 2 valores na matriz
 	void (*freeValue)(valueType);     //ponteiro para funcao para dar free em value caso ele seja um ponteiro
 	int (*cmp)(valueType, valueType); //ponteiro para funcao para comparar o conteudo de duas posicoes na matriz
}MATRIX;


/*FUNCAO QUE INICIALIZA A MATRIZ
	PARAMETROS-> n: matriz n por n
				 matrixType: matriz transposta ou nao
				 printValue: ponteiro pra funcao que imprime o tipo 'valueType'
				 freeValue: ponteiro para funcao que da free no tipo 'valueType'
				 cmp: ponteiro para fincao que compara o tipo 'valueType'
	RETORNO-> m: ponteiro para matriz */
MATRIX* createMatrix(int n, char matrixType, void (*printValue)(valueType), void (*freeValue)(valueType), int(cmp)(valueType, valueType) );

/*FUNCAO QUE INSERE UM VALOR 'valueType' NA MATRIZ
	PARAMETROS-> m: ponteiro para matriz
				 line: linha a inserir o valor
				 column: coluna a inserir o valor
				 value: valor a ser inserido na matriz
	RETORNOS-> ALL_FINE: nao houve erros
			   LINE OUT OF BOUND: line maior que os limites da matriz
			   COLUMN_OUT_OF_BOUNDS: coluna fora dos limites da matriz
			   NON_EXISTING_MATRIX: matriz base e um ponteiro nulo  */
int insertInMatrix(MATRIX* m, int line, int column, valueType value);

/*FUNCAO QUE REMOVE UM VALOR 'valueType' NA MATRIZ
	'idem insertMatrix()' */
int removeFromMatrix(MATRIX* m, int line, int column);

/*RETORNA O VALOR 'valueType' NA LINHA 'line' E COLUNA 'column'
	PARAMETROS-> m: ponteiro pra matriz
				 line: linha do valor procurado
				 column: coluna do valor procurado
	RETORNOS-> INVALID_VALUE: m e um ponteiro nulo
	           m->matrix[line][column]*/
valueType getMatrixValue(MATRIX* m, int line, int column);

/*GERA A MATRIZ TRANSPOSTA DE m->matriz COM OS MESMOS ATRIBUTOS DESTA
	PARAMETROS-> m: ponteiro para matriz base
	RETORNOS-> NON_EXISTING_MATRIX: matriz base e um ponteiro nulo
			   transposed: ponteiro para a matriz transposta */
MATRIX* generateTransposedMatrix(MATRIX* m);

/*RETORNA O MENOR VALOR DA MATRIZ
	PARAMETROS-> m: ponteiro para matriz
	RETORNO-> NON_EXISTING_MATRIX: matriz base e um ponteiro nulo
			  smallest_coordinates: coordenadas do menor valor da matriz*/
int* matrixSmallestValue(MATRIX* m);

/*IMPRIME A MATRIZ
	PARAMETROS-> ponteiro para matriz
	RETORNOS-> NON_EXISTING_MATRIX: matriz e um ponteiro nulo
			   ALL_FINE: nao houve erros*/
int printMatrix(MATRIX* m);

/*IMPRIME O ID DAS COLUNAS QUE POSSUEM ALGUMA RELACAO COM A LINHA 'line', DIFERENTE DE EMPTY_POSITION
	PARAMETROS-> m: ponteiro para matriz
				 line: linha a analisar
	RETORNOS-> NON_EXISTING_MATRIX_V: m e um ponteiro nulo
			   ALL_FONE: nao houve erros */
int printRelatedIndexes(MATRIX* m, int line);

/*IMPRIME A MATRIZ TRANSPOSTA DE m
	'idem printMatrix()'*/
int printTansposedMatrix(MATRIX* m);

/*RETORNA UMA COPIA DA MATRIZ
	PARAMETROS-> m: ponteiro para matriz  */
MATRIX* copyMatrix(MATRIX* m);

/*DA FREE NA MATRIZ E SEU CONTEUDO
	PARAMETROS-> m: ponteiro pra matriz
	RETORNOS-> NON_EXISTING_MATRIX_V: m e um ponteiro nulo
			   ALL_FINE: nao houve erros*/
int freeMatrix(MATRIX* m);

#endif
