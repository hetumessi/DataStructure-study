//
// Created by 徐绍骞 on 2022/4/23.
//
#include<vector>
static LBPriorotyQueue DoMerge(LBPriorotyQueue,LBPriorotyQueue);
static LBPriorotyQueue SwapChildren(LBPriorotyQueue);
static LBPriorotyQueue LoadRightChild(LBPriorotyQueue,std::vector<LBPriorotyQueue>);
LBPriorotyQueue LeftistHeapInitialize(LBPriorotyQueue pqueue,Elementype intializevalue,enum MAXORMIN ismin){
    pqueue=(LBPriorotyQueue)malloc(sizeof(struct LeftistHeap));
    pqueue->ismin=ismin;
    pqueue->rightchild=pqueue->leftchild=nullptr;
    pqueue->Npl=0;
    pqueue->value=intializevalue;
    return pqueue;
}
Elementype LeftistHeapGetfront(LBPriorotyQueue pqueue){
    return pqueue->value;
}
bool LeftistHeapIsEmpty(LBPriorotyQueue pqueue){
    return !pqueue;
}
LBPriorotyQueue LeftistHeapMerge_REC(LBPriorotyQueue pqueue1,LBPriorotyQueue pqueue2){
    if(pqueue1->ismin!=pqueue2->ismin){
        printf("无法合并：最小堆和最大堆\n");
        return nullptr;
    }
    if(LeftistHeapIsEmpty(pqueue1))return pqueue2;
    if(LeftistHeapIsEmpty(pqueue2))return pqueue1;
    if(compare(pqueue1->ismin,pqueue1->value,pqueue2->value))
        return DoMerge(pqueue1,pqueue2);
    else return DoMerge(pqueue2,pqueue1);
}
LBPriorotyQueue LeftistHeapMerge_ITE(LBPriorotyQueue pqueue1,LBPriorotyQueue pqueue2){
    if(pqueue1->ismin!=pqueue2->ismin){
        printf("无法合并：最小堆和最大堆\n");
        return nullptr;
    }
    LBPriorotyQueue newroot=compare(pqueue1->ismin,pqueue1->value,pqueue2->value)?
            pqueue1:pqueue2;
    std::vector<LBPriorotyQueue>sortvector;
    while(pqueue1){
        sortvector.push_back(pqueue1);
        pqueue1=pqueue1->rightchild;
    }
    while(pqueue2){}

    return newroot;
}

LBPriorotyQueue DoMerge(LBPriorotyQueue pqueue1,LBPriorotyQueue pqueue2){
    if(LeftistHeapIsEmpty(pqueue1->leftchild))pqueue1->leftchild=pqueue2;
    else{
        pqueue1->rightchild=LeftistHeapMerge_REC(pqueue1->rightchild,pqueue2);
        if(pqueue1->leftchild->Npl<pqueue1->rightchild->Npl)SwapChildren(pqueue1);
        pqueue1->Npl=pqueue1->rightchild->Npl+1;
    }
    return pqueue1;
}
LBPriorotyQueue SwapChildren(LBPriorotyQueue pqueue){
    LBPriorotyQueue tmpnode=pqueue->leftchild;
    pqueue->leftchild=pqueue->rightchild;
    pqueue->rightchild=tmpnode;
    return pqueue;
}
LBPriorotyQueue LeftistHeapInsert(LBPriorotyQueue pqueue,Elementype insertvalue){
    LBPriorotyQueue insertnode=nullptr;
    insertnode=LeftistHeapInitialize(insertnode,insertvalue,pqueue->ismin);
    pqueue=LeftistHeapMerge_REC(pqueue,insertnode);
    return pqueue;
}
LBPriorotyQueue LeftistHeapDelete(LBPriorotyQueue pqueue){
    if(LeftistHeapIsEmpty(pqueue)){
        printf("无法删除：空左式堆\n");
        return nullptr;
    }
    LBPriorotyQueue oldroot=pqueue;
    pqueue=LeftistHeapMerge_REC(pqueue->leftchild,pqueue->rightchild);
    free(oldroot);
    return pqueue;
}