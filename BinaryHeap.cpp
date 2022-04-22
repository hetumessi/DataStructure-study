//
// Created by 徐绍骞 on 2022/4/22.
//
#include<cstring>
static bool compare(enum maxormin ismin,const Elementype a,const Elementype b){
    return ismin?a-b<0:a-b>0;
}
PriorityQueue BinaryHeapInitialize(PriorityQueue pqueue,int maxelements,enum maxormin ismin){
    pqueue=(PriorityQueue)malloc(sizeof(struct BinaryHeap));
    if(maxelements<MINPQSIZE){
        printf("Priority queue is too small.");
        maxelements=MINPQSIZE;
    }else{
        pqueue->value=(Elementype*)malloc((maxelements+1)*sizeof(Elementype));
        pqueue->MaxOrMin=ismin;
        pqueue->capacity=maxelements;
        pqueue->size=0;
        if(ismin){
            pqueue->value[0]=-INFINITY;
            for(int i=1;i<=maxelements;i++)pqueue->value[i]=INFINITY;
        }else{
            pqueue->value[0]=INFINITY;
            for(int i=1;i<=maxelements;i++)pqueue->value[i]=-INFINITY;
        }
    }
    return pqueue;
}
void BinaryHeapDestroy(PriorityQueue pqueue){
    free(pqueue->value);
    free(pqueue);
}
void BinaryHeapMakeEmpty(PriorityQueue pqueue){
    pqueue->size=0;
    memset(pqueue->value+1,0,pqueue->capacity);
}
PriorityQueue BinaryHeapInsert(PriorityQueue pqueue,Elementype insertvalue){
    if(BinaryHeapisFull(pqueue)){
        if(compare(pqueue->MaxOrMin,insertvalue,pqueue->value[pqueue->size])){
            printf("二叉堆已满：插入数据将替换已有的最后一个数据\n");
            pqueue->value[pqueue->size--]=insertvalue;
        }else{
            printf("二叉堆已满：无法插入数据");
            return pqueue;
        }
    }
    pqueue->value[++pqueue->size]=insertvalue;
    PercolateUp(pqueue,pqueue->size);
    return pqueue;
}
Elementype BinaryHeapDelete(PriorityQueue pqueue){
    if(BinaryHeapisEmpty(pqueue)){
        printf("无法删除：空叉堆\n");
        return pqueue->value[0];
    }
    Elementype returnvalue=BinaryHeapGetFront(pqueue);
    pqueue->value[1]=pqueue->value[pqueue->size--];
    PercolateDown(pqueue,1);
    return returnvalue;
}
Elementype BinaryHeapGetFront(PriorityQueue pqueue){
    return pqueue->value[1];
}
bool BinaryHeapisEmpty(PriorityQueue pqueue){
    return pqueue->size==0;
}
bool BinaryHeapisFull(PriorityQueue pqueue){
    return pqueue->size==pqueue->capacity;
}
PriorityQueue BinaryHeapDecreaseKey(PriorityQueue pqueue,Elementype delta,int decpos){
    pqueue->value[decpos]-=delta;
    return pqueue;
}
PriorityQueue BinaryHeapIncreaseKey(PriorityQueue pqueue,Elementype delta,int incpos){
    pqueue->value[incpos]+=delta;
    return pqueue;
}
void PercolateDown(PriorityQueue pqueue,int pos){
    Elementype tmpvalue=pqueue->value[pos];
    int parentpos=pos,childpos;
    for(;parentpos<=pqueue->size/2;parentpos=childpos){
        childpos=parentpos*2;
        if(childpos<pqueue->capacity)childpos=
            compare(pqueue->MaxOrMin,pqueue->value[childpos],pqueue->value[childpos+1])?
            childpos:childpos+1;
        if(compare(pqueue->MaxOrMin,tmpvalue,pqueue->value[childpos]))break;
        else pqueue->value[parentpos]=pqueue->value[childpos];
    }
    pqueue->value[parentpos]=tmpvalue;
}
void PercolateUp(PriorityQueue pqueue,int pos){
    Elementype tmpvalue=pqueue->value[pos];
    int currentpos=pos;
    for(;compare(pqueue->MaxOrMin,pqueue->value[currentpos],pqueue->value[currentpos/2]);currentpos/=2)
        pqueue->value[currentpos]=pqueue->value[currentpos/2];
    pqueue->value[currentpos]=tmpvalue;
}
PriorityQueue BinaryHeapBuild(PriorityQueue pqueue,const Elementype*input,int numofinput){
    for(int i=1;i<=numofinput;i++){
        pqueue->value[i]=input[i-1];
        pqueue->size++;
    }
    for(int i=numofinput/2;i>0;i--)PercolateDown(pqueue,i);
    return pqueue;
}