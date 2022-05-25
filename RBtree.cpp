//
// Created by 徐绍骞 on 2022/3/9.
//
#include"data_structure.h"
/* 自顶向下红黑树 */
//通过定义一个头指针，可以找到树根(必须为黑)
//自顶向下建树，结点不记录其父结点信息
//因此需要特别定义几个指针用于记录当前结点及其父、祖父、曾祖结点
static RBptr RBNULLptr=nullptr,current,parent,sibling,grand,great;
RBptr RBInitialize(RBptr root,bool color){
    root=(RBptr)malloc(sizeof(struct RBnode));
    root->value=-MYINFINITY,root->color=color;
    if(!RBNULLptr){
        RBNULLptr=(RBptr)malloc(sizeof(struct RBnode));
        RBNULLptr->value=MYINFINITY,RBNULLptr->color=BLACK;
        RBNULLptr->leftchild=RBNULLptr->rightchild=RBNULLptr;
    }
    root->leftchild=root->rightchild=RBNULLptr;
    return root;
}
void RBtraverse(RBptr root){
    if(root!=RBNULLptr){
        printf(("%d"),root->value);
        RBtraverse(root->leftchild);
        RBtraverse(root->rightchild);
    }
}
RBptr RBFindMax(RBptr root){
    while(root->rightchild!=RBNULLptr)root=root->rightchild;
    return root;
}
RBptr RBFindMin(RBptr root){
    if(root->leftchild!=RBNULLptr)root=RBFindMin(root->leftchild);
    return root;
}
RBptr RBRotate(RBptr grandparent,Elementype accessvalue){
    if(grandparent->value>accessvalue)return
        grandparent->leftchild=grandparent->leftchild->value>accessvalue?
        SingleLeftRotate(grandparent->leftchild):SingleRightRotate(grandparent->leftchild);
    else if(grandparent->value<accessvalue)return
        grandparent->rightchild=grandparent->rightchild->value<accessvalue?
        SingleRightRotate(grandparent->rightchild):SingleLeftRotate(grandparent->rightchild);
    return grandparent;
}
RBptr SingleLeftRotate(RBptr root){
    RBptr leftchild=root->leftchild;
    root->leftchild=leftchild->rightchild;
    leftchild->rightchild=root;
    return leftchild;
}
RBptr SingleRightRotate(RBptr root){
    RBptr rightchild=root->rightchild;
    root->rightchild=rightchild->leftchild;
    rightchild->leftchild=root;
    return rightchild;
}
void RBHandleInsert(RBptr root,Elementype accessvalue){
    current->color=RED,current->leftchild->color=current->rightchild->color=BLACK;
    if(!parent->color){
        grand->color=RED;
        if((accessvalue>parent->value)!=(accessvalue>grand->value))
            parent=RBRotate(grand,accessvalue);
        current=RBRotate(great,accessvalue);
        current->color=BLACK;
    }
    root->rightchild->color=BLACK;
}
RBptr RBInsert(RBptr root,Elementype insertvalue){
    RBNULLptr->value=insertvalue;
    great=grand=parent=current=root;
    while(current->value!=insertvalue){
        great=grand,grand=parent,parent=current;
        if(current->value>insertvalue)current=parent->leftchild;
        else current=parent->rightchild;
        if(!current->leftchild->color&&!current->rightchild->color)
            RBHandleInsert(root,insertvalue);
    }
    if(current!=RBNULLptr){
        printf("插入值: %d 已经在树中\n",insertvalue);
        return root;
    }else{
        current=RBInitialize(current,RED);
        current->value=insertvalue;
        if(parent->value>insertvalue)parent->leftchild=current;
        else parent->rightchild=current;
    }
    RBHandleInsert(root,insertvalue);
    return root;
}
void RBHandleDelete(){
    int reorientvalue;
    current->color=RED;
    if(sibling==RBNULLptr||!sibling->leftchild->color&&!sibling->rightchild->color){
        if(sibling!=RBNULLptr)sibling->color=RED;
        parent->color=BLACK;
    }else{
        if(!sibling->leftchild->color)reorientvalue=sibling->leftchild->value;
        else reorientvalue=sibling->rightchild->value;
        if((parent->value>sibling->value)!=(sibling->value>reorientvalue))
            sibling=RBRotate(parent,reorientvalue);
        grand=RBRotate(grand,sibling->value);
        grand->color=RED,grand->leftchild->color=grand->rightchild->color=BLACK;
        sibling=sibling->value>parent->value?parent->rightchild:parent->leftchild;
    }
}
RBptr RBDelete(RBptr root,Elementype deletevalue){
    RBptr deleteptr;
    grand=parent=root,sibling=parent->leftchild,current=parent->rightchild;
    while(current!=RBNULLptr){
        if(current->leftchild->color&&current->rightchild->color)RBHandleDelete();
        else{
            grand=parent,parent=current;
            if(current->value>deletevalue)current=parent->leftchild,sibling=parent->rightchild;
            else deleteptr=current,current=parent->rightchild,sibling=parent->leftchild;
            if(current->color){
                sibling->color=BLACK,parent->color=RED;
                grand=RBRotate(grand,sibling->value);
                sibling=sibling->value>parent->value?parent->rightchild:parent->leftchild;
            }
            continue;
        }
        grand=parent,parent=current;
        if(current->value>deletevalue)current=parent->leftchild,sibling=parent->rightchild;
        else deleteptr=current,current=parent->rightchild,sibling=parent->leftchild;
    }
    if(deleteptr == RBNULLptr || deleteptr->value != deletevalue){
        printf("删除值: %d 不在树中\n",deletevalue);
        return root;
    }else{
        deleteptr->value=parent->value;
        if(grand->value>parent->value)grand->leftchild=RBNULLptr;
        else grand->rightchild=RBNULLptr;
    }
    free(parent);
    root->rightchild->color=BLACK;
    return root;
}