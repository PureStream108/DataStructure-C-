//邻接表表示法
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef int ElemType;
typedef struct eNode ENode;
typedef struct lGraph LGraph;
typedef struct stack Stack;

enum{
    Duplicate = -1,
    NoPresent = -2
};

struct stack {
    int top;
    int maxSize;
    int *element;
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


// 栈
void CreateStack(Stack *s, int size);
bool IsEmpty(Stack *s);
bool IsFull(Stack *s);
bool Push(Stack *s, int x);
bool Pop(Stack *s);
bool Top(Stack *s, int *x);

// 图
bool Init(LGraph *lg, int size);
bool Exist(LGraph *lg, int u, int v);
bool Insert(LGraph *lg, int u, int v, ElemType w);
bool Remove(LGraph *lg, int u, int v);
void Destroy(LGraph *lg);
void PrintGraph(LGraph *lg);

// 拓扑排序
void Degree(int *inDegree, LGraph g);
bool TopoSort(int *topo, LGraph g);

int main() {
    LGraph g;
    Init(&g, 6);
    
    Insert(&g, 0, 1, 1);
    Insert(&g, 0, 2, 1);
    Insert(&g, 1, 3, 1);
    Insert(&g, 2, 3, 1);
    Insert(&g, 2, 4, 1);
    Insert(&g, 3, 5, 1);
    Insert(&g, 4, 5, 1);
    
    PrintGraph(&g);
    
    int *topo = (int*)malloc(sizeof(int) * g.n);
    printf("拓扑排序:");
    TopoSort(topo, g);
    printf("\n");
    
    free(topo);
    Destroy(&g);
    return 0;
}

void CreateStack(Stack *s, int size) {
    s->maxSize = size;
    s->top = -1;
    s->element = (int*)malloc(sizeof(int) * size);
}

bool IsEmpty(Stack *s) {
    return s->top == -1;
}

bool IsFull(Stack *s) {
    return s->top == s->maxSize - 1;
}

bool Push(Stack *s, int x) {
    if (IsFull(s)) return false;
    s->element[++s->top] = x;
    return true;
}

bool Pop(Stack *s) {
    if (IsEmpty(s)) return false;
    s->top--;
    return true;
}

bool Top(Stack *s, int *x) {
    if (IsEmpty(s)) return false;
    *x = s->element[s->top];
    return true;
}

bool Init(LGraph *lg, int size){
    lg -> n = size;
    lg -> a = (ENode**)malloc(sizeof(ENode*)*size);
    lg -> e = 0;
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

void Degree(int *inDegree, LGraph g){
    ENode *p;
    for(int i = 0; i < g.n; i++)
        inDegree[i] = 0;
    for(int i = 0; i < g.n; i++)
        for(p = g.a[i]; p; p = p -> NextArc)   // 检查顶点v的所有邻接点
            inDegree[p -> AdjVex]++;           // 将顶点v的邻接点的入度+1
}

bool TopoSort(int *topo, LGraph g){
    ENode *p;
    Stack S;
    int j = 0;
    int k = 0;
    int *inDegree = (int*)malloc(sizeof(int)*g.n);
    Degree(inDegree, g);   // 计算顶点的入度
    CreateStack(&S, g.n);       // 初始化堆栈
    for(int i = 0; i < g.n; i++)
        if(!inDegree[i])
            Push(&S, i); // 入度为0的进栈
    for(int i = 0; i < g.n; i++)
    {   
        if(IsEmpty(&S))
            return false;
        else{
            Top(&S, &j);
            Pop(&S);  // 顶点v出栈
            topo[i] = j;
            printf("%d ", j);                           // 将顶点j输出到拓扑序列中
            for( p = g.a[j]; p; p = p -> NextArc){      // 检查以顶点j为尾的所有邻接点
                k = p -> AdjVex;
                inDegree[k]--;
                if(!inDegree[k])                        // 若顶点k入度为0，则进栈
                    Push(&S, k);
        }
        }
    }
    return true;
}