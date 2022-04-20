//
// Created by 徐绍骞 on 2022/2/19.
//

#ifndef ADVANCED_DATA_STRUCTURE_AND_ALGRITHM_ANALYSIS_DATA_STRUCTURE_H
#define ADVANCED_DATA_STRUCTURE_AND_ALGRITHM_ANALYSIS_DATA_STRUCTURE_H
#define INFINITY 65535
typedef int Elementype;
typedef struct AVLnode*AVLptr;
typedef struct Splaynode*Splayptr;
typedef struct RBnode*RBptr;
typedef struct Bplusnode*Bplusptr;
struct  AVLnode{
    AVLptr leftchild,rightchild;
    Elementype value;
    int bp;
};
struct Splaynode{
    Splayptr leftchild,rightchild;
    Elementype value;
};
enum color{RED,BLACK};
struct RBnode{
    RBptr leftchild,rightchild;
    Elementype value;
    bool color;
};
enum isleaf{NONLEAF,LEAF};
struct Bplusnode{
    Bplusptr*childs,sibling,parent;
    Elementype*keys;
    bool isleaf;
};
#endif //ADVANCED_DATA_STRUCTURE_AND_ALGRITHM_ANALYSIS_DATA_STRUCTURE_H
