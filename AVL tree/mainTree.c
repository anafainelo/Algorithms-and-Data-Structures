#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "tree.h"

//------------------------------------------------------------------------------------------------------------------------------
void printValue(type v){
	int x = (int)v;
	printf("%d", x);
	return;
}

//------------------------------------------------------------------------------------------------------------------------------
int cmp(type a, type b){
	return a - b;
}

//------------------------------------------------------------------------------------------------------------------------------

int main(){
	int aux;
	int op, e, check;
	TREE* t = createTree(cmp, printValue, NULL);
	while(1){
		system("clear");
		printf("1 - insert element\n");
		printf("2 - remove element\n");
		printf("3 - search element\n");
		printf("4 - print tree\n");
		printf("5 - eixt\n");
		printf("OPTION: ");
		scanf("%d", &op);
		getchar(); //pega o enter

		switch(op){
			case 1: printf("element: ");
					scanf("%d", &e);
					check = insertElement(t, e);
					break;
			case 2: printf("element: ");
					scanf("%d", &e);
					check = removeElement(t, e);
					break;
			case 3: printf("element: ");
					scanf("%d", &e);
					check = searchElement(t, e, &aux);
					if (check == ERROR) printf("ELEMENT NOT FOUND... ");
					else printf("ELEMENT %d FOUND", aux);
					break;
			case 4: check = printTree(t);
					break;
			case 5: goto end;
		}
		getchar(); //pega o enter
		if(check == ERROR) printf("ERROR");
		getchar();
	}
	end:
	freeTree(t);
	return 0;
}