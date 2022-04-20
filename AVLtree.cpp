//
// Created by 徐绍骞 on 2022/2/19.
//
#include"data_structure.h"
#include<cstdlib>
int Getheight(AVLptr);
void AVLTraverse(AVLptr);
AVLptr AVLFindvalue(AVLptr,Elementype);
AVLptr AVLFindmin(AVLptr);
AVLptr AVLFindmax(AVLptr);
AVLptr LLSingleRotation(AVLptr);
AVLptr RRSingleRotation(AVLptr);
AVLptr LRDoubleRotation(AVLptr);
AVLptr RLDoubleRotation(AVLptr);
AVLptr AVLInsert(AVLptr,Elementype);
AVLptr AVLDelete(AVLptr,Elementype);
Splayptr SplayInitialize(Splayptr);
void SplayTraverse(Splayptr);
Splayptr SplayZig(Splayptr);
Splayptr SplayZag(Splayptr);
Splayptr SplaySplay(Splayptr, Elementype);
Splayptr SplayInsert(Splayptr,Elementype);
Splayptr SplayDelete(Splayptr,Elementype);
/* AVL树 */
int Getheight(AVLptr root){
    if(root){
        int leftheight,rightheight,higherheight;
        leftheight=Getheight(root->leftchild);
        rightheight=Getheight(root->rightchild);
        higherheight=leftheight>=rightheight?leftheight:rightheight;
        return higherheight+1;
    }
    return 0;
}
void AVLTraverse(AVLptr root){
    if(root){
        printf("%d ",root->value);
        AVLTraverse(root->leftchild);
        AVLTraverse(root->rightchild);
    }
}
AVLptr AVLFindvalue(AVLptr root,Elementype findvalue){
    if(!root){
        printf("找不到具有该值的结点");
        return nullptr;
    }
    else if(root->value>findvalue)root=AVLFindvalue(root->leftchild,findvalue);
    else if(root->value<findvalue)root=AVLFindvalue(root->rightchild,findvalue);
    return root;
}
AVLptr AVLFindmin(AVLptr root){
    if(!root)return nullptr;
    while(root->leftchild)root=root->leftchild;
    return root;
}
AVLptr AVLFindmax(AVLptr root){
    if(!root)return nullptr;
    if(root->rightchild)root=AVLFindmax(root->rightchild);
    return root;
}
AVLptr LLSingleRotation(AVLptr root){
    AVLptr tmptr=root->leftchild;
    root->leftchild=tmptr->rightchild;
    tmptr->rightchild=root;
    root=tmptr;
    return root;
}
AVLptr RRSingleRotation(AVLptr root){
    AVLptr tmptr=root->rightchild;
    root->rightchild=tmptr->leftchild;
    tmptr->leftchild=root;
    root=tmptr;
    return root;
}
AVLptr LRDoubleRotation(AVLptr root){
    root->leftchild=RRSingleRotation(root->leftchild);
    return LLSingleRotation(root);
}
AVLptr RLDoubleRotation(AVLptr root){
    root->rightchild=LLSingleRotation(root->rightchild);
    return RRSingleRotation(root);
}
AVLptr AVLInsert(AVLptr root, Elementype insertvalue){
    int leftheight=0,rightheight=0;
    if(!root){
        root=(AVLptr)malloc(sizeof(struct AVLnode));
        root->leftchild=root->rightchild=nullptr;
        root->value=insertvalue,root->bp=0;
    }else if(root->value>insertvalue){
        root->leftchild=AVLInsert(root->leftchild,insertvalue);
        if(root->leftchild)leftheight=Getheight(root->leftchild);
        if(root->rightchild)rightheight=Getheight(root->rightchild);
        root->bp=leftheight-rightheight;
        if(root->bp<-1||root->bp>1){
            if(root->leftchild->value>insertvalue)root=LLSingleRotation(root);
            else root=LRDoubleRotation(root);
        }
    }else if(root->value<insertvalue){
        root->rightchild=AVLInsert(root->rightchild,insertvalue);
        if(root->leftchild)leftheight=Getheight(root->leftchild);
        if(root->rightchild)rightheight=Getheight(root->rightchild);
        root->bp=leftheight-rightheight;
        if(root->bp<-1||root->bp>1){
            if(root->rightchild->value<insertvalue)root=RRSingleRotation(root);
            else root=RLDoubleRotation(root);
        }
    }else printf("插入值：%d 已经在树中\n",insertvalue);
    return root;
}
AVLptr AVLDelete(AVLptr root,Elementype deletevalue){
    if(!root){
        printf("删除值：%d 不在树中\n",deletevalue);
        return nullptr;
    }else if(root->value>deletevalue)root->leftchild=AVLDelete(root->leftchild,deletevalue);
    else if(root->value<deletevalue)root->rightchild=AVLDelete(root->rightchild,deletevalue);
    else{
        if(Getheight(root)==1)root=nullptr;
        else if(Getheight(root->rightchild)>=Getheight(root->leftchild)){
            root->value=AVLFindmin(root->rightchild)->value;
            root->rightchild=AVLDelete(root->rightchild,root->value);
        }else{
            root->value=AVLFindmax(root->leftchild)->value;
            root->leftchild=AVLDelete(root->leftchild,root->value);
        }
    }
    return root;
}
