#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"kcluster.h"

int main()
{
    Point pointset[N];
    FILE *fp;
    int count = 0;
    fp = fopen("geometry.txt", "r");
    if( fp == NULL){
        printf("file open failed!");
        return 1;
    }

    char title1[256]; char title2[256];
    fgets(title1, sizeof(title1), fp); fgets(title2, sizeof(title2), fp);

    while(count < MAX && fscanf(fp, "%d %d %*d %*d %*d", &pointset[count].cl, &pointset[count].num) == 2){
        count += 1;

    }

    fclose(fp);
    printf("read %d files\n", count);
    for(int i = 0; i < 20; i++){
        printf("%d %d\n", pointset[i].cl, pointset[i].num);
    }

    int cycle = 0;

    //手动给定质心
    Point centerset[K];
    for(int i = 0; i < K;i++){
        for(int j = 0; j < N; j++){
            if(pointset[j].cl == i){
                centerset[i].cl = i;
                centerset[i].num = pointset[j].num;
                continue;
            }
        }
    }

    cluster(pointset,centerset);
    int ob1 = objection(pointset, centerset);
    cycle += 1;

    updatecenter(pointset, centerset);
    cluster(pointset, centerset);
    int ob2 = objection(pointset, centerset);
    cycle += 1;

    //迭代结束时目标函数值不再变化
    while(abs(ob1-ob2) != 0){
        ob1 = ob2;
        updatecenter(pointset, centerset);
        cluster(pointset, centerset);
        ob2 = objection(pointset,centerset);
        cycle += 1; 
    }

    BubbleSort(pointset);

    printf("the cycle has been activated for %d rounds", cycle);

    //int actualclass = Clusternum(pointset);

    FILE *fp1 = fopen("output.txt","w");
    if(fp1 == NULL){
        printf("File open failed!");
        return 1;
    }
    //fprintf(fp1, "实际聚类数目为%d\n", actualclass);
    for(int i = 0; i < N; i++){
        fprintf(fp1, "%d %d\n", pointset[i].cl, pointset[i].num);
    }

    fclose(fp1);

    return 0;



    

  


}