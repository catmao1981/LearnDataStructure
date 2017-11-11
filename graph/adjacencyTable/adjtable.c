#include<stdio.h>    
#include<stdlib.h>   
#include<io.h>  
#include<math.h>  
#include<time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXVEX 100 /* 最大顶点数,应由用户定义 */

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码,如OK等 */
typedef char VertexType; /* 顶点类型应由用户定义 */
typedef int EdgeType; /* 边上的权值类型应由用户定义 */
typedef int GraphType;	/* GraphType图的类型1-有向图 0-无向图*/

//图的类型
GraphType graphType;

typedef struct EdgeNode /* 边表结点  */
{
	int adjvex;    /* 邻接点域,存储该顶点对应的下标 */
	EdgeType info;		/* 用于存储权值,对于非网图可以不需要 */
	struct EdgeNode *next; /* 链域,指向下一个邻接点 */
}EdgeNode;

typedef struct VertexNode /* 顶点表结点 */
{
	VertexType data; /* 顶点域,存储顶点信息 */
	EdgeNode *firstedge;/* 边表头指针 */
}VertexNode, AdjList[MAXVEX];

typedef struct{
	AdjList adjList; 
	int numNodes,numEdges; /* 图中当前顶点数和边数 */
}GraphAdjList;

/* 建立图的邻接表结构 */
void  CreateALGraph(GraphAdjList *G){
	int i,j,k;
	EdgeNode *e;
	printf("输入顶点数和边数:\n");
	scanf("%d,%d",&G->numNodes,&G->numEdges); 
	
	printf("输入顶点信息\n");
	
	for(i = 0;i < G->numNodes;i++) /* 读入顶点信息,建立顶点表 */
	{
		scanf("%d",&(G->adjList[i].data)); 	/* 输入顶点信息 */
		G->adjList[i].firstedge=NULL; 	/* 将边表置为空表 */
	}
	
	for(k = 0;k < G->numEdges;k++)/* 建立边表 */
	{
		printf("输入边(vi,vj)上的顶点序号:\n");
		scanf("%d,%d",&i,&j); /* 输入边(vi,vj)上的顶点序号 */
		e=(EdgeNode *)malloc(sizeof(EdgeNode)); /* 向内存申请空间,生成边表结点 */
		e->adjvex=j;					/* 邻接序号为j */                         
		e->next=G->adjList[i].firstedge;	/* 采用链表头插法:将e的指针指向当前顶点上指向的结点 */
		G->adjList[i].firstedge=e;		/* 将当前顶点的指针指向e */               
		
		//因是无向表,则两个节点都要进行插入
		e=(EdgeNode *)malloc(sizeof(EdgeNode)); /* 向内存申请空间,生成边表结点 */
		e->adjvex=i;					/* 邻接序号为i */                         
		e->next=G->adjList[j].firstedge;	/* 将e的指针指向当前顶点上指向的结点 */
		G->adjList[j].firstedge=e;		/* 将当前顶点的指针指向e */               
	}
	
}

/* 显示无向图的详情 */
void displayGraph(GraphAdjList *graph){
	int i,j,edge;
	printf("顶点数:%d,边数:%d\n",graph->numNodes,graph->numEdges);
	for(i=0;i<graph->numNodes;i++){
			printf("顶点:%d\n",graph->adjList[i].data);
			printf("边:");
			VertexNode vertexNode = graph->adjList[i];
			EdgeNode *en = vertexNode.firstedge; 
			while(en != NULL){
					edge = en->adjvex;
					printf("-%d",edge);
					en = en->next;		
				}
			printf("\n");					
		}		
}

/* 建立有向图的邻接表结构 */
void  CreateDirALGraph(GraphAdjList *G){
	int i,j,k;
	EdgeNode *e;
	printf("输入顶点数和弧数:\n");
	scanf("%d,%d",&G->numNodes,&G->numEdges); 
	
	printf("输入顶点信息\n");
	
	for(i = 0;i < G->numNodes;i++) /* 读入顶点信息,建立顶点表 */
	{
		scanf("%d",&(G->adjList[i].data)); 	/* 输入顶点信息 */
		G->adjList[i].firstedge=NULL; 	/* 将边表置为空表 */
	}
	
	for(k = 0;k < G->numEdges;k++)/* 建立边表 */
	{
		printf("输入弧<vi,vj>上的顶点序号:\n");
		scanf("%d,%d",&i,&j); /* 输入边(vi,vj)上的顶点序号 */
		e=(EdgeNode *)malloc(sizeof(EdgeNode)); /* 向内存申请空间,生成边表结点 */
		e->adjvex=j;					/* 邻接序号为j */                         
		e->next=G->adjList[i].firstedge;	/* 采用链表头插法:将e的指针指向当前顶点上指向的结点 */
		G->adjList[i].firstedge=e;		/* 将当前顶点的指针指向e */                              
	}
	
}


int main(void){    
	GraphAdjList G;
	printf("请输入图的类型1-有向图 0-无向图:\n");
	scanf("%d",&graphType); /* 设置图的类型 */    
	if(graphType){
			CreateDirALGraph(&G);
			printf("显示有向图详情如下:\n");
			displayGraph(&G);
		}else{
			CreateALGraph(&G);
			printf("显示无向图详情如下:\n");
			displayGraph(&G);		
			}
	
	
	return 0;
}

