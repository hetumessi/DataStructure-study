//
// Created by 徐绍骞 on 2022/4/28.
//
#include"data_structure.h"
#include<queue>
static SBPriorityQueue DoMerge(SBPriorityQueue,SBPriorityQueue);
static SBPriorityQueue SwapChildren(SBPriorityQueue);
static int GetDepth(SBPriorityQueue root,SBPriorityQueue dest){
    int leftdepth,rightdepth,depth=-1;
    if(root&&root!=dest){
        leftdepth=(depth=GetDepth(root->leftchild,dest))>=0?depth+1:-1;
        rightdepth=(depth=GetDepth(root->rightchild,dest))>=0?depth+1:-1;
        return leftdepth>rightdepth?leftdepth:rightdepth;
    }
    if(!root)return depth;
    else return 0;
}
void SkewHeapTraversal(SBPriorityQueue root){
    std::queue<SBPriorityQueue>q;
    if(!root){
        printf("无法遍历：空堆\n");
        return;
    }
    int currentdepth=0,tmpdepth;
    q.push(root);
    printf("%d: ",currentdepth);
    while(!q.empty()){
        tmpdepth=GetDepth(root,q.front());
        if(tmpdepth>currentdepth){
            currentdepth=tmpdepth;
            printf("\n%d: ",currentdepth);
        }
        printf("%d ",q.front()->value);
        if(q.front()->leftchild)q.push(q.front()->leftchild);
        if(q.front()->rightchild)q.push(q.front()->rightchild);
        q.pop();
    }
}
SBPriorityQueue SkewHeapInitialize(SBPriorityQueue pqueue,Elementype initializevalue,enum MAXORMIN ismin){
    pqueue=(SBPriorityQueue)malloc(sizeof(struct SkewHeap));
    pqueue->ismin=ismin;
    pqueue->leftchild=pqueue->rightchild=nullptr;
    pqueue->value=initializevalue;
    return pqueue;
}
SBPriorityQueue SkewHeapInsert(SBPriorityQueue pqueue,Elementype insertvalue){
    SBPriorityQueue insertnode=nullptr;
    insertnode=SkewHeapInitialize(insertnode,insertvalue,pqueue->ismin);
    pqueue=SkewHeapMerge(pqueue,insertnode);
    return pqueue;
}
SBPriorityQueue SkewHeapDelete(SBPriorityQueue pqueue){
    if(!pqueue){
        printf("无法删除：空斜堆\n");
        return nullptr;
    }else{
        SBPriorityQueue deletenode=pqueue;
        pqueue=SkewHeapMerge(deletenode->leftchild,deletenode->rightchild);
        free(deletenode);
    }
    return pqueue;
}
SBPriorityQueue SkewHeapMerge(SBPriorityQueue pqueue1,SBPriorityQueue pqueue2){
    if(!pqueue1)return pqueue2;
    if(!pqueue2)return pqueue1;
    if(pqueue1->ismin!=pqueue2->ismin){
        printf("无法合并：最小堆和最大堆\n");
        return nullptr;
    }
    if(compare(pqueue1->ismin,pqueue1->value,pqueue2->value))
        return DoMerge(pqueue1,pqueue2);
    else return DoMerge(pqueue2,pqueue1);
}
SBPriorityQueue DoMerge(SBPriorityQueue pqueue1,SBPriorityQueue pqueue2){
    if(!pqueue1->leftchild)pqueue1->leftchild=pqueue2;
    else{
        pqueue1->rightchild=SkewHeapMerge(pqueue1->rightchild,pqueue2);
        SwapChildren(pqueue1);
    }
    return pqueue1;
}
SBPriorityQueue SwapChildren(SBPriorityQueue pqueue){
    SBPriorityQueue tmpnode=pqueue->leftchild;
    pqueue->leftchild=pqueue->rightchild;
    pqueue->rightchild=tmpnode;
    return pqueue;
}
SBPriorityQueue SkewHeapBuild(SBPriorityQueue pqueue,const Elementype*input,int numofinput){
    std::queue<SBPriorityQueue>SBqueue;
    SBPriorityQueue currentnode=pqueue,popnode1,popnode2;
    SBqueue.push(pqueue);
    for(int i=0;i<numofinput;i++){
        currentnode=SkewHeapInitialize(currentnode,input[i],pqueue->ismin);
        SBqueue.push(currentnode);
    }
    while(SBqueue.size()>1){
        popnode1=SBqueue.front(),SBqueue.pop();
        popnode2=SBqueue.front(),SBqueue.pop();
        SBqueue.push(SkewHeapMerge(popnode1,popnode2));
    }
    pqueue=SBqueue.front();
    return pqueue;
}