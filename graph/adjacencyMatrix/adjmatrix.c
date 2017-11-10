#include<stdio.h>    
#include<stdlib.h>   
#include<io.h>  
#include<math.h>  
#include<time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXVEX 100 /* 最大顶点数，应由用户定义 */
#define INFINITY 65535 /*模拟无穷大*/

typedef int GraphType;	/* GraphType图的类型1-有向图 0-无向图*/
typedef char VertexType; /* 顶点类型应由用户定义  */
typedef int EdgeType; /* 边上的权值类型应由用户定义 */
//图的类型
GraphType graphType;
//邻接矩阵数据结构
typedef struct
{
	VertexType vexs[MAXVEX]; /* 顶点表 */
	EdgeType arc[MAXVEX][MAXVEX];/* 邻接矩阵，可看作边表 */
	int numNodes, numEdges; /* 图中当前的顶点数和边数  */
}MGraph;

/* 建立无向网图的邻接矩阵表示 */
void CreateMGraph(MGraph *G){
	int i,j,k,w;
	printf("输入顶点数和边数:\n");
	scanf("%d,%d",&G->numNodes,&G->numEdges); /* 输入顶点数和边数 */
	for(i = 0;i <G->numNodes;i++) /* 读入顶点信息,建立顶点表 */
		scanf(&G->vexs[i]);
	for(i = 0;i <G->numNodes;i++)
		for(j = 0;j <G->numNodes;j++)
			G->arc[i][j]=INFINITY;	/* 邻接矩阵初始化 */
	for(k = 0;k <G->numEdges;k++) /* 读入numEdges条边，建立邻接矩阵 */
	{
		printf("输入边(vi,vj)上的下标i，下标j和权w:\n");
		scanf("%d,%d,%d",&i,&j,&w); /* 输入边(vi,vj)上的权w */
		G->arc[i][j]=w; 
		G->arc[j][i]= G->arc[i][j]; /* 因为是无向图，矩阵对称 */
	}
}
/* 显示无向图的详情 */
void displayGraph(MGraph *graph){
	int i,j;
	printf("顶点数:%d,边数:%d\n",graph->numNodes,graph->numEdges);
	for(i=0;i<graph->numNodes;i++){
			printf("顶点:%d\n",i);
			printf("边:");
			for(j=0;j<graph->numNodes;j++){	  
					if(graph->arc[i][j]!=INFINITY){
							printf("%d-%d,",i,j);
						}
				}
			printf("\n");					
		}
	printf("无向图去除重复边:\n");
	for(i=0;i<graph->numNodes;i++){
			//printf("顶点:%d\n",i);
			//printf("边:");
			for(j=0;j<i;j++){	  
					if(graph->arc[i][j]!=INFINITY){
							printf("%d-%d,",i,j);
						}
				}
			//printf("\n");					
		}
		printf("\n");		
}


/* 建立有向网图的邻接矩阵表示 */
void CreateDirMGraph(MGraph *G){
	int i,j,k,w;
	printf("输入顶点数和弧数:\n");
	scanf("%d,%d",&G->numNodes,&G->numEdges); /* 输入顶点数和弧数 */
	for(i = 0;i <G->numNodes;i++) /* 读入顶点信息,建立顶点表 */
		scanf(&G->vexs[i]);
	for(i = 0;i <G->numNodes;i++)
		for(j = 0;j <G->numNodes;j++)
			G->arc[i][j]=0;	/* 邻接矩阵初始化 */
	for(k = 0;k <G->numEdges;k++) /* 读入numEdges条边，建立邻接矩阵 */
	{
		printf("输入边(vi,vj)上的下标i，下标j:\n");
		scanf("%d,%d",&i,&j); /* 输入弧的开始与结束下标 */
		G->arc[i][j]=1; 
	}
}

/* 显示有向图的详情 */
void displayDirGraph(MGraph *graph){
	int i,j;
	int outDegree=0,inDegree=0;
	printf("顶点数:%d,弧数:%d\n",graph->numNodes,graph->numEdges);
	for(i=0;i<graph->numNodes;i++){
			printf("顶点:%d\n",i);
			printf("弧:");
			for(j=0;j<graph->numNodes;j++){	  
					if(graph->arc[i][j]!=0){
							printf("%d->%d,",i,j);
						}
				}
			printf("\n");					
		}
	
	//计算出度
	for(i=0;i<graph->numNodes;i++){
			for(j=0;j<graph->numNodes;j++){
					outDegree = outDegree + graph->arc[i][j];
					//printf("i=%d,j=%d,outDegree=%d",i,j,outDegree);	
				}
			printf("顶点%d,出度为%d\n",i,outDegree);
			outDegree=0;
			j=0;									
		}
	
	//计算入度
	for(j=0;j<graph->numNodes;j++){
			for(i=0;i<graph->numNodes;i++){
					inDegree += graph->arc[i][j];	
				}
			printf("顶点%d,入度为%d\n",j,inDegree);
			inDegree=0;
			i=0;									
		}			
}

void printadjmatrix(MGraph *graph){
		int i=0,j=0;
		for(i=0;i<graph->numNodes;i++){
			for(j=0;j<graph->numNodes;j++){
					printf("%d ",graph->arc[i][j]);	
				}
			printf("\n");										
		}
	
	}

int main(void){    
	MGraph graph;
	printf("请输入图的类型1-有向图 0-无向图:\n");
	scanf("%d",&graphType); /* 设置图的类型 */    
	if(graphType){
			CreateDirMGraph(&graph);
			printf("显示有向图详情如下:\n");
			printadjmatrix(&graph);
			displayDirGraph(&graph);	
		}else{
			CreateMGraph(&graph);	
			printf("显示无向图详情如下:\n");
			printadjmatrix(&graph);
			displayGraph(&graph);	
			}
	
	return 0;
}