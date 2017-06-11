#include <stdio.h>
#include <stdlib.h>

/*
	线性表的顺序存储实现
*/

#define MAXSIZE	100
typedef struct
{
	int data[MAXSIZE];
	int last;	// 数组的下标。线性表的长度：L.Last+1 或 PtrL->Last+1
} List;

/// 创建空数组
List* createEmptyList()
{
	List *pList = (List*)malloc(sizeof(List));
	pList->last = -1;

	return pList;
}

/// 查找数组中的元素
int findElement(int element, List *pList)
{
	int index = -1;
	for (int i = 0; i <= pList->last; ++i)
	{
		if (element == pList->data[i])
		{
			index = i;
			break;
		}
	}
	return index;
}

/// 插入
void insertElement(int element, int index, List *pList)
{
	if (pList->last + 1 == MAXSIZE)
	{
		printf("list if full\n");
		return;
	}

	if (index < 0 || index > pList->last + 1)
	{
		printf("position is illegal\n");
		return;
	}

	for (int i = pList->last; i >= index; --i)
	{
		pList->data[i+1] = pList->data[i];
	}
	pList->data[index] = element;
	pList->last++;
}

/// 删除
void deleteElement(int index, List *pList)
{
	if (index < 0 || index > pList->last)
	{
		printf("the index: %d is illegal\n", index);
		return;
	}

	for (int i = index; i <= pList->last; ++i)
	{
		pList->data[i] = pList->data[i + 1];
	}
	pList->last--;
}

// int main(int argc, char const *argv[])
// {
// 	// 创建数组
// 	List *pList = createEmptyList();
// 	for (int i = 0; i < 5; i++)
// 	{
// 		pList->data[i] = i * 2;
// 		pList->last ++;
// 	}

// 	// insertElement(17, 4, pList);
// 	// deleteElement(4, pList);
// 	int index = findElement(8, pList);
// 	printf("index: %d\n", index);

// // 遍历，用 pList->last + 2 是为了看看数组的元素有没有真的被删除
// for (int i = 0; i <= pList->last + 2; ++i)
// {
// 	printf("%d\n", pList->data[i]);
// } 

// 	return 0;
// }