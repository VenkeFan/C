#include <stdio.h>
#include <stdlib.h>

/*
	堆栈
*/

//////////////////////// 栈的顺序存储实现 ////////////////////////

#define ERROR	-99999
#define MAXSIZE	100
typedef struct
{
	int data[MAXSIZE];
	int top; // 下标，top == -1时栈空
} Stack;

/// 创建
Stack* create()
{
	Stack *pStack = (Stack *)malloc(sizeof(Stack));
	pStack->top = -1;

	return pStack;
}

/// 入栈
void push(int element, Stack *pStack)
{
	if (pStack->top == MAXSIZE - 1)
	{
		printf("stack is full\n");
		return;
	}

	pStack->top++;
	pStack->data[pStack->top] = element;
}

/// 出栈
int pop(Stack *pStack)
{
	if (pStack->top == -1)
	{
		printf("stack is empty\n");
		return ERROR;
	}

	int element = pStack->data[pStack->top];
	pStack->top--;

	return element;
}

/*
	一个数组实现两个堆栈，要最大地利用数组空间
*/
struct DStack
{
	int data[MAXSIZE];
	int top1;
	int top2;
};

/// 创建
DStack* dCreate()
{
	DStack *pStack = (DStack *)malloc(sizeof(DStack));
	pStack->top1 = -1;
	pStack->top2 = MAXSIZE;

	return pStack;
}

/// 入栈
void dPush(int element, DStack *pStack, int tag)
{
	if (pStack->top2 - pStack->top1 == 1)
	{
		printf("DStack is full\n");
		return;
	}

	if (tag == 1)
	{
		pStack->data[++(pStack->top1)] = element;
	}
	else
	{
		pStack->data[++(pStack->top2)] = element;
	}
}

/// 出栈
int dPop(DStack *pStack, int tag)
{
	if (tag == 1)
	{
		if (pStack->top1 == -1)
		{
			printf("stack1 is empty\n");
			return ERROR;
		}

		int element = pStack->data[(pStack->top1)--];
		return element;
	}
	else
	{
		if (pStack->top2 == MAXSIZE)
		{
			printf("stack2 is empty\n");
			return ERROR;
		}
		int element = pStack->data[(pStack->top2)--];
		return element;
	}	
}

//////////////////////// 栈的链式存储实现 ////////////////////////

struct LinkStack
{
	int data;
	LinkStack *next;
};

/// 创建
LinkStack* linkCreate()
{	
	LinkStack *topStack = (LinkStack *)malloc(sizeof(LinkStack));
	topStack->data = ERROR;
	topStack->next = NULL;

	return topStack;
}

/// 入栈
void push(int element, LinkStack *topStack)
{
	LinkStack *p = linkCreate();
	p->data = element;
	p->next = topStack->next;
	topStack->next = p;
}

/// 出栈
int pop(LinkStack *topStack)
{
	if (!topStack->next)
	{
		printf("stack is empty\n");
		return ERROR;
	}

	LinkStack *p = topStack->next;
	topStack->next = p->next;
	int element = p->data;
	free(p);

	return element;
}

int main(int argc, char const *argv[])
{
	// // 栈的顺序存储实现
	// // 创建
	// Stack *pStack = create();

	// // 入栈
	// for (int i = 1; i < 10; ++i)
	// {
	// 	push(i * 2, pStack);
	// }

	// // 出栈
	// int element = pop(pStack);
	// printf("pop: %d\n", element);

	// // 遍历
	// for (int i = 0; i <= pStack->top; ++i)
	// {
	// 	printf("%d\n", pStack->data[i]);
	// }



	// 栈的链式存储实现
	// 创建
	LinkStack *topStack = linkCreate();

	// 入栈
	for (int i = 1; i < 10; ++i)
	{
		push(i * 2, topStack);
	}

	// 出栈
	int element = pop(topStack);
	printf("pop: %d\n", element);

	// 遍历
	LinkStack *p = topStack;
	while(p)
	{
		printf("%d\n", p->data);
		p = p->next;
	}

	return 0;
}