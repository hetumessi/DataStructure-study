#include"data_structure.h"
#include<ctime>
int main(){
    clock_t start=clock(),end;
    int testnum=10,testdata1[testnum],testdata2[testnum*testnum];
    int vnum=10,ednum=12,sortnum=7;
    Datatype topsortlist[vnum];
    memset(topsortlist,0,sizeof(topsortlist));
    Edge e=(Edge)malloc(sizeof(struct Enode));
    srand(time(nullptr));
    for(int i=0;i<testnum;i++)testdata1[i]=rand()%100;
    for(int i=0;i<testnum*testnum;i++)testdata2[i]=rand()%200;
    for(int i=0;i<ednum;i++)printf("%d ",testdata2[i]);
    printf("\n");
    LGraph lgraph=nullptr;
    MGraph mgraph=nullptr;
    lgraph=LGraphInitialize(lgraph,vnum);
    mgraph=MGraphInitialize(mgraph,vnum);
    for(int i=0;i<ednum;i++){
        scanf("%d %d",&e->v1.vname,&e->v2.vname);
        e->weight=testdata2[i];
        e->v1.key=testdata1[i],e->v2.key=testdata1[(i+1)%testnum];
        LGraphInsert(lgraph,e);
        MGraphInsert(mgraph,e);
    }
    printf("\n");
    LVertex curvertex;
    for(int i=0;i<lgraph->Vnum;i++){
        curvertex=lgraph->graphlist[i].firstadjacency;
        while(curvertex){
            printf("%d ",curvertex->weight);
            curvertex=curvertex->next;
        }
    }
    printf("\n");
    LGraphDFS(lgraph);
    MGraphDFS(mgraph);
    LGraphBFS(lgraph);
    MGraphBFS(mgraph);
    LGraphTopSort(lgraph,topsortlist,sortnum);
    for(int i=0;i<lgraph->Vnum;i++)printf("%d ",topsortlist[i]);
    printf("\n");
    GraphEntry entry=nullptr;
    entry=EntryInitialize(entry,lgraph->Vnum);
    LGraphDijkstra(lgraph,entry,1);
    printf("\n");
    MGraphDijkstra(mgraph,entry,2);
    for(int i=0;i<mgraph->Vnum;i++)printf("%d ",mgraph->vertexkey[i]);
    end=clock();
    printf("耗时：%lf 秒",(double)(end-start)/CLOCKS_PER_SEC);
    return 0;
}