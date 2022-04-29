#include<ctime>
#include<cstdio>
#include"AVLtree.cpp"
#include"Splaytree.cpp"
#include"RBtree.cpp"
#include"Bplustree.cpp"
#include"BinaryHeap.cpp"
#include"LeftistHeap.cpp"
#include"SkewHeap.cpp"
#include"BinomialQueue.cpp"
#include"test/test.cpp"
#include"demo/demo.cpp"
int main(){
    clock_t start=clock(),end;
    BinomialQueue q=nullptr,p=nullptr;
    int capacity=15,numofinput=capacity-8,randdata[capacity];
    int stddata[10]={1,2,3,4,5,6,7,8,9,10};
    srand(time(nullptr));
    for(int i=0;i<capacity;i++){
        randdata[i]=rand()%100;
        printf("%d ",randdata[i]);
    }
    printf("\n");
    q=BinomialQueueInitialize(q);
    p=BinomialQueueInitialize(p);
    for(int i=0;i<numofinput;i++)BinomialQueueInsert(q,randdata[i]);
    for(int i=0;i<numofinput+1;i++)BinomialQueueInsert(p,stddata[i]);
    for(int i=0;q->Forest[i];i++){
        TreeTraverse(q->Forest[i]);
        printf("\n");
    }
    ForestMerge(p,q);
    BinomialQueueDeleteMin(p);
    for(int i=0;i<MAXTREES;i++)if(p->Forest[i]){
        TreeTraverse(p->Forest[i]);
        printf("\n");
    }
    BinTreeDecreaseKey(p->Forest[2]->firstchild->firstchild,50);
    for(int i=0;i<MAXTREES;i++)if(p->Forest[i]){
        TreeTraverse(p->Forest[i]);
        printf("\n");
    }
    printf("\n");
    end=clock();
    printf("耗时：%lf 秒",(double)(end-start)/CLOCKS_PER_SEC);
    return 0;
}