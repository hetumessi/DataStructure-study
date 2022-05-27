#include"data_structure.h"
#include<ctime>
int main(){
    clock_t start=clock(),end;
    srand(time(nullptr));
    int testnum=8,testdata1[testnum];
    HashTable_Link htb=nullptr;
    Hashnodeptr travptr;
    htb=LHashTableInitialize(htb,4);
    for(int i=0;i<testnum;i++){
        testdata1[i]=rand()%100;
        printf("%d ",testdata1[i]);
        htb=LHashTableInsert(testdata1[i],htb);
    }
    printf("\n");
    for(int i=0;i<htb->capacity;i++)if(htb->nodelist[i]){
            travptr=htb->nodelist[i];
            while(travptr){
                printf("%d ",travptr->key);
                travptr=travptr->next;
            }
            printf("\n");
    }
    LHashTableFind(3432,htb);
    LHashTableFind(testdata1[4],htb);
    LHashTableDelete(testdata1[4],htb);
    LHashTableFind(testdata1[4],htb);
    for(int i=0;i<htb->capacity;i++)if(htb->nodelist[i]){
            travptr=htb->nodelist[i];
            while(travptr){
                printf("%d ",travptr->key);
                travptr=travptr->next;
            }
            printf("\n");
        }
    end=clock();
    printf("耗时：%lf 秒",(double)(end-start)/CLOCKS_PER_SEC);
    return 0;
}