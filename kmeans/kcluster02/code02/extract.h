//将所给图片提取并映射到聚类使用的点结构
#ifndef EXTRACT_H
#define EXTRACT_H
#define Total_Sub 6476
#define Total_Gra 1619
#include"kcluster02.h"

typedef struct{
    int index;
    char relate_index[5];
    int relate_num;

}Raw_Point;

typedef struct{
    int index;
    int relate_num;
}Subgraph;

typedef struct{
    int Groupnum;
    Subgraph sub1;
    Subgraph sub2;
    Subgraph sub3;
    Subgraph sub4;
    int total_rel_num;
}Graph;

Subgraph* getsubgraphset(Raw_Point rawset[Total_rawPt]);

Graph *combinesubgra(Subgraph* subgraphset);

#endif