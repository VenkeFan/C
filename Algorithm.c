#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Heap.c"

/*
	算法
*/

/// Hailstone问题
int hailstone(int n)
{
	int length = 0;
	while (n > 1)
	{
		n = n % 2 == 0 ? n / 2 : (3 * n) + 1;
		length++;
	}
	return length;
}

/// 交换两个整数
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void swap2(int a, int b)
{
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;

	printf("a = %d, b = %d\n", a, b);
}

/// 斐波纳契（递归）
long fibonacciRecursive(int n)
{
	return n < 2 ? n : fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

/// 斐波纳契（迭代）
long long fibonacciIter(int n)
{
	if (n < 2)
	{
		return n;
	}
	long long n0 = 0, n1 = 1;

	for (int i = 1; i < n; ++i)
	{
		n1 = n0 + n1;
		n0 = n1 - n0;
	}

	return n1;
}

/// 冒泡排序
void bubbleSort(int array[], int length)
{
	int count = 0; // 记录循环总次数
	for (int i = length - 1; i >= 0; --i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (array[j] > array[j + 1])
			{
				swap(&array[j], &array[j + 1]);
			}
			count++;
		}
	}

	printf("bubbleSort count: %d\n", count);
}

/// 冒泡排序（改进版）
void bubbleSort_2(int array[], int length)
{
	int count = 0; // 记录循环总次数
	for (int i = length - 1; i >= 0; --i)
	{
		bool sorted = true; // 是否已经有序

		for (int j = 0; j < i; ++j)
		{
			if (array[j] > array[j + 1])
			{
				swap(&array[j], &array[j + 1]);

				sorted = false;
			}
			count++;
		}

		if (sorted)
		{
			break;
		}
	}

	printf("bubbleSort_2 count: %d\n", count);
}

void bubbleSort_3(int array[], int length)
{
	int count = 0; // 记录循环总次数
	int i = length - 1;

	while (i > 0)
	{
		int rank = 0; // 记录上次排序最后交换的位置
		for (int j = 0; j < i; ++j)
		{
			if (array[j] > array[j + 1])
			{
				swap(&array[j], &array[j + 1]);

				rank = j;
			}
		}
		i = rank;

		count++;
	}

	printf("bubbleSort_3 count: %d\n", count);
}

/// 插入排序
void insertionSort(int array[], int length)
{
	for (int i = 1; i < length; ++i)
	{
		int temp = array[i];

		int j = i;
		for (; j > 0 && array[j - 1] > temp; --j)
		{
			array[j] = array[j - 1];
		}

		array[j] = temp;
	}
}

/// 希尔排序
void shellSort(int array[], int length)
{
	// Sedgewick 增量序列
	// for (int i = 0; i < length; ++i)
	// {
	// 	int increment = 9 * pow(4, i) - 9 * pow(2, i) + 1;
	// }


	// Hibbard 增量序列
	// pow(2, length) - 1
	
	for (int i = length / 2; i > 0; i /= 2)
	{
		for (int j = i; j < length; j += i)
		{
			int temp = array[j];
			int k = j;
			for (; k > 0 && array[k - i] > temp; k -= i)
			{
				array[k] = array[k - i];
			}
			array[k] = temp;
		}
	}
}

/// 堆排序
void heapSortt(int array[], int length)
{

}

MaxHeap buildHeap(int array[], int length)
{
	MaxHeap heap = (MaxHeap)malloc(sizeof(HeapStruct));
	heap->elements = (ElementType *)malloc((length + 1) * sizeof(ElementType));
	heap->size = length;
	heap->capacity = length;
	heap->elements[0] = MAXDATA;

	return heap;
}

int main(int argc, char const *argv[])
{
	// 斐波纳契数列
	// {
	// 	int count = 9;
	// 	// for (int i = 0; i < count; ++i)
	// 	// {
	// 	// 	printf("recursion fibonacciRecursive(%d) = %d\n", i, fibonacciRecursive(i));
	// 	// }
	// 	printf("==========================================\n");
	// 	for (int i = 0; i < count; ++i)
	// 	{
	// 		printf("iter fibonacciIter(%d) = %lld\n", i, fibonacciIter(i));
	// 	}
	// }


	// Hailstone问题
	// {
	// 	int length = hailstone(27);
	// 	printf("hailstone length: %d\n", length);
	// }

	// int array[] = {19, 12, 30, 9, 6, 25, 15, 36, 59, 10, 78, 65, 46, 99, 83, 66};
	// int length = sizeof(array) / sizeof(array[0]);

	// // 冒泡排序
	// // bubbleSort(array, length);
	// // bubbleSort_2(array, length);
	// // bubbleSort_3(array, length);
	
	// // insertionSort(array, length);

	// // shellSort(array, length);

	// for (int i = 0; i < length; ++i)
	// {
	// 	printf("%d\n", array[i]);
	// }

	swap2(3, 4);

	return 0;
}