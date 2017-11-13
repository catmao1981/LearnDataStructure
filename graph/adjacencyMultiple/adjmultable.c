#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 20

//������������
typedef int VertexType;

typedef enum {unvisited,isvisited}VisitIf;

//ͼ������:����ͼ/��
typedef enum {UDG,UDN}GraphKind;

typedef struct EdgeNode {
	VisitIf mark;	//���ʱ��
	int ivex;	//�߶���һ
	int jvex;	//�߶����
	struct EdgeNode *ilink;	//ָ�������ڶ���һ����һ����,�����������ͬ��һ����
	struct EdgeNode *jlink;	//ָ�������ڶ��������һ����,�������յ���ͬ��һ����
	int weight;	//�ߵ�Ȩֵ
}EdgeNode;


typedef struct VexNode {
	VertexType data;
	EdgeNode *firstedge;	//ָ���һ�������ڸö���ı�
}VexNode;

typedef struct {
	VexNode adjmulist[MAX_VERTEX_NUM];
	int vexnum;	//ͼ�Ķ�����
	int edgenum;	//ͼ�ı���
	//GraphKind kind; //ͼ������
}AMLGraph;


/*
* @description:����ͼ(����ͼ/��)
*/
void CreateGraph(AMLGraph *G) {
	int i,j,k,w;
	VertexType va,vb;
	EdgeNode *eNode;

	//ȷ��ͼ�Ķ���ͱ���
	printf("please enter vexnum and edgenum:");
	scanf("%d,%d",&(*G).vexnum,&(*G).edgenum);

	//ȷ��ͼ�ĸ�������
	printf("please enter each value of graph:");
	for(i = 0; i < (*G).vexnum ; i++)  {
		scanf("%d,",&(*G).adjmulist[i].data);
		(*G).adjmulist[i].firstedge = NULL;
	}
	
	//ȷ������������ϵ����������
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
		//�Ż��������ڶ�������������λ��
		//i = LocateVex(*G,va);
		//j = LocateVex(*G,vb);
		i = va;
		j = vb;
		//if(i < 0 || j < 0)
		//	return ERROR;

		eNode = (EdgeNode *) malloc(sizeof(struct EdgeNode));
		//if(!eNode)
		//	exit(OVERFLOW);

		///�����½ڵ�
		eNode->ivex = i;
		eNode->jvex = j;
		eNode->mark = unvisited;
		//ע��ÿ�β����½ڵ㶼��������ı�ͷ����
		eNode->ilink = (*G).adjmulist[i].firstedge;
		//�˴���jlink���и��£����Կ����Ǹ��µ�adjmulist[j]��㣬Ŀǰ������ǲ��Ҳ���ֱ�Ӹ���jlink���в��ң�Ӧ�ø���Ԫ�ص�λ��
		//���������õĵ�����ilink,����jlink
		eNode->jlink = (*G).adjmulist[j].firstedge;
		(*G).adjmulist[i].firstedge = eNode;
		(*G).adjmulist[j].firstedge = eNode;
		//if((*G).kind == UDN)
		//	p->weight = w;
	}
}

void displayGraph(AMLGraph *graph){
	int i,j,edgeHead,edgeTail;
	printf("������:%d,����:%d\n",graph->vexnum,graph->edgenum);
	for(i=0;i<graph->vexnum;i++){
			printf("����:%d\n",graph->adjmulist[i].data);
			printf("����Ϣ:\n");

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