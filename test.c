#include <stdio.h>
#include <time.h>

void printN(int n)
{
	for (int i = 0; i < n; ++i)
	{
		printf("%d\n", i);
	}
}

// 递归打印
void recursionPrintN(int n)
{
	if (n)
	{
		recursionPrintN(n - 1);
		printf("recursionPrintN: %d\n", n);
	}
}

/*
	给定N个整数的序列{ A1, A2, …, AN}，求函数的最大值。
	即最大子列和
*/
int MaxSubseqSum1(int array[], int count)
{
	int maxSum = 0, currentSum = 0;
	
	for (int i = 0; i < count; ++i)
	{
		currentSum += array[i];
		if (currentSum > maxSum)
		{
			maxSum = currentSum;
		}
		if (currentSum < 0)
		{
			currentSum = 0;
		}
	}

	return maxSum;
}

int main(int argc, char const *argv[])
{
	// int n = 100000;
	// recursionPrintN(n);

	int array[] = {4, -3, 5, -2, -1, 2, 6, -2};
	int maxSum = MaxSubseqSum1(array, 8);
	printf("%d\n", maxSum);

	return 0;
}