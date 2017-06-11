#include <stdio.h>
#include <stdlib.h>

/*
	二叉树
*/

/// 二叉树
typedef struct TreeNode *BinTree;
struct TreeNode {
	int data;
	TreeNode *left;
	TreeNode *right;
};

/// 定义栈
typedef BinTree ElementType;
struct LinkStack
{
	ElementType data;
	LinkStack *next;
};

/// 创建
LinkStack* stackCreate()
{	
	LinkStack *topStack = (LinkStack *)malloc(sizeof(LinkStack));
	topStack->data = NULL;
	topStack->next = NULL;

	return topStack;
}

/// 是否为空栈
bool isEmptyStack(LinkStack *topStack)
{
	return topStack->next == NULL;
}

/// 入栈
void push(ElementType element, LinkStack *topStack)
{
	LinkStack *p = stackCreate();
	p->data = element;
	p->next = topStack->next;
	topStack->next = p;
}

/// 出栈
ElementType pop(LinkStack *topStack)
{
	if (!topStack->next)
	{
		printf("stack is empty\n");
		return NULL;
	}

	LinkStack *p = topStack->next;
	topStack->next = p->next;
	ElementType element = p->data;
	free(p);

	return element;
}

/// 定义队列
#define ERROR	NULL
#define MAXSIZE	100
typedef struct
{
	ElementType data[MAXSIZE];
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

/// 是否为空队列
bool isEmptyQueue(Queue *pQueue)
{
	return pQueue->front == pQueue->rear;
}

/// 入队
void addQ(ElementType element, Queue *pQueue)
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
ElementType deleteQ(Queue *pQueue)
{
	if (pQueue->front == pQueue->rear)
	{
		printf("queue is empty\n");
		return ERROR;
	}

	ElementType element = pQueue->data[(pQueue->front + 1) % MAXSIZE];
	pQueue->front = (pQueue->front + 1) % MAXSIZE;

	return element;
}

//////////////////////////////// 树的操作 //////////////////////////////////////

/// 创建
BinTree create(int i)
{
	BinTree bt = NULL;

	if (i < 10)
	{
		bt = (BinTree)malloc(sizeof(TreeNode));
		bt->data = i;

		bt->left = create(2 * i);
		bt->right = create(2 * i + 1);
	}

	return bt;
}

/// 先序遍历
void preOrderTraversal(BinTree bt)
{
	if(bt)
	{
		printf("preOrderRecursion: %d\n", bt->data);
		preOrderTraversal(bt->left);
		preOrderTraversal(bt->right);
	}
}

/// 中序遍历
void inOrderTraversal(BinTree bt)
{
	if(bt)
	{
		inOrderTraversal(bt->left);
		printf("inOrderRecursion: %d\n", bt->data);
		inOrderTraversal(bt->right);
	}
}

/// 后序遍历
void postOrderTraversal(BinTree bt)
{
	if(bt)
	{
		postOrderTraversal(bt->left);
		postOrderTraversal(bt->right);
		printf("postOrderRecursion: %d\n", bt->data);
	}
}

/////////////////////// 非递归遍历 ///////////////////////

/// 中序非递归遍历
void inOrderTraversalNonRecursion(BinTree bt)
{
	BinTree tree = bt;
	LinkStack *stack = stackCreate();

	while(tree || !isEmptyStack(stack))
	{
		if (tree)
		{
			push(tree, stack);
			// 先序
			// printf("inOrderTraversalNonRecursion: %d\n", tree->data);
			tree = tree->left;
		}
		else
		{
			tree = pop(stack);
			//  中序
			printf("inOrderTraversalNonRecursion: %d\n", tree->data);
			tree = tree->right;
		}
	}
}

/// 后序非递归遍历
void postOrderTraversalNonRecursion(BinTree bt)
{
	BinTree tree = bt;
	LinkStack *stack = stackCreate();
	LinkStack *outStack = stackCreate();

	/*
		思路：后续遍历顺序是 左右根。所以先用 根右左 的顺序遍历，再反转打印即可。
	*/
	while(tree || !isEmptyStack(stack))
	{
		if (tree)
		{
			push(tree, stack);
			push(tree, outStack);
			// printf("postOrderTraversalNonRecursion Reversal: %d\n", element->data);
			tree = tree->right;
		}
		else
		{
			tree = pop(stack);
			tree = tree->left;
		}
	}

	while(!isEmptyStack(outStack))
	{
		BinTree element = pop(outStack);
		printf("postOrderTraversalNonRecursion: %d\n", element->data);
	}
}

/// 层序遍历
void levelOrderTraversal(BinTree bt)
{
	BinTree tree = bt;
	if (!tree)
	{
		return;
	}
	Queue *queue = create();
	addQ(tree, queue);

	while(!isEmptyQueue(queue))
	{
		tree = deleteQ(queue);

		printf("levelOrderTraversal: %d\n", tree->data);

		if (tree->left)
		{
			addQ(tree->left, queue);
		}
		if (tree->right)
		{
			addQ(tree->right, queue);
		}
	}
}

/// 树高
int postOrderGetHeight(BinTree bt)
{
	int leftHeight, rightHeight, treeHeight;
	if (bt)
	{
		leftHeight = postOrderGetHeight(bt->left);
		rightHeight = postOrderGetHeight(bt->right);
		treeHeight = leftHeight > rightHeight ? leftHeight : rightHeight;
		return treeHeight + 1;
	}
	else
		return 0;
}

int main(int argc, char const *argv[])
{
	// 创建
	BinTree bt = create(1);

	// 递归遍历
	// preOrderTraversal(bt);
	// inOrderTraversal(bt);
	// postOrderTraversal(bt);

	// 非递归遍历
	// inOrderTraversalNonRecursion(bt);
	// postOrderTraversalNonRecursion(bt);

	// levelOrderTraversal(bt);

	// 树高
	int height = postOrderGetHeight(bt);
	printf("tree height: %d\n", height);

	return 0;
}