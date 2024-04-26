#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define VertexMax 100 //最大顶点数为100
#define MaxInt 32767 //表示最大整数，表示 ∞
#define MVNum 10
//typedef enum{DG,UDG,DN,UDN}GraphKind;
typedef char VertexType; //每个顶点数据类型为字符型
typedef int VerTexType;
typedef struct AMGraph
{
	VertexType vexs[VertexMax];//存放顶点元素的一维数组
	int arcs[VertexMax][VertexMax];//邻接矩阵二维数组 
	int vexnum, arcnum;//图的顶点数和边数
	int kind;//当前图的类型（1有向图DG,2无向图UDG,3有向网DN,4无向网UDN） 
}AMGraph,*AAMGraph;
typedef struct VNode
{
	VerTexType data;//存放数据
	struct ArcNode* firstarc;//指向第一条依附该顶点的边的指针
}VNode,AdjList[MVNum];//AdjList表示邻接表类型
typedef struct ArcNode
{
	VerTexType AdjVex;
	VNode* Nextarc;
}ArcNode;
typedef struct ALGraph
{
	AdjList vertices;//vertices--vertex的复数,这里指这么一个的数组
	int vexnum, arcnum;//图的当前顶点和弧数
}ALGraph;
int LocateVex(AMGraph* G, int Vex)
{
	int i = 0;
	for (i = 0; i < G->vexnum; i++)
	{
		if (Vex == G->vexs[i])
			return i;
		return 0;
	}
}
int  LocateVex_1(ALGraph* G, int Vex)
{
	int i = 0;
	for (i = 0; i < G->vexnum; i++)
	{
		if (Vex == G->vertices[i].data)
			return i;
		return 0;
	}
}
//1.构建有向图（Directed Graph）
void CreateUDG(AMGraph* G)
{
	int i = 0, j = 0, k = 0, v1 = 0, v2 = 0, weight = 0;
	//G = (AMGraph*)malloc(sizeof(AMGraph));
	printf("please input vexnum and arcnum:>");
	G->vexnum = 0;
	G->arcnum = 0;
	scanf("%d%d", &G->vexnum, &G->arcnum);
	printf("please input information of vexnum:>");
	for (i = 0; i < G->vexnum; i++)
	{
		scanf("%c",&G->vexs[i]);
	}
	for (i = 0; i < G->vexnum; i++)
	{
		for (j = 0; j < G->vexnum; j++)
		{
			G->arcs[i][j] = MaxInt;
		}
	}
	printf("please input one side of weight V1 and V2:>");
	for (k = 0; k < G->arcnum; k++)
	{
		scanf("%d%d%d", &v1, &v2, &weight);
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		G->arcs[i][j] = weight;
		G->arcs[j][i] = G->arcs[i][j];
	}

}
void CreateUDG_1(ALGraph* G1)
{
	int v1 = 0, v2 = 0;
	int i = 0, j = 0;
	G1 = (ALGraph*)malloc(sizeof(ALGraph));
	printf("请输入总顶点数,总边数:>");
	scanf("%d%d", &G1->vexnum, &G1->arcnum);
	for (int i = 0; i < G1->vexnum; i++)
	{
		scanf("%d", &G1->vertices[i].data);
		G1->vertices[i].firstarc = NULL;
	}
	for (int k = 0; k < G1->arcnum; k++)
	{
		scanf("%d%d", &v1, &v2);
	}
	i = LocateVex_1(&G1, &v1);
	j = LocateVex_1(&G1, &v2);
	ArcNode* p1=NULL;
	p1 = (ArcNode*)malloc(sizeof(ArcNode));
	if (p1 == NULL)
		exit(0);
	if (G1 == NULL)
		exit(0);
	p1->AdjVex = j;
	p1->Nextarc = G1->vertices[i].firstarc;
	G1->vertices[i].data = p1;
	ArcNode* p2 = NULL;
	p2 = (ArcNode*)malloc(sizeof(ArcNode));
	if (p2 == NULL)
		exit(0);
	if (G1 == NULL)
		exit(0);
	p2->AdjVex = i;
	p2->Nextarc = G1->vertices[j].firstarc;
	G1->vertices[j].data = p2;
	//因为是无向图,所以这里要再创建一个结点,进行和p1一样的操作
}
void main()
{
	AMGraph G;
	ALGraph G1;
	//G = (AMGraph*)malloc(sizeof(AMGraph));
	CreateUDG(&G);
	CreateUDG_1(&G1);
	return 0;
}//注释懒得写