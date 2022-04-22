//
// Created by 徐绍骞 on 2022/2/19.
//

#ifndef ADVANCED_DATA_STRUCTURE_AND_ALGRITHM_ANALYSIS_DATA_STRUCTURE_H
#define ADVANCED_DATA_STRUCTURE_AND_ALGRITHM_ANALYSIS_DATA_STRUCTURE_H
#define INFINITY 65535
#define MINPQSIZE 5
#define MAXPQSIZE (INFINITY/sizeof(int))
typedef int Elementype;
typedef struct AVLnode*AVLptr;
typedef struct Splaynode*Splayptr;
typedef struct RBnode*RBptr;
typedef struct Bplusnode*Bplusptr;
typedef struct BinaryHeap*PriorityQueue;
enum isleaf{NONLEAF,LEAF};
enum maxormin{MAX,MIN};
struct  AVLnode{
    AVLptr leftchild,rightchild;
    Elementype value;
    int bp;
};
int Getheight(AVLptr);
void AVLTraverse(AVLptr);
AVLptr AVLFindvalue(AVLptr,Elementype);
AVLptr AVLFindmin(AVLptr);
AVLptr AVLFindmax(AVLptr);
AVLptr LLSingleRotation(AVLptr);
AVLptr RRSingleRotation(AVLptr);
AVLptr LRDoubleRotation(AVLptr);
AVLptr RLDoubleRotation(AVLptr);
AVLptr AVLInsert(AVLptr,Elementype);
AVLptr AVLDelete(AVLptr,Elementype);
struct Splaynode{
    Splayptr leftchild,rightchild;
    Elementype value;
};
Splayptr SplayInitialize(Splayptr);
void SplayTraverse(Splayptr);
Splayptr SplayZig(Splayptr);
Splayptr SplayZag(Splayptr);
Splayptr SplaySplay(Splayptr, Elementype);
Splayptr SplayInsert(Splayptr,Elementype);
Splayptr SplayDelete(Splayptr,Elementype);
enum color{RED,BLACK};
struct RBnode{
    RBptr leftchild,rightchild;
    Elementype value;
    bool color;
};
RBptr RBNULLptr=nullptr,current,parent,sibling,grand,great;
RBptr RBInitialize(RBptr,bool);
void RBtraverse(RBptr);
RBptr RBFindMax(RBptr);
RBptr RBFindMin(RBptr);
RBptr RBRotate(RBptr,Elementype);
RBptr SingleLeftRotate(RBptr);
RBptr SingleRightRotate(RBptr);
void RBHandleInsert(RBptr,Elementype);
RBptr RBInsert(RBptr,Elementype);
void RBHandleDelete();
RBptr RBDelete(RBptr,Elementype);
struct Bplusnode{
    Bplusptr*childs,sibling,parent;
    Elementype*keys;
    bool isleaf;
};
Bplusptr BplusInitialize(Bplusptr,int,bool);
Bplusptr BplusSearchdata(Bplusptr,Elementype,int);
Bplusptr BplusSearchrange(Bplusptr,Elementype,Elementype,int);
void BplusTraverse(Bplusptr,int);
void BplusTravelleaves(Bplusptr,int);
Bplusptr BplusInsert(Bplusptr,Elementype,int);
Bplusptr DoInsert(Bplusptr,Elementype,int);
Bplusptr LeafInsert(Bplusptr,Elementype,int);
Bplusptr LeafSplit(Bplusptr,int);
Bplusptr NonleafSplit(Bplusptr,int);
Bplusptr HandleParent(Bplusptr,Bplusptr,int);
Bplusptr BuildNewParent(Bplusptr,Bplusptr,Elementype,int);
struct BinaryHeap{   //数组实现(数组模拟完全二叉树)
    enum maxormin MaxOrMin;
    Elementype*value;
    int capacity,size;
};
PriorityQueue BinaryHeapInitialize(PriorityQueue,int,enum maxormin);
void BinaryHeapDestroy(PriorityQueue);
void BinaryHeapMakeEmpty(PriorityQueue);
PriorityQueue BinaryHeapInsert(PriorityQueue,Elementype);
Elementype BinaryHeapDelete(PriorityQueue);
Elementype BinaryHeapGetFront(PriorityQueue);
bool BinaryHeapisEmpty(PriorityQueue);
bool BinaryHeapisFull(PriorityQueue);
PriorityQueue BinaryHeapDecreaseKey(PriorityQueue,Elementype,int);
PriorityQueue BinaryHeapIncreaseKey(PriorityQueue,Elementype,int);
PriorityQueue BinaryHeapBuild(PriorityQueue,const Elementype*,int);
void PercolateDown(PriorityQueue,int);
void PercolateUp(PriorityQueue,int);
#endif //ADVANCED_DATA_STRUCTURE_AND_ALGRITHM_ANALYSIS_DATA_STRUCTURE_H
