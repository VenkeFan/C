#include <stdio.h>

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

// quick sort
int median3(int array[], int left, int right) {
	int center = (left + right) / 2;
	
	if (array[left] > array[center]) swap(&array[left], &array[center]);
	if (array[left] > array[right]) swap(&array[left], &array[right]);
	if (array[center] > array[right]) swap(&array[center], &array[right]);
	
	return array[center];
}

void quickSort(int array[], int left, int right) {
	if (left >= right) return;
	
	int pivot = median3(array, left, right);
	printf("pivot = %d\n", pivot);
	int i = left, j = right;
	while(i < j) {
		while(array[i] < pivot) {i++;}
		while(array[j] > pivot) {j--;}
		
		swap(&array[i], &array[j]);
		
		if (array[j] == pivot) j--;
	}
	
	quickSort(array, left, i - 1);
	quickSort(array, i + 1, right);
}

// bubble sort
void bubbleSort(int array[], int left, int right) {
	for (int i = right; i >= left; i--) {
		int flag = 0;
		for (int j = 0; j < i; j++) {
			if (array[j] > array[j + 1]) {
				swap(&array[j], &array[j + 1]);
				
				flag = 1;
			}
		}
		
		if (0 == flag) break;
	}
}

// selection sort
void selectionSort(int array[], int left, int right) {
	for (int i = left; i <= right; i++) {
		int min = i;
		for (int j = i + 1; j <= right; j++) {
			if (array[j] < array[min]) {
				min = j;
			}
		}
		if (min != i) {
			swap(&array[min], &array[i]);
		}
	}
}

// insert sort
void insertSort(int array[], int left, int right) {
	for (int i = left + 1; i <= right; i++) {
		int temp = array[i];
		int j = i - 1;
		while (j >= 0) {
			if (array[j] > temp) {
				array[j + 1] = array[j];
				j--;
			} else {
				break;
			}
		}
		array[j + 1] = temp;
	}
}

// merge sort
void merge(int array[], int resultArray[], int left, int right, int center) {
	int i = left;
	int j = center + 1;
	int index = 0;
	while (i <= center && j <= right) {
		if (array[i] < array[j]) {
			resultArray[index++] = array[i++];
		} else {
			resultArray[index++] = array[j++];
		}
	}
	
	while (i <= center) {
		resultArray[index++] = array[i++];
	}
	while (j <= right) {
		resultArray[index++] = array[j++];
	}
	
	index = 0;
  	while(left <= right){
		array[left++] = resultArray[index++];
	}
}

void merge_Sort(int array[], int resultArray[], int left, int right) {
	if (left >= right) return;
	
	int center = (left + right) / 2;
	merge_Sort(array, resultArray, left, center);
	merge_Sort(array, resultArray, center + 1, right);
	merge(array, resultArray, left, right, center);
}

void mergeSort(int array[], int left, int right) {
	int resultArray[right + 1];
	merge_Sort(array, resultArray, left, right);
}

// shell sort
void shellSort(int array[], int left, int right) {
	for (int d = (right + 1) / 2; d > 0; d /= 2) {
		for (int i = d; i <= right; i++) {
			int temp = array[i];
			int j = i - d;
			while (j >= 0) {
				if (array[j] > temp) {
					array[j + d] = array[j];
					j -= d;
				} else {
					break;
				}
			}
			array[j + d] = temp;
		}
	}
}

// bucket sort
void bucket_Sort(int array[], int left, int right, int bucketCount) {
	int buckets[bucketCount][1];// 此处桶的容量设为1，只为实现桶排序的原理。应该是数组或链表
	int flag = -1;
	for (int i = 0; i < bucketCount; i++) {
		buckets[i][0] = flag;
	}
	
	for (int i = left; i <= right; i++) {
		// 此处应是把值插入和桶的下标相同的桶里，这里只是简化了，因为C语言还得自己定义数组或聊表
		buckets[array[i]][0] = array[i];
	}
	
	int index = 0;
	for (int i = 0; i < bucketCount; i++) {
		if (buckets[i][0] != flag) {
			array[index++] = buckets[i][0];
		}
	}
}

void bucketSort(int array[], int left, int right) {
	if (left >= right) return;
	
	int min = array[0], max = array[0];
	for (int i = left; i <= right; i++) {
		if (min > array[i]) min = array[i];
		if (max < array[i]) max = array[i];
	}
	
	int bucketCount = max + 1;
	// if (right + 1 >> bucketCount)
	bucket_Sort(array, left, right, bucketCount);
	// else {other sort}
}

int main()
{
   	//int array[] = {98, 36, 12, 30, 9, 6, 25, 15, 19, 59, 10, 78, 65, 46, 99, 83, 66};
	int array[] = {3,0,8,4,5,6,1,5,5};
	//int array[] = {3,2,1,4};
	
	int length = sizeof(array) / sizeof(array[0]);
   	
   	//quickSort(array, 0, length - 1);
	
	//bubbleSort(array, 0, length - 1);
	
	//selectionSort(array, 0, length - 1);
	
	//insertSort(array, 0, length - 1);
	
	//mergeSort(array, 0, length - 1);

	//shellSort(array, 0, length - 1);

	//bucketSort(array, 0, length - 1);

	for (int i = 0; i < length; ++i)
	{
		printf("%d\n", array[i]);
	}

   	return 0;
}