#include<ctime>
#include<cstdio>
#include"AVLtree.cpp"
#include"Splaytree.cpp"
#include"RBtree.cpp"
#include"Bplustree.cpp"
#include"test.cpp"
#include"demo.cpp"
int main(){
    clock_t start=clock(),end;
    test_lfu_cache();
    end=clock();
    printf("耗时：%lf 秒",(double)(end-start)/CLOCKS_PER_SEC);
    return 0;
}