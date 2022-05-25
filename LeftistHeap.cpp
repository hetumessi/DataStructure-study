//
// Created by 徐绍骞 on 2022/4/23.
//
#include"data_structure.h"
#include<vector>
#include<queue>
static LBPriorityQueue DoMerge(LBPriorityQueue,LBPriorityQueue);
static LBPriorityQueue SwapChildren(LBPriorityQueue);
static bool cmp(LBPriorityQueue a, LBPriorityQueue b){
    return compare(a->ismin,a->value,b->value);
}
static int Getheight(LBPriorityQueue pqueue){
    int leftheight,rightheight;
    if(pqueue){
        leftheight=Getheight(pqueue->leftchild);
        rightheight=Getheight(pqueue->rightchild);
        return (leftheight>rightheight?leftheight:rightheight)+1;
    }
    return 0;
}
void LeftistHeapTraversal(LBPriorityQueue root){
    std::queue<LBPriorityQueue>q;
    if(LeftistHeapIsEmpty(root)){
        printf("空堆\n");
        return;
    }
    q.push(root);
    while(!q.empty()){
        printf("[%d, %d, %d] ",q.front()->value,q.front()->Npl,Getheight(q.front()));
        if(q.front()->leftchild)q.push(q.front()->leftchild);
        if(q.front()->rightchild)q.push(q.front()->rightchild);
        q.pop();
    }
}
LBPriorityQueue LeftistHeapInitialize(LBPriorityQueue pqueue, Elementype intializevalue, enum MAXORMIN ismin){
    pqueue=(LBPriorityQueue)malloc(sizeof(struct LeftistHeap));
    pqueue->ismin=ismin;
    pqueue->rightchild=pqueue->leftchild=nullptr;
    pqueue->Npl=0;
    pqueue->value=intializevalue;
    return pqueue;
}
Elementype LeftistHeapGetfront(LBPriorityQueue pqueue){
    return pqueue->value;
}
bool LeftistHeapIsEmpty(LBPriorityQueue pqueue){
    return !pqueue;
}
LBPriorityQueue LeftistHeapMerge_REC(LBPriorityQueue pqueue1, LBPriorityQueue pqueue2){
    if(LeftistHeapIsEmpty(pqueue1))return pqueue2;
    if(LeftistHeapIsEmpty(pqueue2))return pqueue1;
    if(pqueue1->ismin!=pqueue2->ismin){
        printf("无法合并：最小堆和最大堆\n");
        return nullptr;
    }
    if(compare(pqueue1->ismin,pqueue1->value,pqueue2->value))
        return DoMerge(pqueue1,pqueue2);
    else return DoMerge(pqueue2,pqueue1);
}
LBPriorityQueue LeftistHeapMerge_ITE(LBPriorityQueue pqueue1, LBPriorityQueue pqueue2){
    if(LeftistHeapIsEmpty(pqueue1))return pqueue2;
    if(LeftistHeapIsEmpty(pqueue2))return pqueue1;
    if(pqueue1->ismin!=pqueue2->ismin){
        printf("无法合并：最小堆和最大堆\n");
        return nullptr;
    }
    LBPriorityQueue current1=pqueue1,current2=pqueue2,tmpnode,newroot;
    std::vector<LBPriorityQueue>sortvector;
    while(current1||current2){
        if(current1){
            tmpnode=current1;
            sortvector.push_back(current1);
            current1=current1->rightchild;
            tmpnode->rightchild=nullptr;
        }
        if(current2){
            tmpnode=current2;
            sortvector.push_back(current2);
            current2=current2->rightchild;
            tmpnode->rightchild=nullptr;
        }
    }
    std::sort(sortvector.begin(),sortvector.end(), cmp);
    newroot=*sortvector.begin();
    for(auto i=sortvector.begin();i!=sortvector.end()-1;i++)
        (*i)->rightchild=*(i+1);
    for(auto i=sortvector.rbegin();i!=sortvector.rend();i++){
        if(LeftistHeapIsEmpty((*i)->rightchild))continue;
        else if(LeftistHeapIsEmpty((*i)->leftchild)||(*i)->leftchild->Npl<(*i)->rightchild->Npl)
            SwapChildren(*i);
        if(!LeftistHeapIsEmpty((*i)->rightchild))(*i)->Npl=(*i)->rightchild->Npl+1;
        else (*i)->Npl=0;
    }
    return newroot;
}
LBPriorityQueue DoMerge(LBPriorityQueue pqueue1, LBPriorityQueue pqueue2){
    if(LeftistHeapIsEmpty(pqueue1->leftchild))pqueue1->leftchild=pqueue2;
    else{
        pqueue1->rightchild=LeftistHeapMerge_REC(pqueue1->rightchild,pqueue2);
        if(pqueue1->leftchild->Npl<pqueue1->rightchild->Npl)SwapChildren(pqueue1);
        pqueue1->Npl=pqueue1->rightchild->Npl+1;
    }
    return pqueue1;
}
LBPriorityQueue SwapChildren(LBPriorityQueue pqueue){
    LBPriorityQueue tmpnode=pqueue->leftchild;
    pqueue->leftchild=pqueue->rightchild;
    pqueue->rightchild=tmpnode;
    return pqueue;
}
LBPriorityQueue LeftistHeapInsert(LBPriorityQueue pqueue, Elementype insertvalue){
    LBPriorityQueue insertnode=nullptr;
    insertnode=LeftistHeapInitialize(insertnode,insertvalue,pqueue->ismin);
//    pqueue=LeftistHeapMerge_REC(pqueue,insertnode);
    pqueue=LeftistHeapMerge_ITE(pqueue,insertnode);
    return pqueue;
}
LBPriorityQueue LeftistHeapDelete(LBPriorityQueue pqueue){
    if(LeftistHeapIsEmpty(pqueue)){
        printf("无法删除：空左式堆\n");
        return nullptr;
    }
    LBPriorityQueue deletenode=pqueue;
    pqueue=LeftistHeapMerge_REC(pqueue->leftchild,pqueue->rightchild);
    free(deletenode);
    return pqueue;
}
LBPriorityQueue LeftistHeapBuild(LBPriorityQueue pqueue, const Elementype*input, int numofinput){
    std::queue<LBPriorityQueue>LBqueue;
    LBPriorityQueue innode=pqueue,outnode1,outnode2;
    LBqueue.push(innode);
    for(int i=0;i<numofinput;i++){
        innode=LeftistHeapInitialize(innode, input[i], pqueue->ismin);
        LBqueue.push(innode);
    }
    while(LBqueue.size()>1){
        outnode1=LBqueue.front(),LBqueue.pop();
        outnode2=LBqueue.front(),LBqueue.pop();
        innode=LeftistHeapMerge_REC(outnode1,outnode2);
//        innode=LeftistHeapMerge_ITE(outnode1,outnode2);
        LBqueue.push(innode);
    }
    pqueue=LBqueue.front();
    return pqueue;
}