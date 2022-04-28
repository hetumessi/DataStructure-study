#include<ctime>
#include<cstdio>
#include"AVLtree.cpp"
#include"Splaytree.cpp"
#include"RBtree.cpp"
#include"Bplustree.cpp"
#include"BinaryHeap.cpp"
#include"LeftistHeap.cpp"
#include"test/test.cpp"
#include"demo/demo.cpp"
int main(){
    clock_t start=clock(),end;
    LBPriorotyQueue pq1=nullptr,pq2=nullptr,pq3=nullptr,pq4=nullptr;
    int capacity=15,numofinput=capacity-8,randdata[capacity];
    int stddata[10]={1,2,3,4,5,6,7,8,9,10};
    srand(time(nullptr));
    for(int i=0;i<capacity;i++){
        randdata[i]=rand()%100;
        printf("%d ",randdata[i]);
    }
    printf("\n");
    pq1=LeftistHeapInitialize(pq1,stddata[0],MIN);
    pq2=LeftistHeapInitialize(pq2,stddata[0],MAX);
    pq3=LeftistHeapInitialize(pq3,stddata[0],MIN);
    pq4=LeftistHeapInitialize(pq4,stddata[0],MAX);
//    printf("%d %d\n",pq1->value,pq2->value);
    for(int i=0;i<numofinput;i++)pq1=LeftistHeapInsert(pq1,stddata[i+1]);
    for(int i=0;i<numofinput;i++)pq2=LeftistHeapInsert(pq2,stddata[i+1]);
    pq3=LeftistHeapBuild(pq3, stddata+1, numofinput);
    pq4=LeftistHeapBuild(pq4, stddata+1, numofinput);
//    pq1=LeftistHeapDelete(pq1);
//    pq2=LeftistHeapDelete(pq2);
//    pq3=LeftistHeapDelete(pq3);
//    pq4=LeftistHeapDelete(pq4);
//    pq1=LeftistHeapMerge_REC(pq1,pq2);
//    pq1=LeftistHeapMerge_ITE(pq1,pq3);
//    pq2=LeftistHeapMerge_REC(pq4,pq2);
    LeftistHeapTraversal(pq1);
    printf("\n");
    LeftistHeapTraversal(pq2);
    printf("\n");
    LeftistHeapTraversal(pq3);
    printf("\n");
    LeftistHeapTraversal(pq4);
    printf("\n");
    end=clock();
    printf("耗时：%lf 秒",(double)(end-start)/CLOCKS_PER_SEC);
    return 0;
}