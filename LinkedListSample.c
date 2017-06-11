#include <stdio.h>
#include <stdlib.h>

/*
	线性表的链式存储实现

	本节示例为带头节点的单向链表。
	在带头结点的单链表中，其第一个结点被称作头结点。
	第一个存放数据元素的结点称作首元结点，头结点指向首元结点。
	头结点是为了操作的统一与方便而设立的，其一般不放数据（也可存放链表的长度、用做监视哨等）。
	此结点不能计入链表长度值。
*/

typedef struct Node
{
	int data;
	Node *next;
} List;

/// 尾插法创建链表
List* rearCreate(int size)
{
	// 头节点
	List *head = (List *)malloc(sizeof(List));
	head->data = -10000;
	head->next = NULL;

	List *prevP = head;

	for (int i = 1; i <= size; i++)
	{
		List *p = (List *)malloc(sizeof(List));
		p->data = i * 10;
		p->next = NULL;	

		prevP->next = p;
		prevP = p;
	}

	return head;
}

/// 头插法
List* frontCreate(int size)
{
	// 头节点
	List *head = (List *)malloc(sizeof(List));
	head->data = -10000;
	head->next = NULL;

	List *prevP = NULL;

	for (int i = 1; i <= size; ++i)
	{
		List *p = (List *)malloc(sizeof(List));
		p->data = i * 10;
		p->next = NULL;

		p->next = prevP;
		head->next = p;
		prevP = p;
	}

	return head;
}

/// 求表长
int length(List *head)
{
	// 头结点不能计入链表长度，所以从首元节点开始计！！
	List *p = head->next;
	int i = 0;

	while(p)
	{
		p = p->next;
		i++;
	}

	return i;
}

/// 按序号查找
List* findWithIndex(int index, List *head)
{
	List *p = head;
	int i = 0;

	if (index < i)
	{
		printf("find position: %d is illegal\n", index);
		return NULL;
	}

	while(p && i < index)
	{
		p = p->next;
		i++;
	}

	return p;
}

/// 按值查找
List* findWithElement(int element, List *head)
{
	List *p = head->next;
	while(p && p->data != element)
	{
		p = p->next;
	}

	return p;
}

/// 插入（在第 index 个位置）
List* insert(int element, int index, List *head)
{
	List *p;

	p = findWithIndex(index - 1, head); // 找到要插入位置的上一个节点
	if (p)
	{
		List *s = (List *)malloc(sizeof(List));
		s->data = element;

		s->next = p->next;
		p->next = s;
	}
	else
	{
		printf("insert position: %d is illegal\n", index);
	}

	return head;
}

/// 删除
List* deleteNode(int index, List *head)
{
	List *p = findWithIndex(index - 1, head); // 找到要删除位置的上一个节点

	if (!p || !p->next)
	{
		printf("delete position: %d is illegal\n", index);
	}
	else
	{
		List *tempP = p->next; // 要删除的节点
		p->next = tempP->next;
		free(tempP);
	}

	return head;
}

int main(int argc, char const *argv[])
{
	List *head = rearCreate(5);

	//表长
	printf("length: %d\n", length(head));

	// 遍历
	List *pList = head;
	while(pList)
	{
		printf("%d\n", pList->data);
		pList = pList->next;
	}
	printf("===========================================\n");

	// // 按序号查找
	// int index = 1;
	// List *p1 = findWithIndex(index, head);
	// if (p1)
	// {
	// 	printf("index: %d = %d\n", index, p1->data);
	// }
	// else
	// {
	// 	printf("index: %d not found\n", index);
	// }

	// // 按值查找
	// int element = 20;
	// List *p2 = findWithElement(element, head);
	// if (p2)
	// {
	// 	printf("element: %d found\n", element);
	// }
	// else
	// {
	// 	printf("element: %d not found\n", element);
	// }

	// // 插入
	// List *p = insert(9, 1, head);
	// while(p)
	// {
	// 	printf("%d\n", p->data);
	// 	p = p->next;
	// }

	// 删除
	List *p = deleteNode(1, head);
	while(p)
	{
		printf("%d\n", p->data);
		p = p->next;
	}

	return 0;
}