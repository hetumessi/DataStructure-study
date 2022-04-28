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
typedef struct BinaryHeap*BPriorityQueue;
typedef struct LeftistHeap*LBPriorityQueue;
typedef struct SkewHeap*SBPriorityQueue;
enum COLOR{RED,BLACK};
enum ISLEAF{NONLEAF,LEAF};
enum MAXORMIN{MAX,MIN};
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
bool compare(enum MAXORMIN,Elementype,Elementype);
Bplusptr BplusInitialize(Bplusptr,int,enum MAXORMIN);
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
    enum MAXORMIN MaxOrMin;
    Elementype*value;
    int capacity,size;
};
BPriorityQueue BinaryHeapInitialize(BPriorityQueue, int, enum MAXORMIN);
void BinaryHeapDestroy(BPriorityQueue);
void BinaryHeapMakeEmpty(BPriorityQueue);
BPriorityQueue BinaryHeapInsert(BPriorityQueue, Elementype);
Elementype BinaryHeapDelete(BPriorityQueue);
Elementype BinaryHeapGetFront(BPriorityQueue);
bool BinaryHeapisEmpty(BPriorityQueue);
bool BinaryHeapisFull(BPriorityQueue);
BPriorityQueue BinaryHeapDecreaseKey(BPriorityQueue, Elementype, int);
BPriorityQueue BinaryHeapIncreaseKey(BPriorityQueue, Elementype, int);
BPriorityQueue BinaryHeapBuild(BPriorityQueue,const Elementype*, int);
void PercolateDown(BPriorityQueue, int);
void PercolateUp(BPriorityQueue, int);
struct LeftistHeap{
    enum MAXORMIN ismin;
    Elementype value;
    LBPriorityQueue leftchild,rightchild;
    int Npl;
};
LBPriorityQueue LeftistHeapInitialize(LBPriorityQueue, Elementype, enum MAXORMIN);
Elementype LeftistHeapGetfront(LBPriorityQueue);
bool LeftistHeapIsEmpty(LBPriorityQueue);
LBPriorityQueue LeftistHeapMerge_REC(LBPriorityQueue, LBPriorityQueue);
LBPriorityQueue LeftistHeapMerge_ITE(LBPriorityQueue, LBPriorityQueue);
LBPriorityQueue LeftistHeapInsert(LBPriorityQueue, Elementype);
//为了使左式堆删除与二叉堆删除含义一致(返回原本根结点键值)，因此定义一个宏
#define LeftistHeapBHDelete(queue) LeftistHeapGetfront(heap);LeftistHeapDelete(queue);
LBPriorityQueue LeftistHeapDelete(LBPriorityQueue);
LBPriorityQueue LeftistHeapBuild(LBPriorityQueue, const Elementype*, int);
struct SkewHeap{
    enum MAXORMIN ismin;
    Elementype value;
    SBPriorityQueue leftchild,rightchild;
};
SBPriorityQueue SkewHeapInitialize(SBPriorityQueue,Elementype,enum MAXORMIN);
SBPriorityQueue SkewHeapInsert(SBPriorityQueue,Elementype);
SBPriorityQueue SkewHeapDelete(SBPriorityQueue);
SBPriorityQueue SkewHeapMerge(SBPriorityQueue,SBPriorityQueue);
SBPriorityQueue SkewHeapBuild(SBPriorityQueue,const Elementype*,int);
#endif //ADVANCED_DATA_STRUCTURE_AND_ALGRITHM_ANALYSIS_DATA_STRUCTURE_H
