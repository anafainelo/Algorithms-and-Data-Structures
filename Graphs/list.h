/*Ana Carolina Fainelo de Oliveira
  Trabalho de Grafos, PROF: Alneu
  Numero USP: 10284542
  ICMC - 2018                        */

#ifndef _MY_LIST	
#define _MY_LIST

#define BEGINNING 1
#define MIDDLE 2
#define END 3

#define NO_LIST -1
#define NO_NODE -2
#define TRUE 1
#define FALSE 0

#define INV_VALUE NULL

typedef void* type; 

typedef struct elements NODE;
struct elements {
	type value;
	NODE* next;
};

typedef struct info {
	NODE* begin;
	NODE* end;
	int size;
	int (*cmp)(type, type);
	void(*printValue)(type);
	void (*freeValue)(type);
}LIST;
 
/*CRIA UMA LISTA VAZIA E RETORNA SEU ENDERECO 
	PARAMETROS-> cmp: ponteiro para funcao que compara 2 values; freeValue: ponteiro pra funcao que da free em um value*/
LIST* createList(int (*cmp)(type, type), void(*printValue)(type), void (*freeValue)(type));

/*PROCURA POR UM NODE QUE TENHA COMO CONTEUDO UMA CHAVE 'key' 
	PARAMETROS-> l: lista; key: chave a ser procurada; where: indicador de onde esta a chave: inicio, meio ou fim da lista
	RETORNO-> endereco do node anterior ao node que contem a chave que procuro ou NULL caso key nao seja encontrado */
NODE* searchForNode(LIST* l, type key, int* where);

/*ADICIONA UM ELEMENTO ORDENADO NA LISTA
	PARAMETROS-> l:lista; v: valor a ser inserido;
	RETORNO-> NO_LIST: lista invalida; RETURN 0: tudo certo */
int addElem(LIST* l, type v);

/*REMOVE O NODE QUE CONTEM O VALOR 'v' 
	PARAMETROS-> l:lista; v: valor a ser removido 
	RETORNO-> NO_LIST: lista invalida; NO_NODE: valor nao encontrado, 0: valor removimo com sucesso */ 
int rmElem(LIST* l, type v);

/*FUNCAO QUE RETORNA O NUMERO DE ELEMENTOS DA LISTA
	PARAMETROS-> l: lista
	RETORNO-> tamanho da lista (0 para lista vazia), (-1 para lista inexistente)*/
int listSize(LIST* l);

/*FUNCAO QUE RETORNA O CONTEUDO DO ENESIMO (Nth) NODE DA LISTA (CASO EXISTA)
	PARAMETROS-> l:lista, n: enesima posicao que quero acessar (inicia em 0 - n-1);
	RETORNO-> NULL: posicao/lista inexistente, ou se existir, retorna o conteudo do node */
type accessPosition(LIST* l, int n);

/*FUNCAO QUE RETORNA UM VETOR COM O CONTEUDO DE TODOS OS NODES DA LISTA
	PARAMETROS-> l:lista
	RETORNOS-> NULL: l e um ponteiro nulo ou a lista esta vazia 
			   vetor com o conteudo ('value') armazenado em todos os nodes da lista*/
type* getNodeValues(LIST* l);

/*VERIFICA SE A LISTA ESTA VAZIA OU NAO
	PARAMETROS: l: lista
	RETORNO: TRUE: sim , esta vazia; FALSE: nao esta vazia*/
int isEmpty(LIST* l);

/*IMPRIME O CONTEUDO DA LISTA
	PARAMETROS-> l: lista
	RETORNO-> NO_LIST: l e um ponteiro nulo; NO_NODE; lista vazia; 0: nao houve erros*/
int printList(LIST* l);

/*LIBERA OS PONTEIROS DA LISTA
	PARAMETROS-> l:lista :*/
void freeList(LIST* l);

#endif