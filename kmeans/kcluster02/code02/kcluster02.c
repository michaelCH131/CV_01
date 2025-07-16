#include <stdio.h>
#include <stdlib.h>
#include "kcluster02.h"

//距离函数
int getdistance(Point point1, Point point2)
{
    int d;
    d = abs(point1.num - point2.num);
    return d;
}

//更新质心函数
void updatecenter(Point *pointset, Point *centerset)
{
    Point temp;
    for(int i = 0; i < K; i++){
        temp.num = 0;
        int count = 0;
        for(int j = 0; j < N; j++){
            if(pointset[j].cl == i + 1){
                temp.num += pointset[j].num;
                count += 1;
            }
        }
        if(count == 0){
            centerset[i].num == 0;
        }
        else{
        centerset[i].num = temp.num / count;
        centerset[i].cl = i + 1;
        }
    }
}

//聚类函数
void cluster(Point *pointset, Point *centerset)//应当使用动态内存分配,或者不储存distance，现算现用
{
    // int distance[N][K];
    // for(int i =0; i < N; i++){
    //     for(int j = 0; j < K; j++){
    //         distance[i][j] = getdistance(pointset[i], centerset[j]);
    //         //printf("distance[%d][%d] = %d\n", i, j, distance[i][j]);

    //     }
    // }

    for(int i = 0; i < N; i++){
        int sup = SUP;
        for(int j = 0; j < K; j++){
            int d = getdistance(pointset[i], centerset[j]);
            if(d < sup){
                pointset[i].cl = j + 1;
                sup = d;
            }
        }
    }
}

//目标函数计算
int objection(Point *pointset, Point *centerset)
{
    int sum = 0;
    for(int i = 0; i < N; i++){
        int j = pointset[i].cl;
        sum += abs(pointset[i].num - centerset[j-1].num);
    }

    return sum;

}

//冒泡排序
void BubbleSort(Point *pointset){
    for(int i = 0; i < N-1; i++){
        for(int j = 0; j < N-1-i; j++){
            if(pointset[j].cl > pointset[j+1].cl){
                Point temp;
                temp = pointset[j];
                pointset[j] = pointset[j+1];
                pointset[j+1] = temp;
            }
        }
    }
}

//统计实际类数(有误)
// int Clusternum(Point pointset[N])
// {
//     int cluster_size[K+1];
//     for(int i = 0; i < N; i++){
//         cluster_size[pointset[i].cl] += 1; 
//     }

//     int actualclass = 0;
//     for(int i = 1; i < K + 1; i++){
//         if(cluster_size[i] > 0){
//             actualclass += 1;
//         }
//     }

//     return actualclass;
// }