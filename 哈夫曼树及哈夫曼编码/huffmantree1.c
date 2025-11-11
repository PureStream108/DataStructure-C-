#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#define MAX_SIZE 100
typedef int ElemType;
typedef struct priorityQueue PriorityQueue;
typedef struct btnode BTNode;
typedef struct binarytree BinaryTree;
typedef struct pqitem PQItem;

// 二叉树
struct btnode{
    ElemType element;
    BTNode *lChild;
    BTNode *rChild;
};

struct binarytree{
    BTNode *root;
};

// 优先队列
struct pqitem{
    int weight;
    BTNode *tree;
};

struct priorityQueue{
    PQItem *elements;
    int n;
    int max_Size;
};


// 二叉树
void CreateTree(BinaryTree *bt);
BTNode* NewNode(ElemType x, BTNode *ln, BTNode *rn);
void ClearTree(BinaryTree *bt);
void Clear(BTNode *t);

// 优先权队列
void CreatPQ(PriorityQueue *PQ, int mSize);
void Destory(PriorityQueue *PQ);
bool IsEmpty(PriorityQueue *PQ);   // 判断队列是否为空
bool IsFull(PriorityQueue *PQ);    // 判断队列是否已满
int Size(PriorityQueue *PQ);       // 获取优先队列的元素总数量
void Append(PriorityQueue *PQ, ElemType x, BTNode *t);  // 添加元素，并完成建堆运算
void Serve(PriorityQueue * PQ, ElemType *x, BTNode **t); // 获取堆顶元素，并完成建堆运算
void AdjustUp(PQItem heap[], int current); // 向上调整
void AdjustDown(PQItem heap[], int current, int border); // 向下调整

// 哈夫曼算法
BinaryTree CreateHFMTree(int w[], int m);
void PrintTreeOrder(BTNode *node);

int main(){
    PriorityQueue pq;
    int weights[] = {5, 11, 15, 77, 16, 45};
    int weightCount = sizeof(weights) / sizeof(weights[0]);
    
    printf("输入权值: ");
    for (int i = 0; i < weightCount; i++) {
        printf("%d ", weights[i]);
    }
    printf("\n");
    
    BinaryTree hfmTree = CreateHFMTree(weights, weightCount);
    
    printf("哈夫曼树后序遍历: \n");
    PrintTreeOrder(hfmTree.root);
    printf("\n");
    
    ClearTree(&hfmTree);
    
    return 0;
}

// 向上调整
void AdjustUp(PQItem heap[], int current){
    int p = current;
    PQItem temp;
    while(p > 0){   // 如果p是根节点了则结束
        if(heap[p].weight < heap[(p - 1) / 2 ].weight){  //  // 如果p小于父结点，则进行交换
            temp = heap[p];
            heap[p] = heap[(p - 1) / 2 ];
            heap[(p - 1) / 2 ] = temp;
            p = (p - 1) / 2;   // 更新p的位置使其成为父结点  
        }else {
            break;
        }
    }
}

// 向下调整
void AdjustDown(PQItem heap[], int current, int border){
    int p = current;
    int minChild;
    PQItem temp;
    while(2 * p + 1 <= border){    // 若p不是叶结点，则执行
        if((2 * p + 2 <= border) && (heap[2 * p + 1].weight > heap[2 * p + 2].weight))
            minChild = 2 * p + 2;  // 右子树存在，且较小，则minChild指向p的右子树
        else
            minChild = 2 * p + 1;  // 右子树不存在或较大，则指向p的左子树
        if(heap[p].weight <= heap[minChild].weight){
            break;                 // 若当前结点不大于自己的最小的子树，则结束
        }
        else{                      // 否则就将p与最小的子树进行交换
            temp = heap[p];
            heap[p] = heap[minChild];
            heap[minChild] = temp;
            p = minChild;          // 设置下轮循环待考察元素的位置（当前下移元素位置）
        }
    }
}

