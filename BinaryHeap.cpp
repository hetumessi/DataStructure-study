//
// Created by 徐绍骞 on 2022/4/22.
//
#include<cstring>
bool compare(enum MAXORMIN ismin,Elementype a,Elementype b){
    return ismin?a-b<0:a-b>0;
}
BPriorityQueue BinaryHeapInitialize(BPriorityQueue pqueue, int maxelements, enum MAXORMIN ismin){
    pqueue=(BPriorityQueue)malloc(sizeof(struct BinaryHeap));
    if(maxelements<MINPQSIZE){
        printf("Priority queue is too small.");
        maxelements=MINPQSIZE;
    }else{
        pqueue->value=(Elementype*)malloc((maxelements+1)*sizeof(Elementype));
        pqueue->MaxOrMin=ismin;
        pqueue->capacity=maxelements;
        pqueue->size=0;
        if(ismin){
            pqueue->value[0]=-MYINFINITY;
            for(int i=1;i<=maxelements;i++)pqueue->value[i]=MYINFINITY;
        }else{
            pqueue->value[0]=MYINFINITY;
            for(int i=1;i<=maxelements;i++)pqueue->value[i]=-MYINFINITY;
        }
    }
    return pqueue;
}
void BinaryHeapDestroy(BPriorityQueue pqueue){
    free(pqueue->value);
    free(pqueue);
}
void BinaryHeapMakeEmpty(BPriorityQueue pqueue){
    pqueue->size=0;
    memset(pqueue->value+1,0,pqueue->capacity);
}
BPriorityQueue BinaryHeapInsert(BPriorityQueue pqueue, Elementype insertvalue){
    if(BinaryHeapisFull(pqueue)){
        if(compare(pqueue->MaxOrMin,insertvalue,pqueue->value[pqueue->size])){
            printf("二叉堆已满：插入数据将替换已有的最后一个数据\n");
            pqueue->size--;
        }else{
            printf("二叉堆已满：无法插入数据");
            return pqueue;
        }
    }
    pqueue->value[++pqueue->size]=insertvalue;
    PercolateUp(pqueue,pqueue->size);
    return pqueue;
}
Elementype BinaryHeapDelete(BPriorityQueue pqueue){
    if(BinaryHeapisEmpty(pqueue)){
        printf("无法删除：空叉堆\n");
        return pqueue->value[0];
    }
    Elementype returnvalue=BinaryHeapGetFront(pqueue);
    pqueue->value[1]=pqueue->value[pqueue->size--];
    PercolateDown(pqueue,1);
    return returnvalue;
}
Elementype BinaryHeapGetFront(BPriorityQueue pqueue){
    return pqueue->value[1];
}
bool BinaryHeapisEmpty(BPriorityQueue pqueue){
    return pqueue->size==0;
}
bool BinaryHeapisFull(BPriorityQueue pqueue){
    return pqueue->size==pqueue->capacity;
}
BPriorityQueue BinaryHeapDecreaseKey(BPriorityQueue pqueue, Elementype delta, int decpos){
    pqueue->value[decpos]-=delta;
    if(pqueue->MaxOrMin)PercolateUp(pqueue,decpos);
    else PercolateDown(pqueue,decpos);
    return pqueue;
}
BPriorityQueue BinaryHeapIncreaseKey(BPriorityQueue pqueue, Elementype delta, int incpos){
    pqueue->value[incpos]+=delta;
    if(pqueue->MaxOrMin)PercolateDown(pqueue,incpos);
    else PercolateUp(pqueue,incpos);
    return pqueue;
}
void PercolateDown(BPriorityQueue pqueue, int pos){
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
void PercolateUp(BPriorityQueue pqueue, int pos){
    Elementype tmpvalue=pqueue->value[pos];
    int currentpos=pos;
    for(;compare(pqueue->MaxOrMin,pqueue->value[currentpos],pqueue->value[currentpos/2]);currentpos/=2)
        pqueue->value[currentpos]=pqueue->value[currentpos/2];
    pqueue->value[currentpos]=tmpvalue;
}
BPriorityQueue BinaryHeapBuild(BPriorityQueue pqueue, const Elementype*input, int numofinput){
    for(int i=1;i<=numofinput;i++){
        pqueue->value[i]=input[i-1];
        pqueue->size++;
    }
    for(int i=numofinput/2;i>0;i--)PercolateDown(pqueue,i);
    return pqueue;
}