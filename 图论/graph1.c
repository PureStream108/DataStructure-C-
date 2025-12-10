//邻接矩阵
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

void Init(mGraph *mg, int size, ElemType noEdgeValue); // 初始化带权有向图
void Destory(mGraph *mg);
bool Exist(mGraph *mg, int u, int v);
bool Insert(mGraph *mg, int u, int v, ElemType w);
bool Remove(mGraph *mg, int u, int v);

int main(){
    mGraph g;
    int vertexNum = 5;
    
    // 初始化图（5个顶点，无边时用INF表示）
    Init(&g, vertexNum, 9999);
    
    // 插入边
    printf("插入边\n");
    Insert(&g, 0, 1, 10);
    Insert(&g, 0, 2, 20);
    Insert(&g, 1, 3, 30);
    Insert(&g, 2, 4, 40);
    Insert(&g, 3, 0, 50);

    // 测试重复插入
    printf("重复插入边(0->1): %s\n", 
           Insert(&g, 0, 1, 15) == Duplicate ? "已存在" : "成功");
    
    // 查询边
    printf("查询边\n");
    printf("边 0->1 %s\n", Exist(&g, 0, 1) ? "存在" : "不存在");
    printf("边 1->0 %s\n", Exist(&g, 1, 0) ? "存在" : "不存在");
    
    // 删除边
    printf("删除边：\n");
    Remove(&g, 0, 1);
    printf("删除边 0->1\n");
    printf("边 0->1 %s\n", Exist(&g, 0, 1) ? "存在" : "不存在");
    
    // 测试无效操作
    printf("测试无效操作：\n");
    printf("插入边(-1->1): %s\n", Insert(&g, -1, 1, 10) ? "成功" : "失败");
    printf("插入边(1->1): %s\n", Insert(&g, 1, 1, 10) ? "成功" : "失败");
    printf("插入边(1->10): %s\n", Insert(&g, 1, 10, 10) ? "成功" : "失败");
    
    // 销毁图
    Destory(&g);
    printf("\n图已销毁\n");
    
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

void Destory(mGraph *mg){
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

bool Remove(mGraph *mg, int u, int v){
    if(u < 0 || v < 0 || u > mg -> n - 1 || v > mg -> n - 1 || u == v)
        return false;
    else if(mg -> a[u][v] == mg -> noEdge)
        return NoPresent;
    else
        mg -> a[u][v] = mg -> noEdge;   // 删除边
    mg -> e--;
    return true;
}