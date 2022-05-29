//
// Created by 徐绍骞 on 2022/5/29.
//
#include "data_structure.h"
LGraph LGraphInitialize(LGraph graph,int vnum){
    graph=(LGraph)malloc(sizeof(struct LGraphnode));
    graph->Enum=0,graph->Vnum=vnum;
    graph->graphlist=(Adjacencylist)malloc(vnum*sizeof(struct Adjacencynode));
    for(int i=0;i<vnum;i++){
        graph->graphlist[i].firstadjacency=nullptr;
        graph->graphlist[i].indegree=0;
    }
    return graph;
}
MGraph MGraphInitialize(MGraph graph,int vnum){
    graph=(MGraph)malloc(sizeof(struct MGraphnode));
    graph->graphmatrix=(Weighttype**)malloc(vnum*sizeof(Weighttype*));
    for(int i=0;i<vnum;i++){
        graph->graphmatrix[i]=(Weighttype*)malloc(vnum*sizeof(Weighttype));
        for(int j=0;j<vnum;j++)graph->graphmatrix[i][j]=0;
    }
    graph->vertexkey=(Elementype*)malloc(vnum*sizeof(Elementype));
    for(int i=0;i<vnum;i++)graph->vertexkey[i]=0;
    graph->Enum=0,graph->Vnum=vnum;
    return graph;
}
LGraph LGraphInsert(LGraph graph,Edge edge){
    LVertex curvertex=graph->graphlist[edge->v1.vname].firstadjacency;
    while(curvertex)curvertex=curvertex->next;
    curvertex=(LVertex)malloc(sizeof(struct LGraphnode));
    curvertex->key=edge->v2.key;
    curvertex->weight=edge->weight;
    curvertex->next=nullptr;
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