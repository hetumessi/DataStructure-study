#include"data_structure.h"
#include<ctime>
int main(){
    clock_t start=clock(),end;

    end=clock();
    printf("耗时：%lf 秒",(double)(end-start)/CLOCKS_PER_SEC);
    return 0;
}