/*聚类中使用的常量及函数原型*/
#ifndef KCLUSTER_H
#define KCLUSTER_H
#define MAX 16200
#define K 2000 //指定的分类数目
#define N 16102 //图像总数
#define SUP 1000 //上界数

typedef struct{
    int cl; //定义点的类
    int num; //图像（点）相关联的图像数目
}Point;

int getdistance(Point point1, Point point2);

void updatecenter(Point pointset[N], Point centerset[K]);

void cluster(Point pointset[N],Point centerset[K]);

int objection(Point pointset[N], Point centerset[K]);

void BubbleSort(Point pointset[N]);

//int Clusternum(Point pointset[N]);
#endif
