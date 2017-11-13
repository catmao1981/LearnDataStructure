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

typedef struct ArcNode//弧节点  
{  
    int tailIndex;//弧尾位置  
    int headIndex;//弧头位置  
    struct ArcNode *tailNext;//下一个弧尾相同的弧  
    struct ArcNode *headNext;//下一个弧头相同的弧  
}ArcNode;  
  
typedef struct VNode  
{  
    int vexName;//顶点名称  
    ArcNode * firstIn;  
    ArcNode * firstOut;  
}GraphList[MAXVEX];//  
  
typedef struct GraphOrth  
{  
    GraphList glist;//顶点数组.  
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


/* 建立图的十字链表结构 */
void  CreateOrthGraph(GraphOrth *G)
{
	  printf("输入图的顶点数和弧数\n");  
    scanf("%d,%d",&G->vexNum,&G->arcNum);    
    //构造顶点集    
    printf("请输入顶点集\n");
    //初始化各个链表集    
    for (int i = 0; i < G->vexNum; i++){    
        int name;  
        scanf("%d",&name);  
        G->glist[i].vexName = name;
        //此处构造一个空的ArcNode  
        G->glist[i].firstIn = G->glist[i].firstOut = getHeadNode();//初始化指向为空  
    }    
        
    printf("请输入顶点的关系\n");    
    for (int i = 0; i < G->arcNum; i++){    
        int vex1,vex2;  
        scanf("%d,%d",&vex1,&vex2);    
        //int location1 = vexLocation(*g,vex1);  
        //int location2 = vexLocation(*g,vex2);  
        ArcNode * pNode = getArcNode(vex1,vex2);  
        pNode->tailNext = G->glist[vex1].firstOut->tailNext; //采用头插法插入 
        G->glist[vex1].firstOut->tailNext = pNode;  
        pNode->headNext = G->glist[vex2].firstIn->headNext;  //采用头插法插入
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

/* 显示有向图的详情 */
void displayGraph(GraphOrth *graph){
	int i,j,arcHead,arcTail;
	printf("顶点数:%d,弧数:%d\n",graph->vexNum,graph->arcNum);
	for(i=0;i<graph->vexNum;i++){
			printf("顶点:%d\n",graph->glist[i].vexName);
			printf("弧信息:\n");
			printf("入度:");
			//firstIn与firstOut不会为空，会指向头结点信息为空的arcNode
			//打印head相关的入度链表
			ArcNode *arcNode = graph->glist[i].firstIn;
			while(arcNode != NULL){
					if(arcNode->headIndex==65535){//如果是头结点，则跳过
							arcNode = arcNode->headNext;
							continue;
						}
					arcHead = arcNode->headIndex;
					arcTail = arcNode->tailIndex;
					printf("%d->%d,",arcTail,arcHead);
					arcNode = arcNode->headNext;		
				}
			printf("\n");
			printf("出度:");	
			//打印tail相关的出度链表	
			arcNode = graph->glist[i].firstOut;
			while(arcNode!= NULL){
					if(arcNode->tailIndex==65535){//如果是头结点，则跳过
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