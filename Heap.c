#include <stdio.h>
#include <stdlib.h>
#include <time.h>

clock_t start, stop;

/*
	堆

	堆的两个特性
 		结构性：用数组表示的完全二叉树；	
      	有序性：任一结点的关键字是其子树所有结点的最大值(或最小值)

    堆的元素下标从1开始，0位置一般定义一个哨兵！！
*/

#define MAXDATA 99999999	// 定义“哨兵”为大于堆中所有可能元素的值，便于以后更快操作
#define ERROR	-99999

typedef int ElementType;

struct HeapStruct
{
	ElementType *elements;	// 堆元素数组的指针
	int size;				// 当前元素个数
	int capacity;			// 最大容量
};

typedef HeapStruct *MaxHeap;

/// 创建
MaxHeap createEmpty(int maxSize)
{
	MaxHeap heap = (MaxHeap)malloc(sizeof(HeapStruct));
	heap->elements = (ElementType *)malloc((maxSize + 1) * sizeof(ElementType));
	heap->size = 0;
	heap->capacity = maxSize;
	heap->elements[0] = MAXDATA;	// 把MaxData换成小于堆中所有元素的MinData，同样适用于创建最小堆

	return heap;
}

/// 建立
MaxHeap buildMaxHeap(int maxSize)
{
	MaxHeap heap = (MaxHeap)malloc(sizeof(HeapStruct));
	heap->elements = (ElementType *)malloc((maxSize + 1) * sizeof(ElementType));
	heap->size = maxSize;
	heap->capacity = maxSize;
	heap->elements[0] = MAXDATA;

	int m = 100, s = 5;
    srand(s);

	// 先将N个元素按顺序存入，以满足堆的完全二叉树结构特性
	for (int i = 1; i <= maxSize; ++i)
	{
		heap->elements[i] = rand() % m;
		printf("%d\n", heap->elements[i]);
	}

	// 调整节点位置，以满足堆的有序特性
	for (int i = heap->size / 2; i >=1; i--) // 从最后一个节点的父节点开始
	{
		int parent = i, child;
		ElementType parentElement = heap->elements[parent];

		for (; parent * 2 <= heap->size; parent = child)
		{
			child = parent * 2;

			if (child < heap->size && heap->elements[child] < heap->elements[child + 1])
			{
				child++;
			}

			if (parentElement > heap->elements[child])
			{
				break;
			}
			else
			{
				heap->elements[parent] = heap->elements[child];
			}
		}

		heap->elements[parent] = parentElement;
	}

	return heap;
}

/// 插入
void insert(ElementType element, MaxHeap heap)
{
	if (heap->size == heap->capacity)
	{
		printf("heap is full\n");
		return;
	}


	// heap->size++;
	// heap->elements[heap->size] = element;

	// for (int i = heap->size; i >= 1; i /= 2)
	// {
	// 	if (element > heap->elements[i / 2])
	// 	{
	// 		heap->elements[i] = heap->elements[i / 2];
	// 		heap->elements[i / 2] = element;
	// 	}
	// }


	// 过滤节点的方法比交换数据要快
	int i = ++heap->size;

	for (; element > heap->elements[i / 2]; i /= 2)
	{
		heap->elements[i] = heap->elements[i / 2];
	}

	heap->elements[i] = element;
}

/// 删除
ElementType deleteMaxHeap(MaxHeap heap)
{
	if (heap->size == 0)
	{
		printf("heap is empty\n");
		return ERROR;
	}

	// 取出根结点最大值
	ElementType maxItem = heap->elements[1];
	
	// 用最大堆中最后一个元素从根结点开始向上过滤下层结点
	ElementType temp = heap->elements[heap->size];
	
	heap->size--;

	int parent, child;

	for (parent = 1; parent * 2 <= heap->size; parent = child)
	{
		child = parent * 2;

		if (child < heap->size && heap->elements[child] < heap->elements[child + 1])
		{
			child++;
		}

		// 找到了合适的位置
		if (temp > heap->elements[child])
		{
			break;
		} 
		else 
		{
			// 下滤
			heap->elements[parent] = heap->elements[child];
		}
	}

	heap->elements[parent] = temp;

	return maxItem;
}

int main(int argc, char const *argv[])
{
	int maxSize = 6;
	
	int m = 100, s = 5;
    srand(s); //设置随机数种子
    int list[maxSize]; // 随机数数组
    for (int i = 0; i < maxSize; ++i)
    {
    	list[i] = rand() % m;
    }


	// // 创建
	// MaxHeap heap = createEmpty(maxSize);


	// // start = clock();
	// // 插入
	// for (int i = 1; i <= maxSize; ++i)
	// {
	// 	int item = list[i - 1];
	// 	insert(item, heap);
	// }
	// // stop = clock();
	// // printf("tick: %f\n", (double)(stop - start)); // 测试插入耗费的时间

	// 建立
	MaxHeap heap = buildMaxHeap(maxSize);

	// // 删除
	// for (int i = 0; i < maxSize; ++i)
	// {
	// 	ElementType item = deleteMaxHeap(heap);
	// 	printf("delete: %d\n", item);
	// }
	

	for (int i = 0; i <= heap->size; ++i)
	{
		printf("%d\n", heap->elements[i]);
	}

	return 0;
}