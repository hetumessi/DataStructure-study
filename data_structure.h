//
// Created by 徐绍骞 on 2022/2/19.
//
#ifndef ADVANCED_DATA_STRUCTURE_AND_ALGRITHM_ANALYSIS_DATA_STRUCTURE_H
#define ADVANCED_DATA_STRUCTURE_AND_ALGRITHM_ANALYSIS_DATA_STRUCTURE_H
#include<cstdio>
#include<cstdlib>
#include<cassert>
#include<cstring>
#define MYINFINITY 65535
#define SPACESIZE 256*256
#define MINPQSIZE 5
#define MAXTREES 100
#define MINHASHTBSIZE MINPQSIZE
#define DEFAULTLDFACTOR 0.5
typedef int Elementype;
typedef int Weighttype;
typedef int Datatype;
typedef Elementype Cursornode;
typedef Cursornode Cursorlist;
typedef Cursornode Cursorpos;
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
typedef struct Hashtable_Link*HashTable_Link;
typedef struct Hashtable_Array*HashTable_Array;
typedef struct Vnode Vertex;
typedef struct Enode*Edge;
typedef struct Listnode*Hashnodeptr;
typedef struct Vertexnode*LVertex;
typedef struct Adjacencynode*Adjacencylist;
typedef struct LGraphnode*LGraph;
typedef struct MGraphnode*MGraph;
typedef struct Entrynode*GraphEntry;
enum COLOR{RED,BLACK};
enum ISLEAF{NONLEAF,LEAF};
enum MAXORMIN{MAX,MIN};
enum KINDOFENTRY{Legitimate,Empty,Deleted};
enum KINDOFDETECT{Linear,Square,Double};
enum KINDOFPRIME{Larger,Lesser};
struct CursorNode{
    Elementype element;
    Cursorpos next;
};
extern struct CursorNode Cursorspace[SPACESIZE];          //链表空间
void CursorspaceInitialize();
Cursorlist ListMakeEmpty();
bool ListIsEmpty(Cursorlist);
bool ListisLast(Cursorpos,Cursorlist);
Cursorpos ListFind(Elementype,Cursorlist);
Cursorlist ListDelete(Elementype,Cursorlist);
Cursorlist ListInsert(Elementype ,Cursorlist);
Cursorlist ListDeleteList(Cursorlist);
Cursorpos GetHead(Cursorlist);
Cursorpos GetFirst(Cursorlist);
Cursorpos ListAdvance(Cursorpos,Cursorlist,int);
Elementype ListRetrieve(Cursorpos);
Cursorlist ListReverse(Cursorlist);
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
struct Hashtable_Link{
    Hashnodeptr*nodelist;
    int capacity;
};
struct Hashtable_Array{
    Hashnodeptr nodeArray;
    int capacity,size;
    enum KINDOFDETECT howtodetect;
    double loadfactor;
};
struct Listnode{
    Elementype key;
    Hashnodeptr next;
    enum KINDOFENTRY info;
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
HashTable_Link LHashTableInitialize(HashTable_Link, int);
HashTable_Array AHashTableInitialize(HashTable_Array, int,enum KINDOFDETECT,double);
void LHashTableDestroy(HashTable_Link);
void AHashTableDestroy(HashTable_Array);
Hashnodeptr LHashTableFind(Elementype, HashTable_Link);
Index AHashTableFind(Elementype, HashTable_Array);
HashTable_Link LHashTableInsert(Elementype, HashTable_Link);
HashTable_Array AHashTableInsert(Elementype, HashTable_Array);
HashTable_Link LHashTableDelete(Elementype, HashTable_Link);
HashTable_Array AHashTableDelete(Elementype, HashTable_Array);
HashTable_Array Rehash(HashTable_Array);
struct Vnode{
    Datatype vname;  //Datatype可以通过散列映射为数组下标
    Elementype key;
};
struct Enode{
    Vertex v1,v2;
    Weighttype weight;
};
struct Vertexnode{
    Datatype vname;
    Elementype key;
    Weighttype weight;
    LVertex next;
};
struct Adjacencynode{
    Elementype key;
    int indegree,index;
    LVertex firstadjacency;
};
struct LGraphnode{
    Adjacencylist graphlist;
    int Vnum,Enum;
    bool*visited;
};
struct MGraphnode{
    Weighttype**graphmatrix;
    Elementype*vertexkey;
    int Vnum,Enum;
    bool*visited;
};
struct Entrynode{
    int Vnum;
    Weighttype*dist;
    Vertex*path;
};
LGraph LGraphInitialize(LGraph,int);
MGraph MGraphInitialize(MGraph,int);
LGraph LGraphInsert(LGraph,Edge);
MGraph MGraphInsert(MGraph,Edge);
void LGraphDFS(LGraph);
void MGraphDFS(MGraph);
void LGraphBFS(LGraph);
void MGraphBFS(MGraph);
Datatype*LGraphTopSort(LGraph,Datatype*,int);//邻接矩阵的拓扑排序同理，不过要额外计算每个顶点的入度
GraphEntry EntryInitialize(GraphEntry,int);
GraphEntry LGraphDijkstra(LGraph,GraphEntry,Datatype);
GraphEntry MGraphDijkstra(MGraph,GraphEntry,Datatype);
#endif //ADVANCED_DATA_STRUCTURE_AND_ALGRITHM_ANALYSIS_DATA_STRUCTURE_H
