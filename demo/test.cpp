//
// Created by 徐绍骞 on 2022/3/2.
//
#include<cctype>
#include<cmath>
#include<cstring>
#include<cassert>
#include"../data_structure.h"
#define MAXDOCNAME 10
#define MAXWORDLEN 25
#define MAXSTRING "zzzzzzzzzzzzzzzzzzzzzzzz"
typedef struct record*docrecord;
typedef struct word*wordptr;
typedef struct dictionary*dictionaryptr;
struct record{
    int wordcount,docnum;
    docrecord nextdocrecord;
};
typedef struct word{
    char word[MAXWORDLEN];
    docrecord docrecords;
}word;
struct dictionary{
//    dictionaryptr*childs,sibling,parent;
//    word*words;
    dictionaryptr childs[10],sibling,parent;
    word words[10];
    bool isleaf;
};
void Traversedic(dictionaryptr,int);
void solve();
void Replacerecord(dictionaryptr,int,int);
dictionaryptr Storewordsteming(dictionaryptr,int,int);
dictionaryptr InitializeDictionary(dictionaryptr,bool,int);
dictionaryptr SearchDictionary(dictionaryptr,char*,int);
dictionaryptr InsertDictionary(dictionaryptr,char*,int,int);
dictionaryptr DoInsert(dictionaryptr,char*,int,int);
dictionaryptr Insertword(dictionaryptr,char*,int,int);
dictionaryptr Splitleaf(dictionaryptr,int);
dictionaryptr Splitnonleaf(dictionaryptr,int);
dictionaryptr Handleparent(dictionaryptr,dictionaryptr,wordptr,int);
dictionaryptr Getnewparent(dictionaryptr,dictionaryptr,wordptr,int);
void Calculatedistance(dictionaryptr,int,int,int,int);
void solve(){
    int docs,inqs,dicitionaryorder;
    scanf("%d",&docs);
    dicitionaryorder=3;
    char docname[docs][MAXDOCNAME];
    dictionaryptr root=nullptr;
    for(int docnum=0;docnum<docs;docnum++){
        scanf("%s",docname[docnum]);
        root=Storewordsteming(root,docnum,dicitionaryorder);
    }
    scanf("%d",&inqs);
    for(int i=0;i<inqs;i++){
        char inquirydoc1[MAXDOCNAME],inquirydoc2[MAXDOCNAME];
        int inqdocnum1=0,inqdocnum2=0;
        scanf("%s",inquirydoc1);
        scanf("%s",inquirydoc2);
        for(int j=0;j<docs;j++){
            if(!strcmp(docname[j],inquirydoc1))inqdocnum1=j;
            else if(!strcmp(docname[j],inquirydoc2))inqdocnum2=j;
        }
        Calculatedistance(root,i+1,inqdocnum1,inqdocnum2,dicitionaryorder);
    }
//    Traversedic(root,dicitionaryorder);
}
dictionaryptr Storewordsteming(dictionaryptr root,int docnum,int orders){
    int c;
    char word[MAXWORDLEN],*pc=word;
    while(!isalnum(c=getchar()));
    while(c!='#'){
        *pc++=(char)c;
        while(isalnum(c=getchar()))*pc++=(char)c;
        *pc='\0';
        if(strlen(word)>3){
            if(*(pc-2)=='e'&&(*(pc-1)=='d'||*(pc-1)=='s'))*(pc-2)='\0';
            else if(*(pc-3)=='i'&&(*(pc-2)=='e'&&*(pc-1)=='s'||*(pc-2)=='n'&&*(pc-1)=='g'))
                *(pc-3)='\0';
        }
        root=InsertDictionary(root,word,docnum,orders);
        pc=word;
        while(!isalnum(c=getchar())&&c!='#');
    }
    return root;
}
void Replacerecord(dictionaryptr dicnode,int wordpos,int docnum){
    word currentword=dicnode->words[wordpos];
    docrecord currentrecord=currentword.docrecords,nextrecord;
    while(currentrecord){
        if(currentrecord->docnum==docnum){
            currentrecord->wordcount++;
            break;
        }else if(!currentrecord->nextdocrecord){
            nextrecord=(docrecord)malloc(sizeof(struct record));
            nextrecord->docnum=docnum,nextrecord->wordcount=1;
            currentrecord->nextdocrecord=nextrecord;
            break;
        }else currentrecord=currentrecord->nextdocrecord;
    }
}
dictionaryptr InitializeDictionary(dictionaryptr root,bool isleaf,int orders){
    root=(dictionaryptr)malloc(sizeof(struct dictionary));
//    root->childs=(dictionaryptr*)malloc((orders+1)*sizeof(dictionaryptr));
//    root->words=(wordptr)malloc((orders+1)*sizeof(struct word));
    for(int i=0;i<=orders;i++){
        root->childs[i]=nullptr;
        strcpy(root->words[i].word,MAXSTRING);
        root->words[i].docrecords=(docrecord)malloc(sizeof(struct record));
        root->words[i].docrecords->wordcount=0,root->words[i].docrecords->nextdocrecord=nullptr;
    }
    root->sibling=root->parent=nullptr;
    root->isleaf=isleaf;
    return root;
}
dictionaryptr SearchDictionary(dictionaryptr root,char*searchword,int orders){
    if(!root)return nullptr;
    while(!root->isleaf){
        int childpos;
        for(childpos=0;strcmp(searchword,root->words[childpos].word)>=0;childpos++);
        root=SearchDictionary(root->childs[childpos],searchword,orders);
    }
    return root;
}
dictionaryptr InsertDictionary(dictionaryptr root,char*insertword,int docnum,int orders){
    dictionaryptr searchedleaf=SearchDictionary(root,insertword,orders);
    if(!searchedleaf)searchedleaf=InitializeDictionary(root,LEAF,orders);
    for(int i=0;i<orders;i++)if(!strcmp(searchedleaf->words[i].word,insertword)){
            Replacerecord(searchedleaf,i,docnum);
            return root;
    }
    root=DoInsert(searchedleaf,insertword,docnum,orders);
    return root;
}
dictionaryptr DoInsert(dictionaryptr root,char*insertword,int docnum,int orders){
    if(root->isleaf){
        root=Insertword(root,insertword,docnum,orders);
        if(strcmp(root->words[orders].word,MAXSTRING)!=0){
            dictionaryptr next=Splitleaf(root,orders);
            if(root->parent)root->parent=Handleparent(root,next,&(next->words[0]),orders);
            else root->parent=Getnewparent(root,next,&(next->words[0]),orders);
        }
        if(root->parent)root=DoInsert(root->parent,insertword,docnum,orders);
    }else{
        if(root->childs[orders]){
            dictionaryptr next=Splitnonleaf(root,orders);
            if(root->parent)root->parent=Handleparent(root,next,&(root->words[orders/2+1]),orders);
            else root->parent=Getnewparent(root,next,&(root->words[orders/2+1]),orders);
            for(int i=orders/2+1;i<=orders;i++){
                strcpy(root->words[i].word,MAXSTRING),root->words[i-1].docrecords=nullptr;
                root->childs[i]=nullptr;
            }
        }
        if(root->parent)root=DoInsert(root->parent,insertword,docnum,orders);
    }
    return root;
}
dictionaryptr Insertword(dictionaryptr leaf,char*insertword,int docnum,int orders){
    int insertpos;
    for(insertpos=0;strcmp(insertword,leaf->words[insertpos].word)>0;insertpos++);
    for(int i=orders;i>insertpos;i--)leaf->words[i]=leaf->words[i-1];
    strcpy(leaf->words[insertpos].word,insertword);
    leaf->words[insertpos].docrecords=(docrecord)malloc(sizeof(struct record));
    leaf->words[insertpos].docrecords->wordcount=0;
    leaf->words[insertpos].docrecords->docnum=docnum;
    Replacerecord(leaf,insertpos,docnum);
    return leaf;
}
dictionaryptr Splitleaf(dictionaryptr currentleaf,int orders){
    dictionaryptr nextleaf=nullptr;
    nextleaf=InitializeDictionary(nextleaf,LEAF,orders);
    nextleaf->sibling=currentleaf->sibling,currentleaf->sibling=nextleaf;
    for(int i=0;i<(orders+1)/2;i++){
        nextleaf->words[i]=currentleaf->words[i+orders/2+1];
        strcpy(currentleaf->words[i+orders/2+1].word,MAXSTRING);
        currentleaf->words[i+orders/2+1].docrecords=nullptr;
    }
    return nextleaf;
}
dictionaryptr Splitnonleaf(dictionaryptr currentnonleaf,int orders){
    dictionaryptr nextnonleaf=nullptr;
    nextnonleaf=InitializeDictionary(nextnonleaf,NONLEAF,orders);
    nextnonleaf->sibling=currentnonleaf->sibling,currentnonleaf->sibling=nextnonleaf;
    for(int i=0;i<(orders+1)/2;i++){
        nextnonleaf->childs[i]=currentnonleaf->childs[i+orders/2+1];
        nextnonleaf->words[i]=currentnonleaf->words[i+orders/2+1];
    }
    return nextnonleaf;
}
dictionaryptr Handleparent(dictionaryptr before,dictionaryptr next,wordptr newkey,int orders){
    dictionaryptr originparent=before->parent;
    int currentpos;
    for(currentpos=0;strcmp(before->words[0].word,originparent->words[currentpos].word)>=0
         ;currentpos++);
    for(int i=orders;i>currentpos+1;i++){
        originparent->childs[i]=originparent->childs[i-1];
        originparent->words[i-1]=originparent->words[i];
    }
    originparent->childs[currentpos+1]=next;originparent->words[currentpos]=*newkey;
    next->parent=originparent;
    return originparent;
}
dictionaryptr Getnewparent(dictionaryptr currentleaf,dictionaryptr nextleaf,wordptr parentkey,int orders){
    dictionaryptr newparent=nullptr;
    newparent=InitializeDictionary(newparent,NONLEAF,orders);
    newparent->words[0]=*parentkey;
    newparent->childs[0]=currentleaf,newparent->childs[1]=nextleaf;
    currentleaf->parent=nextleaf->parent=newparent;
    return newparent;
}
void Calculatedistance(dictionaryptr root,int casenum,int inqdoc1,int inqdoc2,int orders){
    double innersum=0,modulersum1=0,modulersum2=0,wordcount1,wordcount2;
    docrecord currentpos;
    while(!root->isleaf)root=root->childs[0];
    while(root){
        for(int i=0;i<orders;i++)if(strcmp(root->words[i].word,MAXSTRING)!=0){
                wordcount1=0,wordcount2=0;
                currentpos=root->words[i].docrecords;
                while(currentpos){
                    if(currentpos->docnum==inqdoc1)wordcount1=currentpos->wordcount;
                    else if(currentpos->docnum==inqdoc2)wordcount2=currentpos->wordcount;
                    currentpos=currentpos->nextdocrecord;
                }
                innersum+=wordcount1*wordcount2;
                if(wordcount1>0)modulersum1+=pow(wordcount1,2);
                if(wordcount2>0)modulersum2+=pow(wordcount2,2);
            }else break;
        root=root->sibling;
    }
    printf("Case %d: %.3f\n",casenum,innersum/sqrt(modulersum1*modulersum2));
}
void Traversedic(dictionaryptr root,int orders){
    if(root){
        printf("[%s: ",root->isleaf?"LEAF":"NONLEAF");
        bool flag=false;
        for(int i=0;i<orders;i++){
            if(strcmp(MAXSTRING,root->words[i].word)!=0){
                if(!flag){
                    printf("%s:",root->words[i].word);
                    flag=true;
                }else printf(",%s:",root->words[i].word);
                docrecord tmp=root->words[i].docrecords;
                while(tmp){
                    printf("%d ",tmp->docnum);
                    tmp=tmp->nextdocrecord;
                }
            }
        }
        printf("]");
        for(int i=0;i<orders;i++)if(root->childs[i])Traversedic(root->childs[i],orders);
    }
}