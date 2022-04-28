#include<ctime>
#include<cstdio>
#include"AVLtree.cpp"
#include"Splaytree.cpp"
#include"RBtree.cpp"
#include"Bplustree.cpp"
#include"BinaryHeap.cpp"
#include"LeftistHeap.cpp"
#include"SkewHeap.cpp"
#include"test/test.cpp"
#include"demo/demo.cpp"
int main(){
    clock_t start=clock(),end;
    SBPriorityQueue pq1=nullptr,pq2=nullptr,pq3=nullptr,pq4=nullptr;
    int capacity=15,numofinput=capacity-8,randdata[capacity];
    int stddata[10]={1,2,3,4,5,6,7,8,9,10};
    srand(time(nullptr));
    for(int i=0;i<capacity;i++){
        randdata[i]=rand()%100;
        printf("%d ",randdata[i]);
    }
    printf("\n");
    pq1=SkewHeapInitialize(pq1,stddata[0],MIN);
    pq2=SkewHeapInitialize(pq2,stddata[0],MAX);
    pq3=SkewHeapInitialize(pq3,stddata[0],MIN);
    pq4=SkewHeapInitialize(pq4,stddata[0],MAX);
//    printf("%d %d\n",pq1->value,pq2->value);
    for(int i=0;i<numofinput;i++)pq1=SkewHeapInsert(pq1,stddata[i+1]);
    for(int i=0;i<numofinput;i++)pq2=SkewHeapInsert(pq2,stddata[i+1]);
    pq3=SkewHeapBuild(pq3, stddata+1, numofinput);
    pq4=SkewHeapBuild(pq4, stddata+1, numofinput);
    pq1=SkewHeapDelete(pq1);
    pq2=SkewHeapDelete(pq2);
    pq3=SkewHeapDelete(pq3);
    pq4=SkewHeapDelete(pq4);
//    pq1=LeftistHeapMerge_REC(pq1,pq2);
//    pq1=LeftistHeapMerge_ITE(pq1,pq3);
//    pq2=LeftistHeapMerge_REC(pq4,pq2);
    SkewHeapTraversal(pq1);
    printf("\n");
    SkewHeapTraversal(pq2);
    printf("\n");
    SkewHeapTraversal(pq3);
    printf("\n");
    SkewHeapTraversal(pq4);
    printf("\n");
    end=clock();
    printf("耗时：%lf 秒",(double)(end-start)/CLOCKS_PER_SEC);
    return 0;
}