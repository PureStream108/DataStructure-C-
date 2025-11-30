// 图的遍历
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef int ElemType;
typedef struct eNode ENode;
typedef struct lGraph LGraph;
typedef struct queue Queue;

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

struct queue{
    int front;  // 定义队首
    int rear;   // 定义队尾
    int maxSize;
    int *element;
};

// 队列
void CreateQueue(Queue *q, int size);
bool IsEmpty(Queue *q);
bool IsFull(Queue *q);
bool EnQueue(Queue *q, int x);
bool DeQueue(Queue *q);
bool Front(Queue *q, int *x);

// 图的邻接表表示法
bool Init(LGraph *lg, int size);
bool Exist(LGraph *lg, int u, int v);
bool Insert(LGraph *lg, int u, int v, ElemType w);
bool Remove(LGraph *lg, int u, int v);
void Destroy(LGraph *lg);
void PrintGraph(LGraph *lg);

// 图的遍历
void DFS(int v, int visited[], LGraph g);
void DFSTraverse(LGraph g);
void BFS(int v, int visited[], LGraph g);
void BFSTraverse(LGraph g);

int main(){
    LGraph g;
    Init(&g, 5);
    
    Insert(&g, 0, 1, 10);
    Insert(&g, 0, 2, 20);
    Insert(&g, 1, 3, 30);
    Insert(&g, 1, 4, 40);
    Insert(&g, 2, 3, 50);
    Insert(&g, 3, 4, 60);
    
    PrintGraph(&g);
    
    printf("DFS:");
    DFSTraverse(g);
    printf("\n");
    
    printf("BFS:");
    BFSTraverse(g);
    printf("\n");
    
    Destroy(&g);
    return 0;
}

void CreateQueue(Queue *q, int size){
    q -> maxSize = size;
    q -> front = q -> rear = 0;
    q -> element = (int*)malloc(sizeof(int)*size);
}

bool IsEmpty(Queue *q){
    return q -> front == q -> rear;
}

bool IsFull(Queue *q){
    return (q -> rear + 1) % q -> maxSize == q -> front;
}

bool EnQueue(Queue *q, int x){
    if(IsFull(q))
        return false;
    q -> rear = (q -> rear + 1) % q -> maxSize;
    q -> element[q -> rear] = x;
    return true;
}

bool DeQueue(Queue *q){
    if(IsEmpty(q))
        return false;
    q -> front = (q -> front + 1) % q -> maxSize;
    return true;
}

bool Front(Queue *q, int *x){
    if(IsEmpty(q))
        return false;
    *x = q -> element[(q -> front + 1) % q -> maxSize];
    return true;
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

void DFS(int v, int visited[], LGraph g){
    ENode *w;
    printf("%d ", v); // 访问顶点v
    visited[v] = 1;    // 为顶点v打上标记，证明访问过了v
    for(w = g.a[v]; w; w = w -> NextArc){
        if(!visited[w -> AdjVex])
            DFS(w -> AdjVex, visited, g);
    }
}

void DFSTraverse(LGraph g){
    int *visited = (int*)malloc(sizeof(int)*g.n); // 生成动态标记数组
    for(int i = 0; i < g.n; i++)
        visited[i] = 0;
    for(int i = 0; i < g.n; i++)
        if(!visited[i])
            DFS(i, visited, g);  // 逐一检查每个顶点，如果没被访问过，怎调用DFS算法
    free(visited);
}

void BFS(int v, int visited[], LGraph g){
    ENode *w;
    Queue q;
    CreateQueue(&q, g.n);
    visited[v] = 1;   // 标记顶点v
    printf("%d ", v);
    EnQueue(&q, v);   // 将顶点v放入队列
    while(!IsEmpty(&q)){
        Front(&q, &v);
        DeQueue(&q);    // 队首顶点v出列
        for(w = g.a[v]; w; w = w -> NextArc) // 一次搜索v的未被访问过的邻接点，访问并将其入队
            if(!visited[w -> AdjVex]){
                visited[w -> AdjVex] = 1;
                printf("%d ", w -> AdjVex);
                EnQueue(&q, w -> AdjVex);
            }
    }
}

void BFSTraverse(LGraph g){
    int *visited = (int*)malloc(g.n*sizeof(int));
    for(int i = 0; i < g.n; i++)
        visited[i] = 0;
    for(int i = 0; i < g.n; i++)
        if(!visited[i])
            BFS(i, visited, g);  // 依次检查每个顶点，如果未被访问，则调用宽度优先算法
    free(visited);
}
