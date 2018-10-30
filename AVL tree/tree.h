#define ERROR 1
#define SUCCESS 0

typedef int type;


typedef struct node NODE;
struct node{
	type value;
	NODE* left;
	NODE* right;
	int height;
};

typedef struct myTree{
	NODE* root;
	int (*cmp)(type, type);
	void (*freeValue)(type);
	void (*printValue)(type);
}TREE;

TREE* createTree(int (*compare)(type, type), void (*printValue)(type), void (*freeValue)(type));
int insertElement(TREE* t, type v);
int removeElement(TREE* t, type v);
int searchElement(TREE* t, type v, type* x);
int printTree(TREE* t);
void freeTree(TREE* t);