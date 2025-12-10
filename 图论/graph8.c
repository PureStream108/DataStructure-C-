// 迪杰斯特拉算法和弗洛伊德算法
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define INFTY INT_MAX
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

void Init(mGraph *mg, int size, ElemType noEdgeValue); // 初始化带权有向图
void Destroy(mGraph *mg);
bool Exist(mGraph *mg, int u, int v);
bool Insert(mGraph *mg, int u, int v, ElemType w);
void PrintPath(int *path, int dest);

// 迪杰斯特拉算法
int Choose(int *d, int *s, int n);
bool Dijkstra(int v, ElemType *d, int *path, mGraph g);

// 弗洛伊德算法
void Floyd(mGraph g);

int main(){
    mGraph g;
    int vertexNum = 6;
    
    Init(&g, vertexNum, INFTY); 

    Insert(&g, 0, 1, 50);
    Insert(&g, 0, 4, 80);
    Insert(&g, 0, 2, 10);
    Insert(&g, 1, 2, 15);
    Insert(&g, 1, 4, 20);
    Insert(&g, 2, 3, 15);
    Insert(&g, 3, 1, 20);
    Insert(&g, 3, 4, 35);
    Insert(&g, 4, 5, 15);
    Insert(&g, 5, 3, 9);

    int dest;
    printf("请输入目标顶点序号(0-%d): ", g.n - 1);
    scanf("%d", &dest);

    if (dest < 0 || dest >= g.n) {
        printf("无效的顶点序号！\n");
        Destroy(&g);
        return 1;
    }

    ElemType *dist = (ElemType*)malloc(g.n * sizeof(ElemType));
    int *path = (int*)malloc(g.n * sizeof(int));

    if (!dist || !path) {
        printf("内存分配失败！。\n");
        free(dist);
        free(path);
        Destroy(&g);
        return 1;
    }

    if (Dijkstra(0, dist, path, g)) {
        printf("路径长度: %d\n", dist[dest]);
        printf("路径: 0 ");
        PrintPath(path, dest); // 新增：递归打印路径
        printf("\n");
    }

    free(dist);
    free(path);
    Destroy(&g);
    
    return 0;


}

void Init(mGraph *mg, int size, ElemType noEdgeValue){
    mg -> n = size;             // 初始化顶点数
    mg -> e = 0;                // 初始化边数
    mg -> noEdge = noEdgeValue; // 初始化没有边时的值
    mg -> a = (ElemType**)malloc(sizeof(ElemType*)*size);
    for(int i = 0; i < mg -> n; i++){
        mg -> a[i] = (ElemType*)malloc(sizeof(ElemType)*size);
        for(int j = 0; j < mg -> n; j++){
            mg -> a[i][j] = mg -> noEdge;
        }
        mg -> a[i][i] = 0;
    }
}

void Destroy(mGraph *mg){
    for(int i = 0; i < mg -> n; i++)
        free(mg -> a[i]);           // 先依次释放n个一维数组的存储空间
    free(mg -> a);                  // 释放一维指针数组的存储空间
}

bool Exist(mGraph *mg, int u, int v){
    if(u < 0 || v < 0 || u > mg -> n - 1 || v > mg -> n - 1 || u == v)  // 如果u,v小于0或者是超界或者是uv相等，则失败
        return false;
    else if (mg -> a[u][v] != mg -> noEdge)
        return true;
    else
        return false;
}

bool Insert(mGraph *mg, int u, int v, ElemType w){
    if(u < 0 || v < 0 || u > mg -> n - 1 || v > mg -> n - 1 || u == v)
        return false;
    else if(mg -> a[u][v] != mg -> noEdge) // 不等于无边时的值，证明有边
        return Duplicate;                  // 插入边已存在
    else
        mg -> a[u][v] = w;
    mg -> e++;
    return true;
}

void PrintPath(int *path, int dest) {
    if (path[dest] == -1 || path[dest] == dest) {
        return;
    }
    PrintPath(path, path[dest]); // 递归回溯
    printf("→ %d ", dest);
}

int Choose(int *d, bool *s, int n){
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

bool Dijkstra(int v, ElemType *d, int *path, mGraph g) {
    if (v < 0 || v >= g.n || !d || !path) return false;
    
    bool *s = (bool*)calloc(g.n, sizeof(bool));
    if (!s) return false;

    for (int i = 0; i < g.n; i++) {
        s[i] = false;
        d[i] = g.a[v][i];
        if (i != v && d[i] < INFTY) {
            path[i] = v;
        } else {
            path[i] = -1; // -1表示无前驱
        }
    }
    
    s[v] = true;
    d[v] = 0;

    for (int i = 1; i < g.n; i++) {
        int k = Choose(d, s, g.n);
        if (k == -1) break;
        
        s[k] = true;
        
        for (int w = 0; w < g.n; w++) {
            if (!s[w] && g.a[k][w] < INFTY && d[k] + g.a[k][w] < d[w]) {
                d[w] = d[k] + g.a[k][w];
                path[w] = k; // 更新前驱节点
            }
        }
    }
    
    free(s);
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