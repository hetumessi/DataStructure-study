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
    BPriorityQueue pq1=nullptr,pq2=nullptr;
    int capacity=15,numofinput=capacity-5,randdata[capacity];
    int stddata[10]={1,2,3,4,5,6,7,8,9,10};
    srand(time(nullptr));
    for(int i=0;i<capacity;i++)randdata[i]=rand()%100;
    pq1=BinaryHeapInitialize(pq1,capacity,MIN);
    pq2=BinaryHeapInitialize(pq2,capacity,MAX);
    pq1=BinaryHeapBuild(pq1, randdata, numofinput);
    pq2=BinaryHeapBuild(pq2, randdata, numofinput);
    while(pq1->size>0)printf("%d ",BinaryHeapDelete(pq1));
    printf("\n");
    while(pq2->size>0)printf("%d ",BinaryHeapDelete(pq2));
    printf("\n");
    end=clock();
    printf("耗时：%lf 秒",(double)(end-start)/CLOCKS_PER_SEC);
    return 0;
}