#include<stdio.h>
#include<stdlib.h>
#include"extract.h"

Subgraph* getsubgraphset(Raw_Point *rawset)
{
    Subgraph* subgraphset;
    subgraphset = malloc(Total_Sub * sizeof(Subgraph));
    if(subgraphset == NULL){
        printf("Memory allocation failed!");
        exit(EXIT_FAILURE);
    }
    for(int j = 0; j < Total_Sub; j++){
        subgraphset[j].relate_num = 0;//可能导致了后续0的出现
        subgraphset[j].index = j + 1;
        for(int i = 0; i < Total_rawPt ;i++){
            if(rawset[i].index == subgraphset[j].index){//可以不用遍历全部 在第一个结束处可停止（顺序排列raw）
                subgraphset[j].relate_num += 1;
            }
        }
    }

    return subgraphset;
}

Graph *combinesubgra(Subgraph* subgraphset)
{
    Graph* graphset;
    graphset = malloc((Total_Gra) * sizeof(Graph));
    if(graphset == NULL){
        printf("Memory allocation failed!");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < Total_Gra; i++){
        (graphset + i)->Groupnum = i + 1;
        (*(graphset + i)).sub1 = (*(subgraphset + 4*i));
        (*(graphset + i)).sub2= (*(subgraphset + 4*i + 1));
        (*(graphset + i)).sub3 = (*(subgraphset + 4*i + 2));
        (*(graphset + i)).sub4 = (*(subgraphset + 4*i + 3));
        (*(graphset + i)).total_rel_num = (subgraphset + 4*i)->relate_num + (subgraphset + 4*i + 1)->relate_num + (subgraphset + 4*i + 2)->relate_num + (subgraphset + 4*i + 3)->relate_num;
    }

    return graphset;
}