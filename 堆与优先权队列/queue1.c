#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX_SIZE 100
typedef int ElemType;
typedef struct priorityQueue PriorityQueue;

struct priorityQueue{
    ElemType *elements;
    int n;
    int max_Size;
};

// 声明
void CreatPQ(PriorityQueue *PQ, int mSize);
void Destory(PriorityQueue *PQ);
bool IsEmpty(PriorityQueue *PQ);   // 判断队列是否为空
bool IsFull(PriorityQueue *PQ);    // 判断队列是否已满
int Size(PriorityQueue *PQ);       // 获取优先队列的元素总数量
void Append(PriorityQueue *PQ, ElemType x);  // 添加元素，并完成建堆运算
void Serve(PriorityQueue * PQ, ElemType *x); // 获取堆顶元素，并完成建堆运算
void AdjustUp(ElemType heap[], int current);
void AdjustDown(ElemType heap[], int current, int border);
void PrintPQ(PriorityQueue *PQ);

int main(){
    PriorityQueue pq;
    int x = 0;  // 初始化
    CreatPQ(&pq, MAX_SIZE);
    Append(&pq, 1);Append(&pq, 12);Append(&pq, 17);Append(&pq, 11);Append(&pq, 33);Append(&pq, 6);
    printf("队列为: \n");
    PrintPQ(&pq);
    Serve(&pq, &x);
    printf("堆顶元素为: %d\n", x);
    printf("新队列为: \n");
    PrintPQ(&pq);
    Destory(&pq);
    return 0;
}

// 向上调整
void AdjustUp(ElemType heap[], int current){
    int p = current;
    ElemType temp;
    while(p > 0){   // 如果p是根节点了则结束
        if(heap[p] < heap[(p - 1) / 2 ]){  //  // 如果p小于父结点，则进行交换
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
void AdjustDown(ElemType heap[], int current, int border){
    int p = current;
    int minChild;
    ElemType temp;
    while(2 * p + 1 <= border){    // 若p不是叶结点，则执行
        if((2 * p + 2 <= border) && (heap[2 * p + 1] > heap[2 * p + 2]))
            minChild = 2 * p + 2;  // 右子树存在，且较小，则minChild指向p的右子树
        else
            minChild = 2 * p + 1;  // 右子树不存在或较大，则指向p的左子树
        if(heap[p] <= heap[minChild]){
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
    PQ -> elements = (ElemType*)malloc(mSize*sizeof(ElemType));
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

void Append(PriorityQueue *PQ, ElemType x){
    if(IsFull(PQ))
        return;                      // 队列已满，自然插不下新的元素
    PQ -> elements[PQ -> n] = x;     // 在队尾插入新元素
    PQ -> n++;                       // PQ中的元素总数+1
    AdjustUp(PQ -> elements, PQ -> n - 1);  // 对新增元素执行向上调整
}

void Serve(PriorityQueue *PQ, ElemType *x){
    if(IsEmpty(PQ))                    // 队列为空自然不能获取堆顶元素
        return;
    *x = PQ -> elements[0];          // 将堆顶元素赋值给x
    PQ -> n--;                       // 元素个数-1
    PQ -> elements[0] = PQ -> elements[PQ -> n]; // 将堆尾元素赋值给堆头，从而实现删除堆顶元素
    AdjustDown(PQ -> elements, 0, PQ -> n - 1);  // 向下调整，重新形成最小堆
}

void PrintPQ(PriorityQueue *PQ){
    if(IsEmpty(PQ))
        return;
    int x = PQ -> n;
    for(int i = 0;i < x;i++){
        if(i != x - 1)
            printf("%d -> ", PQ -> elements[i]);
        else
            printf("%d", PQ -> elements[i]);
    }
    printf("\n");
}