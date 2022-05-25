//
// Created by 徐绍骞 on 2022/3/12.
//
#include"data_structure.h"
/* 自顶向下伸展树 */
Splayptr SplayNULLptr=nullptr;
Splayptr SplayInitialize(Splayptr root){
    if(!SplayNULLptr){
        SplayNULLptr=(Splayptr)malloc(sizeof(struct Splaynode));
        SplayNULLptr->leftchild=SplayNULLptr->rightchild=SplayNULLptr;
        SplayNULLptr->value=-MYINFINITY;
    }
    root=(Splayptr)malloc(sizeof(struct Splaynode));
    root->leftchild=root->rightchild=SplayNULLptr;
    return root;
}
void SplayTraverse(Splayptr root){
    if(root!=SplayNULLptr){
        SplayTraverse(root->leftchild);
        printf("%d ",root->value);
        SplayTraverse(root->rightchild);
    }
}
Splayptr SplayZag(Splayptr root){
    Splayptr leftchild=root->leftchild;
    root->leftchild=leftchild->rightchild;
    leftchild->rightchild=root;
    return leftchild;
}
Splayptr SplayZig(Splayptr root){
    Splayptr rightchild=root->rightchild;
    root->rightchild=rightchild->leftchild;
    rightchild->leftchild=root;
    return rightchild;
}
Splayptr SplaySplay(Splayptr root, Elementype accessvalue){
    Splayptr Header=nullptr,LTreeptr,RTreeptr;
    Header=SplayInitialize(Header);
    LTreeptr=RTreeptr=Header;
    if(!root)return SplayNULLptr;
    SplayNULLptr->value=accessvalue;
    while(root->value!=accessvalue)
        if(root->value>accessvalue){
            if(root->leftchild->value>accessvalue)root=SplayZag(root);
            if(root->leftchild==SplayNULLptr)break;
            RTreeptr->leftchild=root;
            RTreeptr=root;
            root=root->leftchild;
        }else{
            if(root->rightchild->value<accessvalue)root=SplayZig(root);
            if(root->rightchild==SplayNULLptr)break;
            LTreeptr->rightchild=root;
            LTreeptr=root;
            root=root->rightchild;
        }
    LTreeptr->rightchild=root->leftchild;
    RTreeptr->leftchild=root->rightchild;
    root->leftchild=Header->rightchild;
    root->rightchild=Header->leftchild;
    return root;
}
Splayptr SplayInsert(Splayptr root,Elementype insertvalue){
    root=SplaySplay(root,insertvalue);
    if(!root)root=SplayInitialize(root);
    else{
        if(root->value>insertvalue){
            Splayptr newroot=SplayNULLptr;
            newroot=SplayInitialize(newroot);
            newroot->value=insertvalue;
            newroot->rightchild=root,newroot->leftchild=root->leftchild;
            root->leftchild=SplayNULLptr;
            return newroot;
        }else if(root->value<insertvalue){
            Splayptr newroot=SplayNULLptr;
            newroot=SplayInitialize(newroot);
            newroot->value=insertvalue;
            newroot->leftchild=root,newroot->rightchild=root->rightchild;
            root->rightchild=SplayNULLptr;
            return newroot;
        }else printf("插入值：%d 已经在树中\n",insertvalue);
    }
    return root;
}
Splayptr SplayDelete(Splayptr root,Elementype deletevalue){
    root=SplaySplay(root,deletevalue);
    if(root==SplayNULLptr||root->value!=deletevalue){
        printf("删除值：%d 不在树中\n",deletevalue);
        return root;
    }
    Splayptr newroot;
    if(root->rightchild!=SplayNULLptr){
        newroot=SplaySplay(root->rightchild,deletevalue);
        newroot->leftchild=root->leftchild;
    }else newroot=root->leftchild;
    free(root);
    return newroot;
}
