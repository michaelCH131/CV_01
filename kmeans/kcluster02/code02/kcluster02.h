/*聚类中使用的常量及函数原型*/
#ifndef KCLUSTER_H
#define KCLUSTER_H
#define MAX 16200
#define Total_rawPt 16102
#define K 400 //指定的分类数目
#define N 1619 //图像总数
#define SUP 100 //上界数

#include"extract.h"

typedef struct{
    int cl; //定义点的类
    int num; //图像（点）相关联的图像数目
    int Graphlabel;//读取的图的标签即图的groupnum
}Point;


int getdistance(Point point1, Point point2);

void updatecenter(Point pointset[N], Point centerset[K]);

void cluster(Point pointset[N],Point centerset[K]);

int objection(Point pointset[N], Point centerset[K]);

void BubbleSort(Point pointset[N]);

//int Clusternum(Point pointset[N]);
#endif
