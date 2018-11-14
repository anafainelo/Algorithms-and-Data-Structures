# Ana Carolina Fainelo de Oliveira
# Trabalho de Grafos, PROF: Alneu
# Numero USP: 10284542
# ICMC - 2018      

run: all
	./main
val: all
	valgrind --leak-check=full --track-origins=yes ./main
all: graph.o list.o matrix.o fila.o pilha.o main.c 
	gcc -o main graph.o list.o matrix.o fila.o pilha.o main.c -g
graph.o: graph.c
	gcc -c graph.c -g
list.o: list.c
	gcc -c list.c -g
matrix.o: matrix.c
	gcc -c matrix.c -g
fila.o:
	gcc -c fila.c -g
pilha.o:
	gcc -c pilha.c -g
zip: graph.h graph.c list.c  matrix.c list.h matrix.h fila.c fila.h pilha.c pilha.h main.c Makefile
	zip graph graph.h graph.c list.c  matrix.c list.h matrix.h fila.c fila.h pilha.c pilha.h main.c Makefile -j
clean:
	rm *.o *.zip
