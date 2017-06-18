#include <stdio.h>
#include <stdlib.h>

/*
	哈夫曼树

	带权路径长度(WPL)：设二叉树有n个叶子结点，每个叶子结点带
	有权值 wk，从根结点到每个叶子结点的长度为 lk，则每个叶子结
	点的带权路径长度之和就是WPL

	最优二叉树或哈夫曼树：WPL最小的树
*/

typedef struct TreeNode *HuffmanTree;
struct TreeNode
{
	int weight;
	TreeNode *left;
	TreeNode *right;
};

/// 构造
HuffmanTree buildHuffman(MinHeap heap)
{
	HuffmanTree hufTree;

	//  建立最小堆
	buildMinHeap(heap);

	for (int i = 1; i <= heap->size; ++i)
	{
		hufTree = (HuffmanTree)malloc(sizeof(TreeNode));
		hufTree->left = deleteMinHeap(heap);
		hufTree->right = deleteMinHeap(heap);
		hufTree->weight = hufTree->left->weight + hufTree->right->weight;

		insertMinHeap(hufTree->weight, heap);
	}

	hufTree = deleteMinHeap(heap);

	return hufTree;
}


int main(int argc, char const *argv[])
{
	
	return 0;
}