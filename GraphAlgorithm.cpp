//
// Created by 徐绍骞 on 2022/5/29.
//
#include "data_structure.h"
#include<queue>
static void doLDFS(LGraph,Datatype);
static void doMDFS(MGraph,Datatype);
static void doLBFS(LGraph,Datatype);
static void doMBFS(MGraph,Datatype);
template<typename T>Datatype FindMinDist(T,GraphEntry);
static void PrintPath(GraphEntry,Datatype);
LGraph LGraphInitialize(LGraph graph,int vnum){
    graph=(LGraph)malloc(sizeof(struct LGraphnode));
    graph->Enum=0,graph->Vnum=vnum;
    graph->graphlist=(Adjacencylist)malloc(vnum*sizeof(struct Adjacencynode));
    graph->visited=(bool*)malloc(sizeof(bool));
    for(int i=0;i<vnum;i++){
        graph->graphlist[i].key=MYINFINITY;
        graph->graphlist[i].firstadjacency=nullptr;
        graph->graphlist[i].indegree=0;
        graph->graphlist[i].index=i;
        graph->visited[i]=false;
    }
    return graph;
}
MGraph MGraphInitialize(MGraph graph,int vnum){
    graph=(MGraph)malloc(sizeof(struct MGraphnode));
    graph->graphmatrix=(Weighttype**)malloc(vnum*sizeof(Weighttype*));
    graph->vertexkey=(Elementype*)malloc(vnum*sizeof(Elementype));
    graph->visited=(bool*)malloc(sizeof(bool));
    for(int i=0;i<vnum;i++){
        graph->graphmatrix[i]=(Weighttype*)malloc(vnum*sizeof(Weighttype));
        for(int j=0;j<vnum;j++)graph->graphmatrix[i][j]=MYINFINITY;
        graph->vertexkey[i]=MYINFINITY;
        graph->visited[i]=false;
    }
    graph->Enum=0,graph->Vnum=vnum;
    return graph;
}
LGraph LGraphInsert(LGraph graph,Edge edge){
    LVertex curvertex=graph->graphlist[edge->v1.vname].firstadjacency,prevertex=curvertex;
    if(!curvertex){
        graph->graphlist[edge->v1.vname].firstadjacency=(LVertex)malloc(sizeof(struct LGraphnode));
        graph->graphlist[edge->v1.vname].firstadjacency->vname=edge->v2.vname;
        graph->graphlist[edge->v1.vname].firstadjacency->key=edge->v2.key;
        graph->graphlist[edge->v1.vname].firstadjacency->weight=edge->weight;
        graph->graphlist[edge->v1.vname].firstadjacency->next=nullptr;
    }else{
        while(curvertex){
            prevertex=curvertex;
            curvertex=curvertex->next;
        }
        curvertex=(LVertex)malloc(sizeof(struct LGraphnode));
        curvertex->vname=edge->v2.vname;
        curvertex->key=edge->v2.key;
        curvertex->weight=edge->weight;
        prevertex->next=curvertex,curvertex->next=nullptr;
    }
    if(graph->graphlist[edge->v1.vname].key==MYINFINITY)
        graph->graphlist[edge->v1.vname].key=edge->v1.key;
    if(graph->graphlist[edge->v2.vname].key==MYINFINITY)
        graph->graphlist[edge->v2.vname].key=edge->v2.key;
    graph->graphlist[edge->v2.vname].indegree++;
    graph->Enum++;
    return graph;
}
MGraph MGraphInsert(MGraph graph,Edge edge){
    graph->graphmatrix[edge->v1.vname][edge->v2.vname]=edge->weight;
    if(graph->vertexkey[edge->v1.vname]==MYINFINITY)
        graph->vertexkey[edge->v1.vname]=edge->v1.key;
    if(graph->vertexkey[edge->v2.vname]==MYINFINITY)
        graph->vertexkey[edge->v2.vname]=edge->v2.key;
    graph->Enum++;
    return graph;
}
void LGraphDFS(LGraph graph){
    for(int i=0;i<graph->Vnum;i++)
        if(!graph->visited[i]){
            doLDFS(graph,i);
            printf("\n");
        }
    for(int i=0;i<graph->Vnum;i++)graph->visited[i]=false;
}
void doLDFS(LGraph graph,Datatype vname){
    graph->visited[vname]=true;
    printf("%d:%d ",vname,graph->graphlist[vname].key);
    for(LVertex vn=graph->graphlist[vname].firstadjacency;vn;vn=vn->next)
        if(!graph->visited[vn->vname])doLDFS(graph,vn->vname);
}
void MGraphDFS(MGraph graph){
    for(int i=0;i<graph->Vnum;i++)
        if(!graph->visited[i]){
            doMDFS(graph,i);
            printf("\n");
        }
    for(int i=0;i<graph->Vnum;i++)graph->visited[i]=false;
}
void doMDFS(MGraph graph,Datatype vname){
    graph->visited[vname]=true;
    printf("%d:%d ",vname,graph->vertexkey[vname]);
    for(int i=0;i<graph->Vnum;i++)
        if(graph->graphmatrix[vname][i]!=MYINFINITY&&!graph->visited[i])
            doMDFS(graph,i);
}
void LGraphBFS(LGraph graph){
    for(int i=0;i<graph->Vnum;i++)
        if(!graph->visited[i]){
            doLBFS(graph,i);
            printf("\n");
        }
    for(int i=0;i<graph->Vnum;i++)graph->visited[i]=false;
}
void doLBFS(LGraph graph,Datatype vname){
    std::queue<struct Adjacencynode>vertexque;
    LVertex curvertex;
    vertexque.push(graph->graphlist[vname]);
    while(!vertexque.empty()){
        curvertex=vertexque.front().firstadjacency;
        while(curvertex){
            if(!graph->visited[curvertex->vname]){
                vertexque.push(graph->graphlist[curvertex->vname]);
                graph->visited[graph->graphlist[curvertex->vname].index]=true;
            }
            curvertex=curvertex->next;
        }
        printf("%d:%d ",vertexque.front().index,vertexque.front().key);
        vertexque.pop();
    }
}
void MGraphBFS(MGraph graph){
    for(int i=0;i<graph->Vnum;i++)
        if(!graph->visited[i]){
            doMBFS(graph,i);
            printf("\n");
        }
    for(int i=0;i<graph->Vnum;i++)graph->visited[i]=false;
}
void doMBFS(MGraph graph,Datatype vname){
    std::queue<int>vertexque;
    vertexque.push(vname);
    while(!vertexque.empty()){
        for(int i=0;i<graph->Vnum;i++)
            if(graph->graphmatrix[vertexque.front()][i]!=MYINFINITY&&!graph->visited[i]){
                vertexque.push(i);
                graph->visited[i]=true;
            }
        printf("%d:%d ",vertexque.front(),graph->vertexkey[vertexque.front()]);
        vertexque.pop();
    }
}
Datatype*LGraphTopSort(LGraph graph,Datatype*topsortlist,int sortnum){
    int vertexindegree[graph->Vnum],topnum=0;
    LVertex curptr;
    std::queue<Datatype>topque;
    memset(vertexindegree,0,sizeof(vertexindegree));
    for(int i=0;i<graph->Vnum;i++)vertexindegree[i]=graph->graphlist[i].indegree;
    for(int i=0;i<graph->Vnum;i++)if(!vertexindegree[i]&&graph->graphlist[i].key!=MYINFINITY){
            topque.push(i);
            vertexindegree[i]--;
    }
    while(!topque.empty()){
        topsortlist[topnum++]=topque.front();
        curptr=graph->graphlist[topque.front()].firstadjacency;
        while(curptr){
            if(!--vertexindegree[curptr->vname])topque.push(curptr->vname);
            curptr=curptr->next;
        }
        topque.pop();
    }
    if(sortnum>topnum)printf("无法完成拓扑排序：图中存在环\n");
    return topsortlist;
}
GraphEntry EntryInitialize(GraphEntry entry,int vnum){
    entry=(GraphEntry)malloc(sizeof(struct Entrynode));
    entry->Vnum=vnum;
    entry->dist=(Weighttype*)malloc(entry->Vnum*sizeof(Weighttype));
    entry->path=(Vertex*)malloc(entry->Vnum*sizeof(Vertex));
    for(int i=0;i<entry->Vnum;i++){
        entry->dist[i]=MYINFINITY;
        entry->path[i].vname=-1,entry->path->key=MYINFINITY;
    }
    return entry;
}
GraphEntry LGraphDijkstra(LGraph graph,GraphEntry entry,Datatype origin){
    entry->dist[origin]=0,entry->path[origin].key=graph->graphlist[origin].key;
    Datatype curvname;
    LVertex curptr;
    while(true){
        curvname=FindMinDist(graph,entry);
        if(curvname<0)break;
        graph->visited[curvname]=true;
        curptr=graph->graphlist[curvname].firstadjacency;
        while(curptr){
            if(!graph->visited[curptr->vname]&&entry->dist[curptr->vname]>entry->dist[curvname]+curptr->weight){
                entry->dist[curptr->vname]=entry->dist[curvname]+curptr->weight;
                entry->path[curptr->vname].vname=curvname;
                entry->path[curptr->vname].key=graph->graphlist[curvname].key;
            }
            curptr=curptr->next;
        }
    }
    for(int i=0;i<entry->Vnum;i++){
        printf("%d: ",entry->dist[i]);
        PrintPath(entry,i);
        printf("%d:%d",graph->graphlist[i].index,graph->graphlist[i].key);
        printf("\n");
    }
    for(int i=0;i<graph->Vnum;i++){
        graph->visited[i]=false;
        entry->dist[i]=MYINFINITY;
        entry->path[i].vname=-1,entry->path[i].key=MYINFINITY;
    }
    return entry;
}
GraphEntry MGraphDijkstra(MGraph graph,GraphEntry entry,Datatype origin){
    entry->dist[origin]=0,entry->path[origin].key=graph->vertexkey[origin];
    Datatype curvertex;
    while(true){
        curvertex=FindMinDist(graph,entry);
        if(curvertex<0)break;
        graph->visited[curvertex]=true;
        for(int i=0;i<graph->Vnum;i++)
            if(entry->dist[i]>entry->dist[curvertex]+graph->graphmatrix[curvertex][i]&&!graph->visited[i]){
                entry->dist[i]=entry->dist[curvertex]+graph->graphmatrix[curvertex][i];
                entry->path[i].vname=curvertex;
                entry->path[i].key=graph->vertexkey[curvertex];
            }
    }
    for(int i=0;i<entry->Vnum;i++){
        printf("%d: ",entry->dist[i]);
        PrintPath(entry,i);
        printf("%d:%d",i,graph->vertexkey[i]);
        printf("\n");
    }
    for(int i=0;i<graph->Vnum;i++){
        graph->visited[i]=false;
        entry->dist[i]=MYINFINITY;
        entry->path[i].vname=-1,entry->path[i].key=MYINFINITY;
    }
    return entry;
}
template<typename T>Datatype FindMinDist(T graph,GraphEntry entry){
    Weighttype mindist=MYINFINITY;
    Datatype minvertexname=-1;
    for(int i=0;i<entry->Vnum;i++)if(mindist>entry->dist[i]&&!graph->visited[i])
            mindist=entry->dist[i],minvertexname=i;
    return minvertexname;
}
void PrintPath(GraphEntry entry,Datatype destination){
    Vertex next=entry->path[destination];
    if(next.vname>0){
        PrintPath(entry,next.vname);
        printf("%d:%d->",next.vname,next.key);
    }
}