#include <stdio.h>
#include <stdlib.h>

/*
	队列
*/

//////////////////////// 队列的顺序存储实现 ////////////////////////

/////循环队列
#define ERROR	-99999
#define MAXSIZE	10
typedef struct
{
	int data[MAXSIZE];
	int front;
	int rear;
} Queue;

/// 创建
Queue* create()
{
	Queue *pQueue = (Queue *)malloc(sizeof(Queue));
	pQueue->front = pQueue->rear = 0;
	return pQueue;
}

/// 入队
void addQ(int element, Queue *pQueue)
{
	if ((pQueue->rear + 1) % MAXSIZE == pQueue->front)
	{
		printf("queue is full\n");
		return;
	}

	pQueue->rear = (pQueue->rear + 1) % MAXSIZE;
	pQueue->data[pQueue->rear] = element;
}

/// 出队
int deleteQ(Queue *pQueue)
{
	if (pQueue->front == pQueue->rear)
	{
		printf("queue is empty\n");
		return ERROR;
	}

	int element = pQueue->data[(pQueue->front + 1) % MAXSIZE];
	pQueue->front = (pQueue->front + 1) % MAXSIZE;

	return element;
}

//////////////////////// 队列的链式存储实现 ////////////////////////

typedef struct Node
{
	int data;
	Node *next;
} QNode;

struct LinkQueue
{
	QNode *front;
	QNode *rear;
};

/// 创建
LinkQueue* linkCreate()
{
	LinkQueue *linkQueue = (LinkQueue *)malloc(sizeof(LinkQueue));
	QNode *front = (QNode *)malloc(sizeof(QNode));
	front->data = ERROR;
	front->next = NULL;

	QNode *rear = (QNode *)malloc(sizeof(QNode));
	rear->data = ERROR;
	rear->next = NULL;

	linkQueue->front = front;
	linkQueue->rear = rear;

	return linkQueue;
}

/// 入队
void addQ(int element, LinkQueue *linkQueue)
{
	QNode *node = (QNode *)malloc(sizeof(QNode));
	node->data = element;
	node->next = NULL;

	// 队列空
	if (!linkQueue->front->next)
	{
		linkQueue->front->next = linkQueue->rear->next = node;
	}
	else
	{
		QNode *rearNode = linkQueue->rear->next;
		rearNode->next = node;
		linkQueue->rear->next = node;
	}
}

/// 出队
int deleteQ(LinkQueue *linkQueue)
{
	if (!linkQueue->front->next)
	{
		printf("queue is empty\n");
		return ERROR;
	}

	QNode *node = linkQueue->front->next;
	linkQueue->front->next = node->next;
	int element = node->data;
	free(node);

	return element;
}


int main(int argc, char const *argv[])
{
	// // 队列的顺序存储实现
	// // 创建
	// Queue *pQueue = create();

	// // 入队
	// for (int i = 1; i <= 10; ++i)
	// {
	// 	addQ(i, pQueue);
	// }

	// // 出队
	// int element = deleteQ(pQueue);
	// printf("delete: %d\n", element);

	// // 遍历
	// for (int i = pQueue->front + 1; i <= pQueue->rear; ++i)
	// {
	// 	printf("%d\n", pQueue->data[i]);
	// }



	// 队列的链式存储实现
	// 创建
	LinkQueue *linkQueue = linkCreate();

	// 入队
	for (int i = 1; i <= 10; ++i)
	{
		addQ(i, linkQueue);
	}

	// 出队
	int element = deleteQ(linkQueue);
	printf("delete: %d\n", element);

	// 遍历
	LinkQueue *p = linkQueue;
	QNode *node = p->front;
	while(node)
	{
		printf("%d\n", node->data);
		node = node->next;
	}

	return 0;
}