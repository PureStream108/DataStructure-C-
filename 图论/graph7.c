// 克鲁斯卡尔算法
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef int ElemType;
typedef struct mgraph mGraph;
enum{
    Duplicate = -1,
    NoPresent = -2
};

struct mgraph{
    ElemType **a;    // 动态二维数组
    int n;           // 顶点数
    int e;           // 边数
    ElemType noEdge; // 两顶点间无边时的值
};

void SelectSort(Edge *eg, int n);
void Kruskal(mGraph g);

int main(){

}

void SelectSort(Edge *eg, int n){
    int small;
    Edge t;
    for(int i = 0; i < n -1; i++){
        small = i;                      // 假定待排序序列中的第一个元素最小
        for(int j = i + 1; j < n; j++)
            if(eg[j].w < eg[small].w)
                small = j;              // 如果扫描到一个比最小值还小的元素，就记其下标
        t = eg[i];                      // 最小元素和待排序中第一个元素交换
        eg[i] = eg[small];
        eg[small] = t;
    }
}

void Kruskal(mGraph g){
    int k, u1, v1, vs1, vs2;
    int j;
    itn *vexSet = (int*)malloc(sizeof(int)*g.n);
    Edge *edgeSet = (Edge*)malloc(sizeof(Edge)*g.e);
    k = 0;
    for(int i = 0; i < g.n; i++)        // 由邻接矩阵产生边集数组
        for(j = 0; j < i; j++){
            if(g.a[i][j] != 0 && g.a[i][j] != g.noEdge){
                edgeSet[k].u = i;
                edgeSet[k].v = j;
                edgeSet[k].w = g.a[i][j];
            }
        }
    SelectSort(edgeSet, g.e/2);
    for(int i = 0; i < g.n; i++)
        vexSet[i] = i;
    k = 0;
    j = 0;
    while(k < g.n - 1){
        u1 = edgeSet[j].u;
        v1 = edgeSet[j].v;
        vs1 = vexSet[u1];
        vs2 = vexSet[v1];
        if(vs1 != vs2){
            printf("%d , %d, %d, \n", edgeSet[j].u, edgeSet[j].v, edgeSet[j].w); // 输出边
            k++;
            for(int i = 0; i < g.n; i++)
                if(vexSet[i] == vs2)
                    vexSet[i] = vs1;
        }
        j++;
    }
}