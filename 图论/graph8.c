// 迪杰斯特拉算法和弗洛伊德算法
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

// 迪杰斯特拉算法
int Choose(int *d, int *s, int n);
bool Dijkstra(int v, ElemType *d, int *path, mGraph g);

// 弗洛伊德算法
void Floyd(mGraph g);

int main(){

}

int Choose(int *d, int *s, int n){
    int minpos;                 //  选出最小的d[i]
    ElemType min;
    min = INFTY;
    minpos = -1;
    for(int i = 0; i < n; i++)
        if(d[i] < min && !s[i]){
            min = d[i];
            minpos = i;
        }
    return minpos;
}

bool Dijkstra(int v, ElemType *d, int *path, mGraph g){
    int k, w;
    int *s;
    if(v < 0 || v > g.n - 1)
        return false;
    s = (int*)malloc(sizeof(int)*g.n);
    for(int i = 0; i < g.n; i++){
        s[i] = 0;
        d[i] = g.a[v][i];
        if(i != v && d[i] < INFTY)
            path[i] = v;
        else
            path[i] = -1;
    }
    s[v] = 1;
    d[v] = 0;                           // 顶点v为源点
    for(int i = 1; i < g.n - 1; i++)
    {
        k = Choose(d, s, g.n);
        if(k == -1)
            continue;
        s[k] = 1;
        printf("%d ", k);
        for(w = 0; w < g.n; w++)
            if(!s[w] && d[k] + g.a[k][w] < d[w]){
                d[w] = d[k] + g.a[k][w];
                path[w] = k;
            }
    }
    for(int i = 0; i < g.n; i++)
        printf("%d ", d[i]);
    return true;
}

void Floyd(mGraph g){
    ElemType **d = (ElemType**)malloc(g.n*sizeof(ElemType*));
    int **p = (int**)malloc(g.n*sizeof(int*));
    for(int i = 0; i < g.n; i++){
        d[i] = (ElemType*)malloc(g.n*sizeof(ElemType));
        p[i] = (int*)malloc(g.n*sizeof(int));
        for(int j = 0; j < g.n; j++){
            d[i][j] = g.noEdge;
            p[i][j] = 0;
        }
    }
    for(int i = 0; i < g.n; i++)
        for(int j = 0; j < g.n; j++){
            d[i][j] = g.a[i][j];
            if(i != j && g.a[i][j] < INFTY)
                p[i][j] = i;
            else
                p[i][j] = -1;
        }
    for(int k = 0; k < g.n; k++)
        for(int i = 0; i < g.n; i++)
            for(int j = 0; j < g.n; j++)
                if(d[i][k] + d[k][j] < d[i][j]){
                    d[i][j] = d[i][k] + d[k][j];
                    p[i][j] = p[k][j];
                }
    for(int i = 0; i < g.n; i++)
    {
        for(int j = 0; j < g.n; j++)
            printf("%d ", d[i][j]);
        printf("\n");
    }
}