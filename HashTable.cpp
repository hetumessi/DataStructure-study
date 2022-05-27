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
void LDestroyHashTable(HashTable_Link table){
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
void ADestroyHashTable(HashTable_Array table){
    free(table->nodeArray);
    free(table);
    printf("散列表已销毁\n");
}
Hashnodeptr LHashTableFind(Elementype findkey, HashTable_Link table){
    assert(findkey>0);
    Hashnodeptr curptr=table->nodelist[hash_int(findkey,table->capacity)];
    while(curptr&&curptr->key!=findkey)curptr=curptr->next;
    if(!curptr){
        printf("查找失败：不存在该键值\n");
        return nullptr;
    }else return curptr;
}
Index AHashTableFind(Elementype findkey, HashTable_Array table){
    int collisionnum=0;
    Index curpos=hash_int(findkey,table->capacity);
    while(table->nodeArray[curpos].info!=Empty&&table->nodeArray[curpos].key!=findkey)
        curpos=detect(curpos,++collisionnum,table)%table->capacity;
    if(table->nodeArray[curpos].info!=Legitimate){
        printf("查找失败：不存在该键值\n");
        return -1;
    }else return curpos;
}
HashTable_Link LHashTableInsert(Elementype insertkey, HashTable_Link table){
    Index insertpos=hash_int(insertkey,table->capacity);
    Hashnodeptr curptr=table->nodelist[insertpos];
    while(curptr&&curptr->next&&curptr->next->key!=insertkey)curptr=curptr->next;
    if(!curptr){
        table->nodelist[insertpos]=(Hashnodeptr)malloc(sizeof(struct Listnode));
        table->nodelist[insertpos]->key=insertkey;
    }else if(!curptr->next){
        curptr->next=(Hashnodeptr)malloc(sizeof(struct Listnode));
        curptr->next->key=table->nodelist[insertpos]->key;
        table->nodelist[insertpos]->key=insertkey;
        curptr->next->next=nullptr;
    }else printf("插入失败：散列表已存在该键值\n");
    return table;
}
HashTable_Array AHashTableInsert(Elementype insertkey, HashTable_Array table){
    int collisionnum=0;
    Index insertpos=hash_int(insertkey,table->capacity);
    while(table->nodeArray[insertpos].info!=Empty&&table->nodeArray[insertpos].key!=insertpos)
        insertpos=detect(insertpos,++collisionnum,table)%table->capacity;
    if(table->nodeArray[insertpos].info!=Legitimate)
        table->nodeArray[insertpos].key=insertkey,table->size++;
    else printf("插入失败：插入值已经在散列表中\n");
    if(table->size>table->loadfactor)table=Rehash(table);
    return table;
}
HashTable_Link LHashTableDelete(Elementype deletekey, HashTable_Link table){
    Index deletepos=hash_int(deletekey,table->capacity);
    Hashnodeptr prevptr,deleteptr;
    prevptr=deleteptr=table->nodelist[deletepos];
    while(deleteptr&&deleteptr->key!=deletekey)prevptr=deleteptr,deleteptr=deleteptr->next;
    if(!deleteptr)printf("删除失败：删除值不在散列表中\n");
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
    printf("创建新的散列表\n");
    Hashnodeptr oldnodeArray=table->nodeArray;
    table->nodeArray=(Hashnodeptr)malloc(table->capacity*2*sizeof(struct Listnode));
    for(int i=0;i<table->capacity;i++)if(oldnodeArray[i].info==Legitimate)
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