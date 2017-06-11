#include <stdio.h>
#include <stdlib.h>
#include "SequenceListSample.c"

/*
	树
*/

/// 顺序查找
int sequentialSearch(int element, List *list)
{
	int index = -1;
	int searchCount = 0;

	for (int i = 0; i < list->last + 1; ++i)
	{
		searchCount++;

		if (list->data[i] == element)
		{
			index = i;
			break;
		}
	}

	printf("sequential search count: %d\n", searchCount);

	return index;
}

/// 二分查找（数据元素必须是有序连续存放的）
int binarySearch(int element, List *list)
{
	int index = -1;
	int left = 0, right = list->last;
	int searchCount = 0;

	while(left <= right)
	{
		searchCount++;

		int middle = (left + right) / 2;

		if (element < list->data[middle])
		{
			right = middle - 1;
		}
		else if (element > list->data[middle])
		{
			left = middle + 1;
		}
		else
		{
			index = middle;
			break;
		}
	}

	printf("binary search count: %d\n", searchCount);
	
	return index;
}

int main(int argc, char const *argv[])
{
	/*
						       10
					 
					  4		            16
				  
				  0	      6	  	    12       18
					
					2       8         14       20
		
		该数组的二分查找判定数
	*/
	// 创建数组
	List *pList = createEmptyList();
	for (int i = 0; i < 11; i++)
	{
		pList->data[i] = i * 2;
		pList->last ++;
	}
	
	int element = 10;
	// int index = sequentialSearch(element, pList);
	// printf("sequentialSearch: element %d -> index %d\n", element, index);

	int index = binarySearch(element, pList);
	printf("binarySearch: element %d -> index %d\n", element, index);

	

	// 遍历
	for (int i = 0; i < pList->last + 1; ++i)
	{
		printf("%d\n", pList->data[i]);
	} 
	
	return 0;
}