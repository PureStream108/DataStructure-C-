//最小代价生成树
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

// 普里姆算法
bool Prim(int k, int *closeVex, ElemType *lowWeight, LGraph g);

int main(){

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

bool Prim(int k, int *closeVex, ElemType *lowWeight, LGraph g){
    ENode *p;
    ElemType min;
    int *isMask = (int*)malloc(sizeof(int)*g.n);
    if(k < 0 || k > g.n)
        return false;
    for(int i = 0; i < g.n; i++) // 初始化三个数组
    {
        closeVex[i] = -1;       // 对应nearest[]， 存放与顶点i距离最近且在生成树上的顶点
        lowWeight[i] = INFTY;   // 存放边 (i,nearest[i]) 的权值
        isMask[i] = 0;          // 标记顶点 i 是否已经在生成树上
    }
    lowWeight[k] = 0;
    closeVex[k] = 0;
    isMask[k] = 1;     // 以上三条说明源点加入生成树
    for(int i = 1; i < g.n; i++){
        for(p = g.a[k]; p; p = p -> NextArc){
            j = p -> AdjVex;
            if((!isMask[j]) && ((lowWeight[j] > p -> w)){ // 更新树外顶点的lowWeight值
                lowWeight[j] = p -> w;                    // 初始都是0，第一遍约等于初始化
                closeVex[j] = k;
            }
        }
        min = INFTY;
        for(int j = 0; j < g.n; j++)    // 找生成树外顶点中，具有最小lowWeight值的顶点k
        {
            if((!isMask[j]) && (lowWeight[j] < min)){
                min = lowWeight[j];
                k = j;
            }
        }
        isMask[k] = 1;    // 将顶点加到生成树上
    }
    for(int i = 0; i < g.n; i++){
        printf("%d ", closeVex[i]);
        printf("%d ", i);
        printf("%d ", lowWeight[i]);
        printf("\n");
    }
    return true;
}