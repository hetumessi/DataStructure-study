//
// Created by 徐绍骞 on 2022/2/19.
//
#ifndef ADVANCED_DATA_STRUCTURE_AND_ALGRITHM_ANALYSIS_DATA_STRUCTURE_H
#define ADVANCED_DATA_STRUCTURE_AND_ALGRITHM_ANALYSIS_DATA_STRUCTURE_H
#include<cstdio>
#include<cstdlib>
#define MYINFINITY 65535
#define MINPQSIZE 5
#define MAXTREES 100
#define MINHASHTBSIZE MINPQSIZE
typedef int Elementype;
typedef unsigned Index;
typedef struct AVLnode*AVLptr;
typedef struct Splaynode*Splayptr;
typedef struct RBnode*RBptr;
typedef struct Bplusnode*Bplusptr;
typedef struct BinaryHeap*BPriorityQueue;
typedef struct LeftistHeap*LBPriorityQueue;
typedef struct SkewHeap*SBPriorityQueue;
typedef struct Binode*BinTree;
typedef struct BinCollection*BinomialQueue;
typedef struct Hashtable*HashTable;
typedef struct Listnode*Hashnodeptr;
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
void BinTreeTraverse(BinTree);
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
struct Binode{
    Elementype value;
    BinTree firstchild,sibling,parent;
};
struct BinCollection{
    int currentsize; //注意是结点数量，不是树的数量
    BinTree*Forest;
};
BinTree TreeInitialize(BinTree,Elementype);
BinomialQueue BinomialQueueInitialize(BinomialQueue);
BinTree TreesCombine(BinTree,BinTree); //合并同样大小的两棵树
BinomialQueue ForestMerge(BinomialQueue,BinomialQueue);
BinomialQueue BinomialQueueInsert(BinomialQueue,Elementype);
Elementype BinomialQueueDeleteMin(BinomialQueue);
// IncreaseKey和PercolateDown的实现方法同理
// 对一个任意结点的Delete操作可以通过DecreaseKey到一个极小值后上滤到根结点，然后DeleteMin
BinTree BinTreeDecreaseKey(BinTree,Elementype);
BinTree BinTreePercolateUp(BinTree);
bool BinomialQueueIsEmpty(BinomialQueue);
struct Hashtable{
    HashTable head;
    Hashnodeptr*nodelist;
    int capacity;
};
struct Listnode{
    Elementype key;
    Hashnodeptr next;
};
inline Index hash_int(Elementype key,int tablesize){
    return key%tablesize;
}
inline Index hash_sumfunc(const char*key,int tablesize){
    unsigned sum=(unsigned char)*key;
    while(*key++)sum+=*key-'a';
    return sum%tablesize;
}
inline Index hash_first3sumfunc(const char*key,int tablesize){
    return (key[0]-'a'+1+27*(key[1]-'a'+1)+27*27*(key[2]-'a'+1))%tablesize;
}
inline Index hash_move32sumfunc(const char*key,int tablesize){
    unsigned long sum=(unsigned char)*key-'a';
    while(*key++){
        sum<<=5;
        sum+=*key;
    }
    return  sum%tablesize;
}
HashTable HashTableInitialize(HashTable,int);
void DestroyHashTable(HashTable);
Hashnodeptr HashTableFind(Elementype,HashTable);
HashTable HashTableInsert(Elementype,HashTable);
Elementype HashTableRetrieve(Hashnodeptr);
#endif //ADVANCED_DATA_STRUCTURE_AND_ALGRITHM_ANALYSIS_DATA_STRUCTURE_H
