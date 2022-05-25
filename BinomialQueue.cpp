//
// Created by 徐绍骞 on 2022/4/28.
//
#include"data_structure.h"
#include<cmath>
void BinTreeTraverse(BinTree root){
    if(root){
        printf("%d ",root->value);
        BinTreeTraverse(root->firstchild);
        BinTreeTraverse(root->sibling);
    }
}
BinTree TreeInitialize(BinTree root,Elementype initializevalue){
    root=(BinTree)malloc(sizeof(struct Binode));
    root->value=initializevalue;
    root->firstchild=root->sibling=root->parent=nullptr;
    return root;
}
BinomialQueue BinomialQueueInitialize(BinomialQueue queue){
    queue=(BinomialQueue)malloc(sizeof(struct BinCollection));
    queue->currentsize=0;
    queue->Forest=(BinTree*)malloc(MAXTREES*sizeof(BinTree));
    return queue;
}
BinTree TreesCombine(BinTree root1,BinTree root2){
    if(!root1)return root2;
    else if(!root2)return root1;
    else if(root1->value>root2->value)return TreesCombine(root2,root1);
    root2->sibling=root1->firstchild;
    root1->firstchild=root2;
    root2->parent=root1;
    return root1;
}
BinomialQueue ForestMerge(BinomialQueue queue1,BinomialQueue queue2){
    BinTree T1,T2,Carry=nullptr;
    int totalsize=queue1->currentsize+queue2->currentsize;
    if(totalsize>MAXTREES){
        printf("合并失败：超过最大容量\n");
        return nullptr;
    }
    for(int treenum=0;queue1->currentsize<totalsize;treenum++){
        T1=queue1->Forest[treenum],T2=queue2->Forest[treenum];
        switch((T1!=nullptr)+2*(T2!=nullptr)+4*(Carry!=nullptr)){
            case 0:case 1:break;
            case 2:
                queue2->Forest[treenum]=nullptr;
                queue1->Forest[treenum]=T2;
                queue1->currentsize+=1<<treenum;
                break;
            case 3:
                Carry=TreesCombine(T1,T2);
                queue1->Forest[treenum]=queue2->Forest[treenum]=nullptr;
                queue1->currentsize-=1<<treenum;
                break;
            case 4:
                queue1->Forest[treenum]=Carry;
                Carry=nullptr;
                queue1->currentsize+=1<<treenum;
                break;
            case 5:
                Carry=TreesCombine(T1,Carry);
                queue1->Forest[treenum]=nullptr;
                queue1->currentsize-=1<<treenum;
                break;
            default:
                Carry=TreesCombine(T2,Carry);
                queue2->Forest[treenum]=nullptr;
                break;
        }
    }
    return queue1;
}
BinomialQueue BinomialQueueInsert(BinomialQueue queue,Elementype insertvalue){
    if(queue->currentsize>=MAXTREES){
        printf("插入失败：二项队列已满\n");
        return queue;
    }
    int emptynum;
    BinTree Carry=nullptr;
    Carry=TreeInitialize(Carry,insertvalue);
    for(emptynum=0;queue->Forest[emptynum];emptynum++);
    for(int i=0;i<emptynum;i++){
        Carry=TreesCombine(queue->Forest[i],Carry);
        queue->Forest[i]=nullptr;
    }
    queue->Forest[emptynum]=Carry;
    queue->currentsize++;
    return queue;
}
Elementype BinomialQueueDeleteMin(BinomialQueue queue){
    if(BinomialQueueIsEmpty(queue)){
        printf("删除失败：空二项队列\n");
        return -MYINFINITY;
    }
    int deletenum=0;
    Elementype deletevalue=MYINFINITY;
    for(int i=0;i<=(int)log2((double)queue->currentsize);i++)if(deletevalue>queue->Forest[i]->value)
        deletevalue=queue->Forest[i]->value,deletenum=i;
    queue->currentsize-=1<<deletenum;
    BinTree deletenode=queue->Forest[deletenum],tmpnode=deletenode->firstchild;
    queue->Forest[deletenum]=nullptr;
    free(deletenode);
    BinomialQueue newqueue=nullptr;
    newqueue= BinomialQueueInitialize(newqueue);
    //注意每棵二项树的结点数为2^k(10...0), 删除一个结点后分解为0到k-1个二项树(01...1)
    for(int i=deletenum-1;i>=0;i--){
        newqueue->Forest[i]=tmpnode;
        tmpnode=tmpnode->sibling;
        newqueue->Forest[i]->sibling=nullptr;
    }
    newqueue->currentsize=(1<<deletenum)-1;
    ForestMerge(queue,newqueue);
    return deletevalue;
}
BinTree BinTreeDecreaseKey(BinTree decnode,Elementype delta){
    decnode->value-=delta;
    BinTreePercolateUp(decnode);
    return decnode;
}
BinTree BinTreePercolateUp(BinTree handlenode){
    BinTree hparent=handlenode->parent;
    Elementype handlevalue=handlenode->value;
    while(hparent&&handlevalue<hparent->value){
        handlenode->value=hparent->value;
        handlenode=hparent;
        hparent=handlenode->parent;
    }
    handlenode->value=handlevalue;
    return handlenode;
}
bool BinomialQueueIsEmpty(BinomialQueue queue){
    return !queue->currentsize;
}