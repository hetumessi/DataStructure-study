//
// Created by 徐绍骞 on 2022/5/25.
//
#include"data_structure.h"
#include<cmath>
static int getprime(int,enum KINDOFPRIME);
static Index detect(Index,int,HashTable_Array);
HashTable_Link LHashTableInitialize(HashTable_Link table, int tablesize){
    table=(HashTable_Link)malloc(sizeof(struct Hashtable_Link));
    if(tablesize<MINHASHTBSIZE)tablesize=MINHASHTBSIZE;
    table->capacity=getprime(tablesize,Larger);
    table->nodelist=(Hashnodeptr*)malloc(table->capacity*sizeof(Hashnodeptr));
    for(int i=0;i<table->capacity;i++)table->nodelist[i]=nullptr;
    return table;
}
HashTable_Array AHashTableInitialize(HashTable_Array table, int tablesize,enum KINDOFDETECT h2detect,double ldfactor){
    table=(HashTable_Array)malloc(sizeof(struct Hashtable_Array));
    if(tablesize<MINHASHTBSIZE)tablesize=MINHASHTBSIZE;
    table->capacity=getprime(tablesize,Larger);
    table->size=0,table->howtodetect=h2detect;
    table->loadfactor= ldfactor<DEFAULTLDFACTOR?ldfactor:DEFAULTLDFACTOR;
    table->nodeArray=(Hashnodeptr)malloc(table->capacity*sizeof(struct Listnode));
    for(int i=0;i<table->capacity;i++)table->nodeArray[i].info=Empty;
    return table;
}
void LHashTableDestroy(HashTable_Link table){
    Hashnodeptr curptr,prevptr;
    for(int i=0;i<table->capacity;i++){
        curptr=table->nodelist[i];
        while(curptr){
            prevptr=curptr;
            curptr=curptr->next;
            free(prevptr);
        }
    }
    free(table->nodelist);
    free(table);
    printf("散列表已销毁\n");
}
void AHashTableDestroy(HashTable_Array table){
    free(table->nodeArray);
    free(table);
    printf("散列表已销毁\n");
}
Hashnodeptr LHashTableFind(Elementype findkey, HashTable_Link table){
    assert(findkey>=0);
    Hashnodeptr curptr=table->nodelist[hash_int(findkey,table->capacity)];
    while(curptr&&curptr->key!=findkey)curptr=curptr->next;
    if(!curptr){
        printf("查找失败：查找值%d不在散列表中\n",findkey);
        return nullptr;
    }else return curptr;
}
Index AHashTableFind(Elementype findkey, HashTable_Array table){
    int collisionnum=0;
    Index curpos=hash_int(findkey,table->capacity);
    while(table->nodeArray[curpos].info!=Empty&&table->nodeArray[curpos].key!=findkey)
        curpos=detect(curpos,++collisionnum,table)%table->capacity;
    if(table->nodeArray[curpos].info!=Legitimate){
        printf("查找失败：查找值%d不在散列表中\n",findkey);
        return -1;
    }else return curpos;
}
HashTable_Link LHashTableInsert(Elementype insertkey, HashTable_Link table){
    Index insertpos=hash_int(insertkey,table->capacity);
    Hashnodeptr curptr,prevptr;
    curptr=prevptr=table->nodelist[insertpos];
    while(curptr&&curptr->key!=insertkey){
        prevptr=curptr;
        curptr=curptr->next;
    }
    if(!curptr){
        if(!prevptr){
            table->nodelist[insertpos]=(Hashnodeptr)malloc(sizeof(struct Hashtable_Link));
            table->nodelist[insertpos]->key=insertkey;
        }else{
            curptr=(Hashnodeptr)malloc(sizeof(struct Hashtable_Link));
            prevptr->next=curptr,curptr->next=nullptr;
            curptr->key=table->nodelist[insertpos]->key;
            table->nodelist[insertpos]->key=insertkey;
        }
    }else printf("插入失败：插入值%d已经在散列表中\n",insertkey);
    return table;
}
HashTable_Array AHashTableInsert(Elementype insertkey, HashTable_Array table){
    int collisionnum=0;
    Index insertpos=hash_int(insertkey,table->capacity);
    while(table->nodeArray[insertpos].info!=Empty&&table->nodeArray[insertpos].key!=insertkey)
        insertpos=detect(insertpos,++collisionnum,table)%table->capacity;
    if(table->nodeArray[insertpos].info!=Legitimate){
        table->nodeArray[insertpos].key=insertkey;
        table->nodeArray[insertpos].info=Legitimate;
        table->size++;
    }else printf("插入失败：插入值%d已经在散列表中\n",insertkey);
    if(table->size>table->capacity*table->loadfactor)table=Rehash(table);
    return table;
}
HashTable_Link LHashTableDelete(Elementype deletekey, HashTable_Link table){
    Index deletepos=hash_int(deletekey,table->capacity);
    Hashnodeptr prevptr,deleteptr;
    prevptr=deleteptr=table->nodelist[deletepos];
    while(deleteptr&&deleteptr->key!=deletekey)prevptr=deleteptr,deleteptr=deleteptr->next;
    if(!deleteptr)printf("删除失败：删除值%d不在散列表中\n",deletekey);
    else if(prevptr==deleteptr){
        table->nodelist[deletepos]=deleteptr->next;
        free(prevptr);
    }else{
        prevptr->next=deleteptr->next;
        free(deleteptr);
    }return table;
}
HashTable_Array AHashTableDelete(Elementype deletekey, HashTable_Array table){
    int collisionnum=0;
    Index deletepos=hash_int(deletekey,table->capacity);
    while(table->nodeArray[deletepos].info!=Empty&&table->nodeArray[deletepos].key!=deletekey)
        deletepos=detect(deletepos,++collisionnum,table)%table->capacity;
    if(table->nodeArray[deletepos].info==Legitimate){
        table->nodeArray[deletepos].info=Deleted;
        table->size--;
    }
    return table;
}
HashTable_Array Rehash(HashTable_Array table){
    printf("散列表扩容\n");
    Hashnodeptr oldnodeArray=table->nodeArray;
    table->capacity=getprime(table->capacity*2,Larger),table->size=0;
    table->nodeArray=(Hashnodeptr)malloc(table->capacity*sizeof(struct Listnode));
    for(int i=0;i<table->capacity;i++)table->nodeArray[i].info=Empty;
    if(table->nodeArray==oldnodeArray)return table;
    for(int i=0;i<table->capacity/2;i++)if(oldnodeArray[i].info==Legitimate)
            AHashTableInsert(oldnodeArray[i].key,table);
    free(oldnodeArray);
    return table;
}
int getprime(int size,enum KINDOFPRIME nextorlast){
    double ssqrt;
    while(true){
        ssqrt=sqrt(size);
        for(int i=2;i<=ssqrt;){
            if(!(size%i))break;
            if(++i>ssqrt)return size;
        }
        if(nextorlast)size--;
        else size++;
    }
}
Index detect(Index curpos,int collisionnum,HashTable_Array table){
    if(table->howtodetect==Linear)return curpos+collisionnum;
    else if(table->howtodetect==Square)return curpos+collisionnum*collisionnum;
    else if(table->howtodetect==Double){
        Elementype factor=getprime(table->capacity,Lesser);
        return curpos+collisionnum*(factor-hash_int(table->nodeArray[curpos].key,factor));
    }else return curpos;
}