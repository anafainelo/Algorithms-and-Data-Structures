run: all
	./tree
val: all
	valgrind --leak-check=full --track-origins=yes ./tree	
all: tree.o
	gcc -o tree mainTree.c tree.o -g
tree.o: tree.c
	gcc -c tree.c -g
close:
	rm *.o
