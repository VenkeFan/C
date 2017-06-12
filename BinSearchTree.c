#include <stdio.h>
#include <stdlib.h>
#include "BinTreeSample.c"
#include "SequenceListSample.c"

/*
	二叉搜索树
*/

/// 创建
BinTree createBST()
{
	BinTree bst = (BinTree)malloc(sizeof(TreeNode));
	bst->left = NULL;
	bst->right = NULL;

	return bst;
}

/// 插入
BinTree insertBST(int data, BinTree bst)
{
	if (!bst)
	{
		bst = (BinTree)malloc(sizeof(TreeNode));
		bst->data = data;
		bst->left = NULL;
		bst->right = NULL;
		return bst;
	}

	if (data == bst->data)
	{
		return bst;
	}

	if (data > bst->data)
	{
		bst->right = insertBST(data, bst->right);
		return bst;
	}
	else
	{
		bst->left = insertBST(data, bst->left);
		return bst;
	}
}

/// 查找
BinTree find(int element, BinTree bst)
{
	if (!bst)
	{
		return NULL;
	}

	if (element > bst->data)
	{
		return find(element, bst->right);
	}
	else if (element < bst->data)
	{
		return find(element, bst->left);
	}
	else
	{
		return bst;
	}
}

/// 非递归查找
BinTree iterFind(int element, BinTree bst)
{
	if (!bst)
	{
		return NULL;
	}

	while(bst)
	{
		if(element > bst->data)
		{
			bst = bst->right;
		}
		else if (element < bst->data)
		{
			bst = bst->left;
		}
		else
		{
			return bst;
		}
	}
}

/// 查找最大元素
BinTree findMax(BinTree bst)
{
	while(bst)
	{
		if (bst->right)
		{
			bst = bst->right;
		}
		else
		{
			return bst;
		}
	}

	return NULL;
}

/// 查找最小元素
BinTree findMin(BinTree bst)
{
	if (!bst)
	{
		return NULL;
	}

	if (!bst->left)
	{
		return bst;	
	}
	else
	{
		return findMin(bst->left);
	}
}

/// 删除
BinTree deleteBST(int element, BinTree bst)
{
	if (!bst)
	{
		return NULL;
	}

	if (element > bst->data)
	{
		bst->right = deleteBST(element, bst->right);
	}
	else if (element < bst->data)
	{
		bst->left = deleteBST(element, bst->left);
	}
	else
	{
		BinTree temp = bst;
		if (!bst->left)
		{
			bst = bst->right;
		}
		else if (!bst->right)
		{
			bst = bst->left;
		}
		else
		{
			// 找右子树的最小元素
			temp = findMin(bst->right);
			bst->data = temp->data;
			bst->right = deleteBST(bst->data, bst->right);
		}
		free(temp);
	}

	return bst;
}

int main(int argc, char const *argv[])
{
	BinTree bst = NULL;
	// int list[] = {6, 3, 9, 1, 4, 7, 10, 2, 5, 8, 11};
	int list[] = {30, 20, 41, 15, 23, 35, 53, 21, 25, 39, 22, 37};
	for (int i = 0; i < 12; ++i)
	{
		// 插入
		bst = insertBST(list[i], bst);
	}

	// 查找
	// int element = 3;
	// BinTree item = find(element, bst);
	// printf("find position: %p\n", item);

	// BinTree item2 = iterFind(element, bst);
	// printf("iter find position: %p\n", item2);

	// 最大元素
	// BinTree maxItem = findMax(bst);
	// printf("maxItem position: %p, data: %d\n", maxItem, maxItem->data);

	// // 最小元素
	// BinTree minItem = findMin(bst);
	// printf("minItem position: %p, data: %d\n", minItem, minItem->data);

	// 删除
	deleteBST(20, bst);
	
	// 遍历
	levelOrderTraversal(bst);
	// preOrderTraversal(bst);

	return 0;
}