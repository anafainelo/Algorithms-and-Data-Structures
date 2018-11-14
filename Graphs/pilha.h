#define sizeofstack 1000
typedef int dataType;

typedef struct mystack{
	dataType* stack;
	int top;
	int size;
}STACK;

STACK* createStack();
dataType stackPop(STACK* p);
dataType stackPush(STACK* p, dataType elem);
dataType stackPull(STACK* p);
int  getStackSize(STACK* p);
void freeStack(STACK* p);
