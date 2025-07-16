#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"kcluster02.h"
#include"extract.h"
//注：2版本的程序出现某行（120）之后num全化为0的情况，经过排查问题在于多个头文件中对大数N的定义进行了修改后与初始定义不符导致的循环越界问题；
int main()
{
    Raw_Point *rawset;
    rawset = malloc(Total_rawPt * sizeof(Raw_Point));
    if(rawset == NULL){
        printf("Memory allocation failed!");
        exit(EXIT_FAILURE);
    }
    FILE *fp;
    int count = 0;
    fp = fopen("geometry.txt", "r");
    if( fp == NULL){
        printf("file open failed!");
        return 1;
    }

    char title1[256]; char title2[256];
    fgets(title1, sizeof(title1), fp); fgets(title2, sizeof(title2), fp);

    while(count < MAX && fscanf(fp, "%d %s %*d %*d %*d", &rawset[count].index, &rawset[count].relate_index) == 2){
        count += 1;

    }

    fclose(fp);
    // printf("read %d files\n", count);
    // for(int i = 0; i < 10; i++){
    //     printf("%d %s\n", rawset[i].index, rawset[i].relate_index);
    // }

// //监测1：输出原始读取点文件rawset.txt
//     FILE *fp0 = fopen("rawpoint.txt","w");
//     if(fp0 == NULL){
//         printf("File open failed!");
//         return 1;
//     }
//     //fprintf(fp1, "实际聚类数目为%d\n", actualclass);
//     for(int i = 0; i < Total_rawPt; i++){
//         fprintf(fp0, "%d %s\n", rawset[i].index, rawset[i].relate_index);
//     }

//     fclose(fp0);


//提取了子图的序号以及关联图片数量
    Subgraph* subgraphset;
    subgraphset = getsubgraphset(rawset);
// //check02: file"subgraph.txt"
//     FILE *fp02 = fopen("subgraph.txt","w");
//     if(fp02 == NULL){
//         printf("file open failed!");
//         exit(EXIT_FAILURE);
//     }
//     fprintf(fp02,"index\tnumber of relative images\n");
//     for(int i = 0; i < Total_Sub; i++){
//         fprintf(fp02,"%d\t%-10d\n", (subgraphset+i)->index, (subgraphset + i)->relate_num);
//     }
//     fclose(fp02);

//组合相邻的4张子图为一张图
    Graph* graphset;
    graphset = combinesubgra(subgraphset);
    // for(int i = 0; i < 10; i++){
    //     printf("第%d组图片总共与%d张图片相关联\n",(graphset + i)->Groupnum,(graphset + i)->total_rel_num);
    // }
//check03:"conbinedgraph.txt" the Groupnumber and number of relative images
    FILE *fp01;
    fp01 = fopen("combinedgraph3.txt","w");
    if(fp01 == NULL){
        printf("file open failed!");
        return 1;
    }
    for(int i = 0; i < Total_Gra; i++){
        fprintf(fp01, "%d %d\n",(graphset + i)->Groupnum,(graphset + i)->total_rel_num);
    }

    fclose(fp01);
//构造pointset用于聚类 并建立graph到point的映射
    Point *pointset;
    pointset = malloc(Total_Gra *sizeof(Point));
    if(pointset == NULL){
        printf("Memory allocation failed!");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < Total_Gra; i++){
        (pointset + i)->num = (graphset + i)->total_rel_num;
        (pointset + i)->Graphlabel = (graphset + i)->Groupnum;
        (pointset + i)->cl = -1;//表示未分类
   }

    int cycle = 0;

    //手动给定质心2
    Point *centerset;
    centerset = malloc(K * sizeof(Point));//按照指定的分类个数分配数组
    if(centerset == NULL){
        printf("Memory allocation failed!");
        exit(EXIT_FAILURE);
    }
    for(int j = 0; j < K; j ++){
        (centerset + j)->cl = (pointset + 4*j)->cl;
        (centerset + j)->num = (pointset + 4*j)->num;
        (centerset + j)->Graphlabel = -1;
    }


    cluster(pointset,centerset);
    int ob1 = objection(pointset, centerset);
    cycle += 1;

    updatecenter(pointset, centerset);
    cluster(pointset, centerset);
    int ob2 = objection(pointset, centerset);
    cycle += 1;

    //迭代结束时目标函数值不再变化
    while(abs(ob1 - ob2) != 0){
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
    fprintf(fp1,"%-10s %-10s %-10s\n","class","number","Graph");//所属类号，相关图片数目（聚类指标），图片序号
    for(int i = 0; i < N; i++){
        fprintf(fp1, "%-10d %-10d G%-9d\n", pointset[i].cl, pointset[i].num, pointset[i].Graphlabel);
    }

    fclose(fp1);


    free(rawset);free(subgraphset);free(graphset);free(pointset);free(centerset);

    return 0;
}