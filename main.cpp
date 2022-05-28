#include"data_structure.h"
#include<ctime>
int main(){
    clock_t start=clock(),end;
    srand(time(nullptr));
    int testnum=25,testdata1[testnum];
    for(int i=0;i<testnum;i++){
        testdata1[i]=rand()%100;
        printf("%d ",testdata1[i]);
    }
    printf("\n");
    HashTable_Array htb1=nullptr;
    HashTable_Link htb2=nullptr;
    htb1=AHashTableInitialize(htb1,10,Double,0.7);
    htb2=LHashTableInitialize(htb2,10);
    printf("%d %d\n",htb1->capacity,htb2->capacity);
    for(int i=0;i<testnum;i++){
        htb1=AHashTableInsert(testdata1[i],htb1);
        htb2=LHashTableInsert(testdata1[i],htb2);
    }
    for(int i=0;i<htb1->capacity;i++)if(htb1->nodeArray[i].info==Legitimate)printf("%d:%d ",i,htb1->nodeArray[i].key);
    printf("\n");
    for(int i=0;i<htb2->capacity;i++)if(htb2->nodelist[i]){
        Hashnodeptr curptr=htb2->nodelist[i];
        while(curptr){
            printf("%d:%d ",i,curptr->key);
            curptr=curptr->next;
        }
    }
    printf("\n%d在开放定址散列表中的下标为%d\n",testdata1[5],AHashTableFind(testdata1[5],htb1));
    LHashTableDelete(LHashTableFind(testdata1[5],htb2)->key,htb2);
    LHashTableFind(testdata1[5],htb2);
    LHashTableDelete(3298,htb2);
    LHashTableInsert(34,htb2);
    LHashTableDelete(LHashTableFind(testdata1[8],htb2)->key,htb2);
    printf("%d %d %d\n",htb1->capacity,htb1->size,htb2->capacity);
    AHashTableDelete(testdata1[7],htb1);
    AHashTableFind(testdata1[7],htb1);
    AHashTableInsert(432,htb1);
    AHashTableFind(423523,htb1);
    AHashTableInsert(312,htb1);
    AHashTableDelete(htb1->nodeArray[4].key,htb1);
//    AHashTableInsert(htb1->nodeArray[4].key,htb1);
    for(int i=0;i<htb1->capacity;i++)if(htb1->nodeArray[i].info==Legitimate)printf("%d:%d ",i,htb1->nodeArray[i].key);
    printf("\n");
    for(int i=0;i<htb2->capacity;i++)if(htb2->nodelist[i]){
            Hashnodeptr curptr=htb2->nodelist[i];
            while(curptr){
                printf("%d:%d ",i,curptr->key);
                curptr=curptr->next;
            }
        }
    printf("\n");
    AHashTableDestroy(htb1);
    LHashTableDestroy(htb2);
    end=clock();
    printf("耗时：%lf 秒",(double)(end-start)/CLOCKS_PER_SEC);
    return 0;
}