void CreatPQ(PriorityQueue *PQ, int mSize){
    PQ -> max_Size = mSize;
    PQ -> n = 0;
    PQ -> elements = (PQItem*)malloc(mSize * sizeof(PQItem));
}

void Destory(PriorityQueue *PQ){
    free(PQ -> elements);     // 释放动态数组
    PQ -> n = 0;              // 元素归0
    PQ -> max_Size = 0;       // 最大长度归0 
}

bool IsEmpty(PriorityQueue *PQ){
    if(PQ -> n == 0)
        return true;
    else
        return false;
}

bool IsFull(PriorityQueue *PQ){
    if(PQ -> n == PQ -> max_Size)
        return true;
    else
        return false;
}

int Size(PriorityQueue *PQ){
    return PQ -> n;
}

void Append(PriorityQueue *PQ, ElemType x, BTNode *t){
    if(IsFull(PQ))
        return;                        
    PQ -> elements[PQ -> n].weight = x;     // 存入权值
    PQ -> elements[PQ -> n].tree = t;       // 存入结点
    PQ -> n++;                              // PQ中的元素总数+1
    AdjustUp(PQ -> elements, PQ -> n - 1);  // 对新增元素执行向上调整
}

void Serve(PriorityQueue *PQ, ElemType *x, BTNode **t){
    if(IsEmpty(PQ))                    
        return;
    *x = PQ -> elements[0].weight;          // 将最小权值赋值给x
    *t = PQ -> elements[0].tree;         // New
    PQ -> n--;                              // 元素个数-1
    PQ -> elements[0] = PQ -> elements[PQ -> n]; // 将堆尾元素赋值给堆头，从而实现删除堆顶元素
    AdjustDown(PQ -> elements, 0, PQ -> n - 1);  // 向下调整，重新形成最小堆
}

BTNode* NewNode(ElemType x, BTNode *ln, BTNode *rn){
    BTNode *p = (BTNode*)malloc(sizeof(BTNode));
    p -> element = x;
    p -> lChild = ln;
    p -> rChild = rn;
}

void ClearTree(BinaryTree *bt){
    Clear(bt -> root);
}

void Clear(BTNode *t){
    if(!t)
        return;
    Clear(t -> lChild);
    Clear(t -> rChild);
    free(t);
}

// 创建哈夫曼树
BinaryTree CreateHFMTree(int w[], int m){
    PriorityQueue PQ;
    BTNode *node_x, *node_y, *new_root;
    int weight_x, weight_y;

    CreatPQ(&PQ, m);                            // 初始化用于存储二叉树的优先权队列，权值存在根结点数据域
    for(int i = 0; i< m; i++){
        node_x = NewNode(w[i], NULL, NULL);     // 创建只包含根结点的单结点树，并把权值存在根结点数据域
        Append(&PQ, w[i], node_x);              // 将结点存入优先权队列
    }
    while(PQ.n > 1){
        Serve(&PQ, &weight_x, &node_x);
        Serve(&PQ, &weight_y, &node_y);                         // 这两步对应哈夫曼算法中取出两个最小的结点进行结合
        
        new_root = NewNode(weight_x + weight_y, node_x, node_y); // 创建新的根节点，权值为两棵树权值之和

        Append(&PQ, weight_x + weight_y, new_root);              // 将合并后的二叉树加入优先权队列
    }

    BinaryTree result;
    Serve(&PQ, &weight_x, &result.root);                         // 取出最终的哈夫曼树
    Destory(&PQ);                                                // 销毁临时的队列
    return result;
}

void PrintTreeOrder(BTNode *node) {
    if (!node) 
        return;
    PrintTreeOrder(node -> lChild);
    PrintTreeOrder(node -> rChild);

    // 判断是否为叶子节点（哈夫曼树的叶子才有原始权重）
    if (!node -> lChild && !node -> rChild) {
        printf("[%d] -> ", node -> element);  // 叶子加括号
    } else {
        printf("%d -> ", node -> element);
    }
}