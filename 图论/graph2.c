//邻接表表示法
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef int ElemType;
typedef struct eNode ENode;
typedef struct lGraph LGraph;
enum{
    Duplicate = -1,
    NoPresent = -2
};

struct eNode{
    int AdjVex;
    ElemType w;
    struct eNode* NextArc;
};

struct lGraph{
    ENode **a;  // 指向一维指针数组
    int n;      // 图中顶点数
    int e;      // 图中边数
};

bool Init(LGraph *lg, int size);
bool Exist(LGraph *lg, int u, int v);
bool Insert(LGraph *lg, int u, int v, ElemType w);
bool Remove(LGraph *lg, int u, int v);
void Destroy(LGraph *lg);
void PrintGraph(LGraph *lg);

int main(){
    LGraph g;
    Init(&g, 5);
    
    Insert(&g, 0, 1, 10);
    Insert(&g, 0, 2, 20);
    Insert(&g, 1, 3, 30);
    Insert(&g, 2, 4, 40);
    Insert(&g, 3, 1, 50);
    
    PrintGraph(&g);
    
    printf("\n边 (0, 1) 存在: %s\n", Exist(&g, 0, 1) ? "是" : "否");
    printf("边 (1, 0) 存在: %s\n", Exist(&g, 1, 0) ? "是" : "否");
    
    Remove(&g, 0, 1);
    printf("\n删除边 (0, 1) 后:\n");
    PrintGraph(&g);
    
    Destroy(&g);
    return 0;
}

bool Init(LGraph *lg, int size){
    lg -> n = size;
    lg -> a = (ENode**)malloc(sizeof(ENode*)*size);
    if(!lg -> a)
        return false;
    else{
        for(int i = 0; i < lg -> n; i++)
            lg -> a[i] = NULL;           // 将指针数组a置空
        return true;
    }
}

bool Exist(LGraph *lg, int u, int v){
    if(u < 0 || v < 0 || u > lg -> n - 1 || v > lg -> n - 1 || u == v) 
        return false;
    ENode *p = lg -> a[u];      // 遍历顶点 u 的邻接表
    while(p != NULL){
        if(p -> AdjVex == v)    // 找到边 (u, v)
            return true;
        p = p -> NextArc;       // 下一个邻接点
    }
    return false;
}

bool Insert(LGraph *lg, int u, int v, ElemType w){
    ENode* p;
    if(u < 0 || v < 0 || u > lg -> n - 1 || v > lg -> n - 1 || u == v) // 判断界限
        return false;
    if(Exist(lg, u, v))
        return Duplicate;
    else{
        p = (ENode*)malloc(sizeof(ENode));
        if(!p)
            return false;
        p -> AdjVex = v;            // 邻接点
        p -> w = w;                 // 权值
        p -> NextArc = lg -> a[u];  // 指向当前链表头
        lg -> a[u] = p;             // 插入链表头部
    }
    lg -> e++;
    return true;
}

bool Remove(LGraph *lg, int u, int v){
    ENode *p, *q;
    if(u < 0 || v < 0 || u > lg -> n - 1 || v > lg -> n - 1 || u == v) // 判断界限
        return false;
    p = lg -> a[u], q = NULL;
    while(p && p -> AdjVex != v){
        q = p;                  // q是p的前驱节点
        p = p -> NextArc;
    }
    if(!p)
        return NoPresent;
    if(q)
        q -> NextArc = p -> NextArc;  // 将q的下一节点跳过p，指向p的下一个，从而达成删除效果
    else
        lg -> a[u] = p -> NextArc;
    free(p);                          // 只有动态数组才需要被free
    lg -> e--;
    return true;
}

void Destroy(LGraph *lg){
    ENode *p, *q;
    for(int i = 0;i < lg -> n;i++){
        p = lg -> a[i];
        q = p;
        while(p){
            p = p -> NextArc;
            free(p);
            q = p;
        }
    }
    free(lg -> a);
}

void PrintGraph(LGraph *lg) {
    printf("图的邻接表:\n");
    for (int i = 0; i < lg->n; i++) {
        printf("顶点 %d: ", i);
        ENode *p = lg->a[i];
        while (p) {
            printf("-> (%d, 权重:%d) ", p->AdjVex, p->w);
            p = p->NextArc;
        }
        printf("\n");
    }
}