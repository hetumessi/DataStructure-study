//
// Created by 徐绍骞 on 2022/4/22.
//
#include<cstring>
#include<cmath>
//struct passage to store data
struct Passage{
    char Name[5];
    char Word[100];
    int weight[100];
};
struct Passage F[100];
double ModuleOfVector(int file); //two functions to calculate results
double MultOfVectors(int file1,int file2);
void solve1(){
    int NumOfFiles; //number of files.
    double result[100]; //store the result[i] for case i
    int i,j,m,n;
    int file1,file2,Case; //file number and case number
    char f1[5],f2[5]; //store the name of file1 and file2 (when compare)
    int flag;
    scanf("%d",&NumOfFiles); //input the number of files
    for(i=0;i<NumOfFiles;i++){
        //Input data in to Passage b
        scanf("%s",F[i].Name);
        getchar(); //This getchar() can free the '\n' in cache.
                      // Otherwise it will assign to the next scanf of getchar operation.
        j=0; //initialize input
        F[i].Word[j] = getchar();
        while(F[i].Word[j] != '#'){
            if(F[i].Word[j]=='\n' || F[i].Word[j]==' ')j--;
            j++;
            scanf("%c",&F[i].Word[j]);
        }
        int testi=(int)strlen(F[i].Word);
        if(F[i].Word[testi]=='e'){
            if(F[i].Word[testi+1]=='s'||F[i].Word[testi+1]=='d')
                F[i].Word[testi]='\0';
        }else if(F[i].Word[testi-1]=='i')
            if(F[i].Word[testi]=='e'&&F[i].Word[testi+1]=='s'||
               F[i].Word[testi]=='n'&&F[i].Word[testi+1]=='g')F[i].Word[testi-1]='\0';
        if(j == 0) //if a file is empty
            printf("File is null!\n");
        //Calcute the weight of word. If two word are the same, the later one's weight will be 0.
        for(m=0;m<j;m++){
            F[i].weight[m] = 0;
            for(n=0;n<j;n++){
                if(F[i].Word[m] == F[i].Word[n])
                    F[i].weight[m]++;
            }
            for(n=0;n<j;n++){
                if(F[i].Word[m] == F[i].Word[n])
                    if(F[i].weight[m] > 1 && m > n){
                        F[i].weight[m]=0;
                        break;
                    }
            }
        }
    }
    //input the number of case
    scanf("%d",&Case);
    for(i=0;i<Case;i++){
        //Input the name of two files. Find their number.
        scanf("%s%s",f1,f2);
        flag=0;
        for(j=0;j<NumOfFiles;j++){
            if(strcmp(F[j].Name,f1) == 0){
                file1=j;
                flag++;
            }
            if(strcmp(F[j].Name,f2) == 0){
                file2=j;
                flag++;
            }
        }
        if(flag != 2) //if any one in the two files doesn't exist. print "File not exist!\n "
            printf("File not exist!\n");
        result[i] = acos(MultOfVectors(file1,file2) /
                (ModuleOfVector(file1)*ModuleOfVector(file2)));
        printf("%f %f %f\n",MultOfVectors(file1,file2),ModuleOfVector(file1),ModuleOfVector(file2));
        //Use acos() to calculate the result
    }
    //print result of cases
    for(i=0;i<Case;i++){
        printf("Case %d: %.3lf\n",i+1 ,result[i]);
    }
    //print result in suitable form
}
//This function returns the module of vector
double ModuleOfVector(int file){
    int i=0;
    double module=0;
    while(F[file].Word[i] != '#'){
        module += F[file].weight[i]*F[file].weight[i];
        i++;
    }
    return sqrt(module);
}
//This function returns the multiplication of vectors
double MultOfVectors(int file1,int file2){
    int i,j;
    double mult=0;
    for(i=0;F[file1].Word[i] != '#';i++ )
        for(j=0;F[file2].Word[j] != '#';j++ ){
            if(F[file1].Word[i] == F[file2].Word[j]){
                mult += F[file1].weight[i] * F[file2].weight[j];
            }
        }
    return mult;
}