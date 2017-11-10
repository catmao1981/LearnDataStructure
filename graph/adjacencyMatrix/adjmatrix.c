#include<stdio.h>    
#include<stdlib.h>   
#include<io.h>  
#include<math.h>  
#include<time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXVEX 100 /* ��󶥵�����Ӧ���û����� */
#define INFINITY 65535 /*ģ�������*/

typedef int GraphType;	/* GraphTypeͼ������1-����ͼ 0-����ͼ*/
typedef char VertexType; /* ��������Ӧ���û�����  */
typedef int EdgeType; /* ���ϵ�Ȩֵ����Ӧ���û����� */
//ͼ������
GraphType graphType;
//�ڽӾ������ݽṹ
typedef struct
{
	VertexType vexs[MAXVEX]; /* ����� */
	EdgeType arc[MAXVEX][MAXVEX];/* �ڽӾ��󣬿ɿ����߱� */
	int numNodes, numEdges; /* ͼ�е�ǰ�Ķ������ͱ���  */
}MGraph;

/* ����������ͼ���ڽӾ����ʾ */
void CreateMGraph(MGraph *G){
	int i,j,k,w;
	printf("���붥�����ͱ���:\n");
	scanf("%d,%d",&G->numNodes,&G->numEdges); /* ���붥�����ͱ��� */
	for(i = 0;i <G->numNodes;i++) /* ���붥����Ϣ,��������� */
		scanf(&G->vexs[i]);
	for(i = 0;i <G->numNodes;i++)
		for(j = 0;j <G->numNodes;j++)
			G->arc[i][j]=INFINITY;	/* �ڽӾ����ʼ�� */
	for(k = 0;k <G->numEdges;k++) /* ����numEdges���ߣ������ڽӾ��� */
	{
		printf("�����(vi,vj)�ϵ��±�i���±�j��Ȩw:\n");
		scanf("%d,%d,%d",&i,&j,&w); /* �����(vi,vj)�ϵ�Ȩw */
		G->arc[i][j]=w; 
		G->arc[j][i]= G->arc[i][j]; /* ��Ϊ������ͼ������Գ� */
	}
}
/* ��ʾ����ͼ������ */
void displayGraph(MGraph *graph){
	int i,j;
	printf("������:%d,����:%d\n",graph->numNodes,graph->numEdges);
	for(i=0;i<graph->numNodes;i++){
			printf("����:%d\n",i);
			printf("��:");
			for(j=0;j<graph->numNodes;j++){	  
					if(graph->arc[i][j]!=INFINITY){
							printf("%d-%d,",i,j);
						}
				}
			printf("\n");					
		}
	printf("����ͼȥ���ظ���:\n");
	for(i=0;i<graph->numNodes;i++){
			//printf("����:%d\n",i);
			//printf("��:");
			for(j=0;j<i;j++){	  
					if(graph->arc[i][j]!=INFINITY){
							printf("%d-%d,",i,j);
						}
				}
			//printf("\n");					
		}
		printf("\n");		
}


/* ����������ͼ���ڽӾ����ʾ */
void CreateDirMGraph(MGraph *G){
	int i,j,k,w;
	printf("���붥�����ͻ���:\n");
	scanf("%d,%d",&G->numNodes,&G->numEdges); /* ���붥�����ͻ��� */
	for(i = 0;i <G->numNodes;i++) /* ���붥����Ϣ,��������� */
		scanf(&G->vexs[i]);
	for(i = 0;i <G->numNodes;i++)
		for(j = 0;j <G->numNodes;j++)
			G->arc[i][j]=0;	/* �ڽӾ����ʼ�� */
	for(k = 0;k <G->numEdges;k++) /* ����numEdges���ߣ������ڽӾ��� */
	{
		printf("�����(vi,vj)�ϵ��±�i���±�j:\n");
		scanf("%d,%d",&i,&j); /* ���뻡�Ŀ�ʼ������±� */
		G->arc[i][j]=1; 
	}
}

/* ��ʾ����ͼ������ */
void displayDirGraph(MGraph *graph){
	int i,j;
	int outDegree=0,inDegree=0;
	printf("������:%d,����:%d\n",graph->numNodes,graph->numEdges);
	for(i=0;i<graph->numNodes;i++){
			printf("����:%d\n",i);
			printf("��:");
			for(j=0;j<graph->numNodes;j++){	  
					if(graph->arc[i][j]!=0){
							printf("%d->%d,",i,j);
						}
				}
			printf("\n");					
		}
	
	//�������
	for(i=0;i<graph->numNodes;i++){
			for(j=0;j<graph->numNodes;j++){
					outDegree = outDegree + graph->arc[i][j];
					//printf("i=%d,j=%d,outDegree=%d",i,j,outDegree);	
				}
			printf("����%d,����Ϊ%d\n",i,outDegree);
			outDegree=0;
			j=0;									
		}
	
	//�������
	for(j=0;j<graph->numNodes;j++){
			for(i=0;i<graph->numNodes;i++){
					inDegree += graph->arc[i][j];	
				}
			printf("����%d,���Ϊ%d\n",j,inDegree);
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
	printf("������ͼ������1-����ͼ 0-����ͼ:\n");
	scanf("%d",&graphType); /* ����ͼ������ */    
	if(graphType){
			CreateDirMGraph(&graph);
			printf("��ʾ����ͼ��������:\n");
			printadjmatrix(&graph);
			displayDirGraph(&graph);	
		}else{
			CreateMGraph(&graph);	
			printf("��ʾ����ͼ��������:\n");
			printadjmatrix(&graph);
			displayGraph(&graph);	
			}
	
	return 0;
}