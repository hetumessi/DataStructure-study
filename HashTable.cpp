//
// Created by 徐绍骞 on 2022/5/25.
//
#include"data_structure.h"
#include<cmath>
static int nextprime(int);
HashTable HashTableInitialize(HashTable table,int tablesize){
    table=(HashTable)malloc(sizeof(struct Hashtable));
    if(tablesize<MINHASHTBSIZE)tablesize=MINHASHTBSIZE;
    table->capacity=nextprime(tablesize);
    table->head=table;
    table->nodelist=(Hashnodeptr*)malloc(table->capacity*sizeof(Hashnodeptr));
    return table->head;
}
void DestroyHashTable(HashTable table){
    Hashnodeptr curptr,prevptr;
    for(int i=0;i<table->capacity;i++){
        curptr=table->nodelist[i];
        while(curptr){
            prevptr=curptr;
            curptr=curptr->next;
            free(prevptr);
        }
    }
    free(table->head);
}
Hashnodeptr HashTableFind(Elementype findkey,HashTable table){
    Hashnodeptr curptr=table->nodelist[hash_int(findkey,table->capacity)];
    while(curptr&&curptr->key!=findkey)curptr=curptr->next;
    if(!curptr){
        printf("查找失败：不存在该键值\n");
        return nullptr;
    }else return curptr;
}
HashTable HashTableInsert(Elementype insertkey,HashTable table){
    Hashnodeptr curptr=table->nodelist[hash_int(insertkey,table->capacity)];
    while(curptr&&curptr->key!=insertkey)curptr=curptr->next;
    if(!curptr){
        curptr=(Hashnodeptr)malloc(sizeof(struct Listnode));
        curptr->key=insertkey;
        curptr->next=nullptr;
    }else printf("插入失败：散列表已存在该键值\n");
    return table->head;
}
int nextprime(int size){
    return size;
}