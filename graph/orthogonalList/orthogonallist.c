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

typedef struct ArcNode//���ڵ�  
{  
    int tailIndex;//��βλ��  
    int headIndex;//��ͷλ��  
    struct ArcNode *tailNext;//��һ����β��ͬ�Ļ�  
    struct ArcNode *headNext;//��һ����ͷ��ͬ�Ļ�  
}ArcNode;  
  
typedef struct VNode  
{  
    int vexName;//��������  
    ArcNode * firstIn;  
    ArcNode * firstOut;  
}GraphList[MAXVEX];//  
  
typedef struct GraphOrth  
{  
    GraphList glist;//��������.  
    int vexNum,arcNum;  
}GraphOrth;

ArcNode * getHeadNode(){  
    ArcNode * pNode = (ArcNode *)malloc(sizeof(ArcNode));  
    if (pNode){  
        pNode->headIndex = pNode->tailIndex = 65535;  
        pNode->headNext = pNode->tailNext = NULL;  
    }  
    return pNode;  
}

ArcNode * getArcNode(int tailIndex,int headIndex){  
    ArcNode * pNode = getHeadNode();  
    if (pNode){  
        pNode->headIndex = headIndex;  
        pNode->tailIndex = tailIndex;  
    }  
    return pNode;  
}


/* ����ͼ��ʮ������ṹ */
void  CreateOrthGraph(GraphOrth *G)
{
	  printf("����ͼ�Ķ������ͻ���\n");  
    scanf("%d,%d",&G->vexNum,&G->arcNum);    
    //���춥�㼯    
    printf("�����붥�㼯\n");
    //��ʼ����������    
    for (int i = 0; i < G->vexNum; i++){    
        int name;  
        scanf("%d",&name);  
        G->glist[i].vexName = name;
        //�˴�����һ���յ�ArcNode  
        G->glist[i].firstIn = G->glist[i].firstOut = getHeadNode();//��ʼ��ָ��Ϊ��  
    }    
        
    printf("�����붥��Ĺ�ϵ\n");    
    for (int i = 0; i < G->arcNum; i++){    
        int vex1,vex2;  
        scanf("%d,%d",&vex1,&vex2);    
        //int location1 = vexLocation(*g,vex1);  
        //int location2 = vexLocation(*g,vex2);  
        ArcNode * pNode = getArcNode(vex1,vex2);  
        pNode->tailNext = G->glist[vex1].firstOut->tailNext; //����ͷ�巨���� 
        G->glist[vex1].firstOut->tailNext = pNode;  
        pNode->headNext = G->glist[vex2].firstIn->headNext;  //����ͷ�巨����
        G->glist[vex2].firstIn->headNext = pNode;
        printf("tailIndex=%d,headIndex=%d\n",pNode->tailIndex,pNode->headIndex);
        
        //test
        /*ArcNode *testOut = G->glist[vex1].firstOut;
        while(testOut!=NULL){
        		printf("Out:%d,",testOut->tailIndex);
        		testOut = testOut->tailNext;
        	}
        printf("\n");	
        ArcNode *testIn = G->glist[vex2].firstIn;
        while(testIn!=NULL){
        		printf("Out:%d,",testOut->headIndex);
        		testIn = testIn->headNext;
        	}
        printf("\n");*/		  
    }    
}

/* ��ʾ����ͼ������ */
void displayGraph(GraphOrth *graph){
	int i,j,arcHead,arcTail;
	printf("������:%d,����:%d\n",graph->vexNum,graph->arcNum);
	for(i=0;i<graph->vexNum;i++){
			printf("����:%d\n",graph->glist[i].vexName);
			printf("����Ϣ:\n");
			printf("���:");
			//firstIn��firstOut����Ϊ�գ���ָ��ͷ�����ϢΪ�յ�arcNode
			//��ӡhead��ص��������
			ArcNode *arcNode = graph->glist[i].firstIn;
			while(arcNode != NULL){
					if(arcNode->headIndex==65535){//�����ͷ��㣬������
							arcNode = arcNode->headNext;
							continue;
						}
					arcHead = arcNode->headIndex;
					arcTail = arcNode->tailIndex;
					printf("%d->%d,",arcTail,arcHead);
					arcNode = arcNode->headNext;		
				}
			printf("\n");
			printf("����:");	
			//��ӡtail��صĳ�������	
			arcNode = graph->glist[i].firstOut;
			while(arcNode!= NULL){
					if(arcNode->tailIndex==65535){//�����ͷ��㣬������
							arcNode = arcNode->tailNext;
							continue;
						}
					arcHead = arcNode->headIndex;
					arcTail = arcNode->tailIndex;
					printf("%d<-%d,",arcHead,arcTail);
					arcNode = arcNode->tailNext;		
				}	
			printf("\n");					
		}		
}

int main(void)
{    
	GraphOrth G;    
	CreateOrthGraph(&G);
	displayGraph(&G);
	return 0;
}