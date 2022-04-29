//
// Created by 徐绍骞 on 2022/3/12.
//
Bplusptr BplusInitialize(Bplusptr root,int orders,bool isleaf){
    root=(Bplusptr)malloc(sizeof(struct Bplusnode));
    root->childs=(Bplusptr*)malloc((orders+1)*sizeof(Bplusptr));
    root->keys=(Elementype*)malloc((orders+1)*sizeof(Elementype));
    for(int i=0;i<orders+1;i++)root->childs[i]=nullptr,root->keys[i]=MYINFINITY;
    root->isleaf=isleaf;
    root->sibling=root->parent=nullptr;
    return root;
}
//假设m阶b+树的非叶子结点最多有m棵子树
Bplusptr BplusSearchdata(Bplusptr root,Elementype searchvalue,int orders){
    int i;
    if(!root->isleaf){
        for(i=0;root->keys[i]<=searchvalue&&i<orders-1;i++);
        root=BplusSearchdata(root->childs[i],searchvalue,orders);
    }
    return root;
}
Bplusptr BplusSearchrange(Bplusptr root,Elementype low,Elementype high,int orders){
    Bplusptr start,end;
    int count=0,flag=0;
    start=BplusSearchdata(root,low,orders);
    end=BplusSearchdata(root,high,orders);
    root=start;
    while(start){
        printf("[");
        for(int i=0;start->keys[i]<MYINFINITY;i++){
            if(!flag){
                printf("%d",start->keys[i]);
                flag=1;
            }else printf(",%d",start->keys[i]);
        }
        printf("]");
        if(start->sibling)start=start->sibling;
        count++;
        if(start==end)break;
    }
    printf("\n[%d,%d]区间内共找到%d个结点\n",low,high,count);
    return root;
}
void BplusTraverse(Bplusptr root,int orders){
    if(!root)return;
    bool flag=false;
    printf("[");
    for(int j=0;j<orders;j++)if(root->keys[j]<MYINFINITY){
            if(!flag){
                printf("%d",root->keys[j]);
                flag=true;
            }else printf(",%d",root->keys[j]);
        }
    printf("]");
    for(int i=0;i<orders;i++)if(root->childs[i])BplusTraverse(root->childs[i],orders);
}
void BplusTravelleaves(Bplusptr root,int orders){
    if(!root)return;
    while(!root->isleaf)root=root->childs[0];
    while(root){
        bool flag=false;
        printf("[");
        for(int i=0;root->keys[i]<MYINFINITY;i++){
            if(!flag){
                printf("%d",root->keys[i]);
                flag=true;
            }else printf(",%d",root->keys[i]);
        }
        printf("]");
        root=root->sibling;
    }
    printf("\n");
}
Bplusptr BplusInsert(Bplusptr root,Elementype insertvalue,int orders){
    if(!root)root=BplusInitialize(root,orders,LEAF);
    Bplusptr insertleaf=BplusSearchdata(root,insertvalue,orders);
    for(int i=0;i<orders;i++)if(insertleaf->keys[i]==insertvalue){
            printf("插入值：%d 已经在树中\n",insertvalue);
            return root;
    }
    root=DoInsert(insertleaf,insertvalue,orders);
    return root;
}
Bplusptr DoInsert(Bplusptr root,Elementype insertvalue,int orders){
    if(root->isleaf){
        root=LeafInsert(root,insertvalue,orders);
        if(root->keys[orders]!=MYINFINITY){
            Bplusptr next=LeafSplit(root,orders);
            if(root->parent)root->parent=HandleParent(root,next,orders);
            else root->parent=BuildNewParent(root,next,next->keys[0],orders);
        }
        if(root->parent)root=DoInsert(root->parent,insertvalue,orders);
    }else{
        if(root->keys[orders-1]!=MYINFINITY){
            Bplusptr next=NonleafSplit(root,orders);
            if(root->parent)root->parent=HandleParent(root,next,orders);
            else root->parent=BuildNewParent(root,next,root->keys[orders/2],orders);
            for(int i=1+orders/2;i<=orders;i++)root->keys[i-1]=MYINFINITY,root->childs[i]=nullptr;
        }
        if(root->parent)root=DoInsert(root->parent,insertvalue,orders);
    }
    return root;
}
Bplusptr LeafInsert(Bplusptr leaf,Elementype insertvalue,int orders){
    int insertpos=0;
    for(;leaf->keys[insertpos]<insertvalue&&insertpos<orders;insertpos++);
    for(int i=orders;i>insertpos;i--)leaf->keys[i]=leaf->keys[i-1];
    leaf->keys[insertpos]=insertvalue;
    return leaf;
}
Bplusptr LeafSplit(Bplusptr leaf,int orders){
    Bplusptr nextleaf=nullptr;
    nextleaf=BplusInitialize(nextleaf,orders,LEAF);
    nextleaf->sibling=leaf->sibling,leaf->sibling=nextleaf;
    for(int i=0;i<(orders+1)/2;i++){
        nextleaf->keys[i]=leaf->keys[i+1+orders/2];
        leaf->keys[i+1+orders/2]=MYINFINITY;
    }
    return nextleaf;
}
/*注意这里原本的非叶结点分裂以后keys先不更新，原因是需要使用root->keys[orders/2]
 * 作为parent的keys(其实就是分裂出去的叶子结点中最小的那个keys)，这个值在处理完
 * parent以后再更新     */
Bplusptr NonleafSplit(Bplusptr nonleaf,int orders){
    Bplusptr nextnonleaf=nullptr;
    nextnonleaf=BplusInitialize(nextnonleaf,orders,NONLEAF);
    for(int i=0;i<(orders+1)/2;i++){
        nextnonleaf->childs[i]=nonleaf->childs[i+1+orders/2];
        nextnonleaf->keys[i]=nonleaf->keys[i+1+orders/2];
    }
    return nextnonleaf;
}
Bplusptr HandleParent(Bplusptr present,Bplusptr next,int orders){
    int insertpos;
    Bplusptr common=present->parent;
    for(insertpos=0;common->keys[insertpos]<=present->keys[0];insertpos++);
    for(int i=orders;i>insertpos+1;i--){
        common->childs[i]=common->childs[i-1];
        common->keys[i]=common->keys[i-1];
    }
    common->childs[insertpos+1]=next,next->parent=common;
    for(int i=0;i<orders;i++)if(common->childs[i+1])
            common->keys[i]=common->childs[i+1]->keys[0];
    return common;
}
Bplusptr BuildNewParent(Bplusptr child,Bplusptr next,Elementype parentfirstkey,int orders){
    Bplusptr newparent=nullptr;
    newparent=BplusInitialize(newparent,orders,NONLEAF);
    child->parent=next->parent=newparent;
    newparent->keys[0]=parentfirstkey;
    newparent->childs[0]=child,newparent->childs[1]=next;
    return newparent;
}