#include <stdio.h>
#include <stdlib.h>

/*
	集合

	用树结构表示集合，树的每个结点代表一个集合元素。
	使用双亲表示法：孩子指向双亲
*/

#define MAXSIZE 10 // 集合最大元素个数

typedef int ElementType;

typedef struct
{
	ElementType data;
	int parent; //采用数组存储形式，parent 非负数代表双亲的下标，负数代表是根节点，绝对值代表集合的元素个数。
} SetType;


/// 查找某个元素所在的集合（用根结点表示）
int find(SetType set[], ElementType element)
{
	int i;

	for (i = 0; i < MAXSIZE && element != set[i].data; ++i)
	{
		// 里面啥也不干...
	}

	if (i >= MAXSIZE)
	{
		return -1;
	}

	for (; set[i].parent >= 0; i = set[i].parent)
	{
		// 里面啥也不干...
	}

	return i;
}

/// 集合的并运算
void union(SetType set[], ElementType x1, ElementType x2)
{
	int root1 = find(set, x1);
	int root2 = find(set, x2);

	if (root1 != root2)
	{
		// 为了改善合并以后的查找性能，可以采用小的集合合并到相对大的集合中
		if (abs(set[root1].parent) > abs(set[root2].parent))
		{
			set[root2].parent = root1;
		}
		else
		{
			set[root1].parent = root2;
		}
	}
}

int main(int argc, char const *argv[])
{
	SetType set[MAXSIZE] = {{.data = 1, .parent = -3}, {.data = 2, .parent = 0}, 
					{.data = 3, .parent = -2}, {.data = 4, .parent = 0},
					{.data = 5, .parent = 2}, {.data = 6, .parent = -2},
					{.data = 7, .parent = 0}, {.data = 8, .parent = 2},
					{.data = 9, .parent = 5}, {.data = 10, .parent = 5}
					};

	int i = find(8, set);

	
	return 0;
}