#include <stdio.h>
#include <stdlib.h>
#include "Graph.c"

/*
	最短路径问题
*/

/// 无权图的单源最短路算法
void unWeighted(LinkedGraph g)
{

}

int main(int argc, char const *argv[])
{
	LinkedGraph g = createLinkedGraph(10);
	linkedBFS(g, 3);
	
	return 0;
}