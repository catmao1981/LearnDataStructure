#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 20

//顶点数据类型
typedef int VertexType;

typedef enum {unvisited,isvisited}VisitIf;

//图的种类:无向图/网
typedef enum {UDG,UDN}GraphKind;

typedef struct EdgeNode {
	VisitIf mark;	//访问标记
	int ivex;	//边顶点一
	int jvex;	//边顶点二
	struct EdgeNode *ilink;	//指向依附于顶点一的下一条边,类似于起点相同的一条弧
	struct EdgeNode *jlink;	//指向依附于顶点二的下一条边,类似与终点想同的一条弧
	int weight;	//边的权值
}EdgeNode;


typedef struct VexNode {
	VertexType data;
	EdgeNode *firstedge;	//指向第一条依附于该顶点的边
}VexNode;

typedef struct {
	VexNode adjmulist[MAX_VERTEX_NUM];
	int vexnum;	//图的顶点数
	int edgenum;	//图的边数
	//GraphKind kind; //图的种类
}AMLGraph;


/*
* @description:创建图(无向图/网)
*/
void CreateGraph(AMLGraph *G) {
	int i,j,k,w;
	VertexType va,vb;
	EdgeNode *eNode;

	//确定图的顶点和边数
	printf("please enter vexnum and edgenum:");
	scanf("%d,%d",&(*G).vexnum,&(*G).edgenum);

	//确定图的各个顶点
	printf("please enter each value of graph:");
	for(i = 0; i < (*G).vexnum ; i++)  {
		scanf("%d,",&(*G).adjmulist[i].data);
		(*G).adjmulist[i].firstedge = NULL;
	}
	
	//确定各个顶点间关系，即建立边
	/*if((*G).kind == UDG)
		printf("please enter heads and tails:\n");
	else 
		printf("please enter heads,weights and tails\n");*/
	
	printf("please enter heads and tails:\n");
	
	for(k = 0; k < (*G).edgenum ;k++) {
		/*if((*G).kind == UDG)
			scanf("%d,%d",&va,&vb);
		else 
			scanf("%d,%d",&va,&vb,&w);*/
		
		scanf("%d,%d",&va,&vb);	
		//放回两顶点在顶点向量数组中位置
		//i = LocateVex(*G,va);
		//j = LocateVex(*G,vb);
		i = va;
		j = vb;
		//if(i < 0 || j < 0)
		//	return ERROR;

		eNode = (EdgeNode *) malloc(sizeof(struct EdgeNode));
		//if(!eNode)
		//	exit(OVERFLOW);

		///建立新节点
		eNode->ivex = i;
		eNode->jvex = j;
		eNode->mark = unvisited;
		//注意每次插入新节点都是在链表的表头进行
		eNode->ilink = (*G).adjmulist[i].firstedge;
		//此处将jlink进行更新，可以看出是更新的adjmulist[j]结点，目前的理解是查找不能直接根据jlink进行查找，应该根据元素的位置
		//来决定调用的到底是ilink,还是jlink
		eNode->jlink = (*G).adjmulist[j].firstedge;
		(*G).adjmulist[i].firstedge = eNode;
		(*G).adjmulist[j].firstedge = eNode;
		//if((*G).kind == UDN)
		//	p->weight = w;
	}
}

void displayGraph(AMLGraph *graph){
	int i,j,edgeHead,edgeTail;
	printf("顶点数:%d,边数:%d\n",graph->vexnum,graph->edgenum);
	for(i=0;i<graph->vexnum;i++){
			printf("顶点:%d\n",graph->adjmulist[i].data);
			printf("边信息:\n");

			EdgeNode *edgeNode = graph->adjmulist[i].firstedge;
			while(edgeNode != NULL){
					edgeHead = edgeNode->ivex;
					edgeTail = edgeNode->jvex;
					printf("%d-%d,",edgeHead,edgeTail);
					if(edgeHead==graph->adjmulist[i].data){
							edgeNode = edgeNode->ilink;		
						}else{
								edgeNode = edgeNode->jlink;
							}			
				}
			printf("\n");					
		}		
}

int main(void){    
	AMLGraph G;
	CreateGraph(&G);
	displayGraph(&G);
	return 0;
}