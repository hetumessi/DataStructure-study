//
// Created by 徐绍骞 on 2022/5/28.
//
#include "data_structure.h"
struct CursorNode Cursorspace[SPACESIZE];
static Cursorpos CursorAalloc();   //模拟堆内存分配，将Cursorspace的第一个单元作为freelist的表头
static void CursorFree(Cursorpos);
void CursorspaceInitialize(){                                            //0作为空指针地址
    memset(Cursorspace,0,sizeof(Cursorspace));
    for(int i=0;i<SPACESIZE-1;i++)Cursorspace[i].next=i+1;  //令每个next指向下一个存储单元
}    //初始状态下所有单元都是free的
Cursorpos CursorAalloc(){
    Cursorpos P;
    P=Cursorspace[0].next;         //将当前freelist中的第一个单元(不算头)分配出去
    Cursorspace[0].next=Cursorspace[P].next;  //freelist头指向被分配出去的单元的下一个单元
    return P;
}
void  CursorFree(Cursorpos P){
    Cursorspace[P].next=Cursorspace[0].next;  //释放的单元插入回到freelist表头之后
    Cursorspace[0].next=P;
}
bool ListIsEmpty(Cursorlist L){
    return Cursorspace[L].next==0;
}
bool ListisLast(Cursorpos P,Cursorlist L){
    return Cursorspace[P].next==0;
}
Cursorpos ListFind(Elementype X,Cursorlist L){
    Cursorpos P=Cursorspace[L].next;
    while(P&&Cursorspace[P].element!=X)P=Cursorspace[P].next;
    return P;   //当没有找到的时候返回0
}
Cursorlist ListDelete(Elementype X,Cursorlist L){  //删除的是元素值为X之后的那个单元
    Cursorpos P=ListFind(X,L),tmpos;
    if(!ListisLast(P,L)){
        tmpos=Cursorspace[P].next;
        Cursorspace[P].next=Cursorspace[tmpos].next;
        CursorFree(tmpos);
    }
    return L;
}
Cursorlist ListInsert(Elementype X,Cursorlist L){
    Cursorpos newnode=CursorAalloc(),P=ListFind(X,L);
    Cursorspace[newnode].element=X;
    if(ListIsEmpty(L))Cursorspace[L].next=newnode;
    else{
        Cursorspace[newnode].next=Cursorspace[P].next;
        Cursorspace[P].next=newnode;
    }
    return L;
}
Cursorlist ListDeleteList(Cursorlist L){
    Cursorpos P=Cursorspace[L].next,tmpos;
    while(P){
        tmpos=P;
        P=Cursorspace[P].next;
        CursorFree(tmpos);
    }
    Cursorspace[L].next=0;
    return L;
}
Cursorpos GetHead(Cursorlist L){
    return L;
}
Cursorpos GetFirst(Cursorlist L){
    return Cursorspace[L].next;
}
Elementype ListRetrieve(Cursorpos P){
    return Cursorspace[P].element;
}
Cursorpos ListAdvance(Cursorpos P,Cursorlist L,int step){
    int thistep=0;
    Cursorpos Adpos=L;
    while(Cursorspace[L].next!=P){
        if(thistep>=step)Adpos=Cursorspace[Adpos].next;
        L=Cursorspace[L].next;
        thistep++;
    }
    return Adpos;
}
Cursorlist ListReverse(Cursorlist L){
    Cursorpos P1,P2,tmp;
    if(ListIsEmpty(L))return L;
    else P1=Cursorspace[L].next,P2=Cursorspace[P1].next;
    while(P2){
        tmp=P1;
        P1=P2,P2=Cursorspace[P2].next;
        Cursorspace[P1].next=tmp;
    }
    Cursorspace[Cursorspace[L].next].next=0;
    Cursorspace[L].next=P1;
    return L;
}