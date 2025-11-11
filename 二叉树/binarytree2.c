// 层次遍历(队列)
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define QUEUESIZE 100

// 1. 前向声明（解决类型未定义问题）
typedef struct btnote BTNode;
typedef struct binarytree BinaryTree;
typedef struct queue Queue;

// 2. 正确定位类型别名
typedef char ElemType;

// 3. 结构体定义（使用BTNode*而非btnote*）
struct btnote{
    ElemType element;
    BTNode *lChild;    // 左子树
    BTNode *rChild;    // 右子树
};

struct binarytree{
    BTNode *root;
};

// 4. 队列定义
struct queue {
    BTNode* data[QUEUESIZE];
    int front, rear;
    int count;
};

// 5. 函数前置声明（所有函数在使用前声明）
void CreateTree(BinaryTree *bt);
BTNode* NewNode(ElemType x, BTNode *ln, BTNode *rn);
void MakeTree(BinaryTree *bt, ElemType x, BinaryTree *left, BinaryTree *right);
void ClearTree(BinaryTree *bt);
void LevelOrderTree(BinaryTree *tree);

// 队列操作声明
void CreateQueue(Queue *q);
bool EnQueue(Queue *q, BTNode* node);
bool DeQueue(Queue *q);
bool Front(Queue *q, BTNode **p);
bool IsEmpty(Queue *q);
void DestroyQueue(Queue *q);

// 6. 函数实现
void CreateTree(BinaryTree *bt){
    bt->root = NULL;
}

BTNode* NewNode(ElemType x, BTNode *ln, BTNode *rn){
    BTNode *p = (BTNode *)malloc(sizeof(BTNode));
    p->element = x;
    p->lChild = ln;
    p->rChild = rn;
    return p;
}

void MakeTree(BinaryTree *bt, ElemType x, BinaryTree *left, BinaryTree *right){
    if(bt->root || left == right) return;
    bt->root = NewNode(x, left->root, right->root);
    left->root = right->root = NULL;
}

// 递归清空树
void ClearTree(BinaryTree *bt){
    if(bt->root){
        BinaryTree left, right;
        left.root = bt->root->lChild;
        right.root = bt->root->rChild;
        ClearTree(&left);
        ClearTree(&right);
        free(bt->root);
        bt->root = NULL;
    }
}

// 队列操作实现
void CreateQueue(Queue *q){
    q->front = q->rear = q->count = 0;
}

bool EnQueue(Queue *q, BTNode* node){
    if(q->count >= QUEUESIZE) return false;
    q->data[q->rear] = node;
    q->rear = (q->rear + 1) % QUEUESIZE;
    q->count++;
    return true;
}

bool DeQueue(Queue *q){
    if(q->count == 0) return false;
    q->front = (q->front + 1) % QUEUESIZE;
    q->count--;
    return true;
}

bool Front(Queue *q, BTNode **p){
    if(q->count == 0) return false;
    *p = q->data[q->front];
    return true;
}

bool IsEmpty(Queue *q){
    return q->count == 0;
}

void DestroyQueue(Queue *q){
    q->front = q->rear = q->count = 0;
}

// 层次遍历
void LevelOrderTree(BinaryTree *tree){
    Queue Q;
    BTNode *p;
    if(!tree->root) 
        return;
    
    CreateQueue(&Q);
    EnQueue(&Q, tree->root);
    
    while(!IsEmpty(&Q)){
        Front(&Q, &p);        // 获取队头结点p
        DeQueue(&Q);
        printf("%c -> ", p->element);
        if(p->lChild) EnQueue(&Q, p->lChild);  // 如果左子树存在，则进队
        if(p->rChild) EnQueue(&Q, p->rChild);
    }
    DestroyQueue(&Q);
}

int main(){
    BinaryTree a, b, x, y, z;
    CreateTree(&a); CreateTree(&b); CreateTree(&x); 
    CreateTree(&y); CreateTree(&z);
    
    MakeTree(&y, 'P', &a, &b);
    MakeTree(&z, 'u', &a, &b);
    MakeTree(&x, 'r', &y, &z);
    MakeTree(&y, 'e', &a, &b);
    MakeTree(&z, 'S', &y, &x);
    
    LevelOrderTree(&z);
    ClearTree(&z);
    
    return 0;
}