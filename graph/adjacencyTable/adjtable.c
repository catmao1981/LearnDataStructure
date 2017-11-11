#include<stdio.h>    
#include<stdlib.h>   
#include<io.h>  
#include<math.h>  
#include<time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXVEX 100 /* ��󶥵���,Ӧ���û����� */

typedef int Status;	/* Status�Ǻ���������,��ֵ�Ǻ������״̬����,��OK�� */
typedef char VertexType; /* ��������Ӧ���û����� */
typedef int EdgeType; /* ���ϵ�Ȩֵ����Ӧ���û����� */
typedef int GraphType;	/* GraphTypeͼ������1-����ͼ 0-����ͼ*/

//ͼ������
GraphType graphType;

typedef struct EdgeNode /* �߱���  */
{
	int adjvex;    /* �ڽӵ���,�洢�ö����Ӧ���±� */
	EdgeType info;		/* ���ڴ洢Ȩֵ,���ڷ���ͼ���Բ���Ҫ */
	struct EdgeNode *next; /* ����,ָ����һ���ڽӵ� */
}EdgeNode;

typedef struct VertexNode /* ������� */
{
	VertexType data; /* ������,�洢������Ϣ */
	EdgeNode *firstedge;/* �߱�ͷָ�� */
}VertexNode, AdjList[MAXVEX];

typedef struct{
	AdjList adjList; 
	int numNodes,numEdges; /* ͼ�е�ǰ�������ͱ��� */
}GraphAdjList;

/* ����ͼ���ڽӱ�ṹ */
void  CreateALGraph(GraphAdjList *G){
	int i,j,k;
	EdgeNode *e;
	printf("���붥�����ͱ���:\n");
	scanf("%d,%d",&G->numNodes,&G->numEdges); 
	
	printf("���붥����Ϣ\n");
	
	for(i = 0;i < G->numNodes;i++) /* ���붥����Ϣ,��������� */
	{
		scanf("%d",&(G->adjList[i].data)); 	/* ���붥����Ϣ */
		G->adjList[i].firstedge=NULL; 	/* ���߱���Ϊ�ձ� */
	}
	
	for(k = 0;k < G->numEdges;k++)/* �����߱� */
	{
		printf("�����(vi,vj)�ϵĶ������:\n");
		scanf("%d,%d",&i,&j); /* �����(vi,vj)�ϵĶ������ */
		e=(EdgeNode *)malloc(sizeof(EdgeNode)); /* ���ڴ�����ռ�,���ɱ߱��� */
		e->adjvex=j;					/* �ڽ����Ϊj */                         
		e->next=G->adjList[i].firstedge;	/* ��������ͷ�巨:��e��ָ��ָ��ǰ������ָ��Ľ�� */
		G->adjList[i].firstedge=e;		/* ����ǰ�����ָ��ָ��e */               
		
		//���������,�������ڵ㶼Ҫ���в���
		e=(EdgeNode *)malloc(sizeof(EdgeNode)); /* ���ڴ�����ռ�,���ɱ߱��� */
		e->adjvex=i;					/* �ڽ����Ϊi */                         
		e->next=G->adjList[j].firstedge;	/* ��e��ָ��ָ��ǰ������ָ��Ľ�� */
		G->adjList[j].firstedge=e;		/* ����ǰ�����ָ��ָ��e */               
	}
	
}

/* ��ʾ����ͼ������ */
void displayGraph(GraphAdjList *graph){
	int i,j,edge;
	printf("������:%d,����:%d\n",graph->numNodes,graph->numEdges);
	for(i=0;i<graph->numNodes;i++){
			printf("����:%d\n",graph->adjList[i].data);
			printf("��:");
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

/* ��������ͼ���ڽӱ�ṹ */
void  CreateDirALGraph(GraphAdjList *G){
	int i,j,k;
	EdgeNode *e;
	printf("���붥�����ͻ���:\n");
	scanf("%d,%d",&G->numNodes,&G->numEdges); 
	
	printf("���붥����Ϣ\n");
	
	for(i = 0;i < G->numNodes;i++) /* ���붥����Ϣ,��������� */
	{
		scanf("%d",&(G->adjList[i].data)); 	/* ���붥����Ϣ */
		G->adjList[i].firstedge=NULL; 	/* ���߱���Ϊ�ձ� */
	}
	
	for(k = 0;k < G->numEdges;k++)/* �����߱� */
	{
		printf("���뻡<vi,vj>�ϵĶ������:\n");
		scanf("%d,%d",&i,&j); /* �����(vi,vj)�ϵĶ������ */
		e=(EdgeNode *)malloc(sizeof(EdgeNode)); /* ���ڴ�����ռ�,���ɱ߱��� */
		e->adjvex=j;					/* �ڽ����Ϊj */                         
		e->next=G->adjList[i].firstedge;	/* ��������ͷ�巨:��e��ָ��ָ��ǰ������ָ��Ľ�� */
		G->adjList[i].firstedge=e;		/* ����ǰ�����ָ��ָ��e */                              
	}
	
}


int main(void){    
	GraphAdjList G;
	printf("������ͼ������1-����ͼ 0-����ͼ:\n");
	scanf("%d",&graphType); /* ����ͼ������ */    
	if(graphType){
			CreateDirALGraph(&G);
			printf("��ʾ����ͼ��������:\n");
			displayGraph(&G);
		}else{
			CreateALGraph(&G);
			printf("��ʾ����ͼ��������:\n");
			displayGraph(&G);		
			}
	
	
	return 0;
}

