#include <stdio.h>
#include <stdlib.h>

/*
	图
	G(V,E)由一个非空的有限顶点集合V和一个可为空有限边集合E组成。
*/

#define MaxVertexNum 100    // 最大顶点数设为 100
#define INFINITY 65535      // ∞设为双字节无符号整数的最大值 65535
typedef int VertexIndex;	// 顶点下标
typedef int VertexData;		// 顶点存储的数据
typedef int WeightType;		// 边的权值

struct EdgeNode
{
	VertexIndex v1, v2; // (v1, v2) 无向边 / <v1, v2> 有向边
	WeightType weight;	// 权重
};
typedef EdgeNode *Edge;

///////////////////////////////// 图的邻接矩阵 /////////////////////////////////

struct Graph
{
	int vertexNum;		// 顶点数
	int edgeNum;		// 边数
	WeightType matrix[MaxVertexNum][MaxVertexNum];		// 邻接矩阵
};
typedef Graph *MatrixGraph;

/// 创建
MatrixGraph createMatrixGraph(int vertexCount)
{
	MatrixGraph g = (MatrixGraph)malloc(sizeof(Graph));
	g->vertexNum = vertexCount;
	g->edgeNum = 0;

	for (int i = 0; i < vertexCount; ++i)
	{
		// 对于无向图的存储，使用n* (n + 1) / 2 的一维数组可以节省一半的空间
		for (int j = 0; j < vertexCount; ++j)
		{
			g->matrix[i][j] = INFINITY;
		}
	}

	return g;
}

/// 插入边
MatrixGraph insertEdge(MatrixGraph g, Edge e)
{
	// 无向图
	g->matrix[e->v1][e->v2] = e->weight;
	g->matrix[e->v2][e->v1] = e->weight;

	return g;
}

///////////////////////////////// 图的邻接表 /////////////////////////////////

// 全局变量，用来标记顶点是否被访问过
#define FALSE 0
#define TRUE  1
short int Visited[MaxVertexNum];

// 定义顶点
struct VertexNode
{
	VertexIndex index;		// 顶点在图的指针数组中的下标
	VertexNode *next;
};
typedef VertexNode *Vertex;

// 定义图
struct GraphNode
{
	int vertexNum;			// 顶点数
	int edgeNum;			// 边数
	Vertex vertexList[];	// 指针数组，对应矩阵每行一个链表，只存非0元素
};
typedef GraphNode *LinkedGraph;

// 定义队列
typedef Vertex ElementType;
struct Queue
{
	int front, rear;
	ElementType data[MaxVertexNum];
};

Queue* createQueue()
{
	Queue *q = (Queue *)malloc(sizeof(Queue));
	q->front = q->rear = 0;
	return q;
}

bool isEmptyQueue(Queue *q)
{
	return q->front == q->rear;
}

void addQueue(Queue *q, ElementType element)
{
	if ((q->rear + 1) % MaxVertexNum == q->front)
	{
		printf("queue is full\n");
		return;
	}

	q->rear = (q->rear + 1) % MaxVertexNum;
	q->data[q->rear] = element;
}

ElementType deleteQueue(Queue *q)
{
	if (isEmptyQueue(q))
	{
		printf("queue is empty\n");
		return NULL;
	}

	ElementType element = q->data[(q->front + 1) % MaxVertexNum];
	q->front = (q->front + 1) % MaxVertexNum;

	return element;
}


/// 尾插法创建链表
Vertex rearCreate(int items[], int size)
{
	Vertex head = NULL, prevP = NULL;

	for (int i = 0; i < size; i++)
	{
		if (items[i] < 0)
		{
			break;
		}

		Vertex p = (Vertex)malloc(sizeof(VertexNode));
		p->index = items[i];
		p->next = NULL;	

		if (head)
		{
			prevP->next = p;
			prevP = p;
		}
		else
		{
			head = p;
			prevP = p;
		}
	}

	return head;
}

/// 创建
LinkedGraph createLinkedGraph(int vertexCount)
{
	LinkedGraph g = (LinkedGraph)malloc(sizeof(GraphNode));
	g->vertexNum = vertexCount;
	g->edgeNum = 0;
	g->vertexList[vertexCount] = (Vertex)malloc(vertexCount * sizeof(VertexNode));
	for (int i = 0; i < vertexCount; ++i)
	{
		// 指针必须初始化为 NULL
		g->vertexList[i] = NULL;
	}


	// 测试数据
	int list[vertexCount][vertexCount] = {{0, 1, 3, -1}, {1, 5, 3, 0, 2, -1}, {2, 1, 5, 4, -1}, {3, 7, 1, 0, 6, -1},
	 {4, 2, 5, 9, -1}, {5, 2, 1, 4, 6, 8, 9, -1}, {6, 5, 8, 7, 3, -1}, {7, 6, 3, -1}, {8, 9, 5, 6, -1}, {9, 4, 5, 8, -1}};
	for (int i = 0; i < vertexCount; ++i)
	{
		Vertex head = rearCreate(list[i], vertexCount);
		g->vertexList[i] = head;
	}

	return g;
}

/// 深度优先遍历
void linkedDFS(LinkedGraph g, int i)
{
	// 任意一个顶点
	Vertex v = g->vertexList[i];

	while(v)
	{
		if (Visited[v->index] != TRUE)
		{
			Visited[v->index] = TRUE;
			printf("DFS: %d, %p\n", v->index, v);

			linkedDFS(g, v->index);
		}
		v = v->next;
	}
}

/// 广度优先遍历
void linkedBFS(LinkedGraph g, int i)
{
	Vertex v = g->vertexList[i];
	if (!v)
	{
		return;
	}

	Queue *q = createQueue();
	Visited[v->index] = TRUE;
	addQueue(q, v);

	while(!isEmptyQueue(q))
	{
		v = deleteQueue(q);
		printf("BFS: %d, %p\n", v->index, v);
		
		v = g->vertexList[v->index];
		while(v)
		{
			if (Visited[v->index] != TRUE)
			{
				Visited[v->index] = TRUE;
				addQueue(q, v);
			}
			v = v->next;
		}
	}
}

/// 如果图不连通的话
void listComponents(LinkedGraph g)
{
	for (int i = 0; i < g->vertexNum; ++i)
	{
		Vertex v = g->vertexList[i];
		if (Visited[v->index] != TRUE)
		{
			linkedDFS(g, v->index); // 或者  linkedBFS(g, 2); 
		}
	}
}

/// 无权图的单源最短路算法


int main(int argc, char const *argv[])
{
	///////// 邻接矩阵的操作 /////////

	// MatrixGraph g = createMatrixGraph(10);


	///////// 邻接表的操作 /////////

	LinkedGraph g= createLinkedGraph(10);

	// linkedDFS(g, 2);

	// linkedBFS(g, 2);

	// listComponents(g);

	return 0;
}