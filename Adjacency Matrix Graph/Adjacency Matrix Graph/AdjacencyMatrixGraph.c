#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define VertexMax 100 //��󶥵���Ϊ100
#define MaxInt 32767 //��ʾ�����������ʾ ��
#define MVNum 10
//typedef enum{DG,UDG,DN,UDN}GraphKind;
typedef char VertexType; //ÿ��������������Ϊ�ַ���
typedef int VerTexType;
typedef struct AMGraph
{
	VertexType vexs[VertexMax];//��Ŷ���Ԫ�ص�һά����
	int arcs[VertexMax][VertexMax];//�ڽӾ����ά���� 
	int vexnum, arcnum;//ͼ�Ķ������ͱ���
	int kind;//��ǰͼ�����ͣ�1����ͼDG,2����ͼUDG,3������DN,4������UDN�� 
}AMGraph,*AAMGraph;
typedef struct VNode
{
	VerTexType data;//�������
	struct ArcNode* firstarc;//ָ���һ�������ö���ıߵ�ָ��
}VNode,AdjList[MVNum];//AdjList��ʾ�ڽӱ�����
typedef struct ArcNode
{
	VerTexType AdjVex;
	VNode* Nextarc;
}ArcNode;
typedef struct ALGraph
{
	AdjList vertices;//vertices--vertex�ĸ���,����ָ��ôһ��������
	int vexnum, arcnum;//ͼ�ĵ�ǰ����ͻ���
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
//1.��������ͼ��Directed Graph��
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
	printf("�������ܶ�����,�ܱ���:>");
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
	//��Ϊ������ͼ,��������Ҫ�ٴ���һ�����,���к�p1һ���Ĳ���
}
void main()
{
	AMGraph G;
	ALGraph G1;
	//G = (AMGraph*)malloc(sizeof(AMGraph));
	CreateUDG(&G);
	CreateUDG_1(&G1);
	return 0;
}//ע������д