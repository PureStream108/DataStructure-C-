#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAXSIZE 100

typedef struct queue Queue;

struct queue{
    int front;              // 队头元素的前一单元的位置下标
    int rear;               // 队尾元素的位置下标
    int maxSize;            // 队列空间的最大容量
    ElementType *element;   // 队列元素的数组首地址
};

void Create(Queue *q, int mSize);
void Destroy(Queue *q);
void Clear(Queue *q);
bool IsEmpty(Queue *q);
bool IsFull(Queue *q);
void Front(Queue *q, ElementType *x);
void EnQueue(Queue *q, ElementType x);
void DeQueue(Queue *q);

int main(){
    // 跟栈差不多，懒得写了
}

void Create(Queue *q, int mSize){
    q -> maxSize = mSize;
    q -> element = (ElementType*)malloc(sizeof(ElementType)*mSize);
    q -> front = q -> rear = 0;
}

void Destroy(Queue *q){
    free(q -> element);
    q -> maxSize = -1;
    q -> front = q -> rear = -1;
}

void Clear(Queue *q){
    q -> front = q -> rear = 0;
}

bool IsEmpty(Queue *q){
    return q -> front == q -> rear;
}

bool IsFull(Queue *q){
    return (q -> rear + 1) % q -> maxSize == q -> front; 
}

void Front(Queue *q, ElementType *x){
    if(IsEmpty(q))
        return;
    *x = q -> element[(q -> front + 1) % q -> maxSize];
}

void EnQueue(Queue *q, ElementType x){
    if(IsFull(q))
        return;
    q -> rear = (q -> rear + 1) % q -> maxSize;
    q -> element[q -> rear] = x;
}

void DeQueue(Queue *q){
    if(IsEmpty(q))
        return;
    q -> front = (q -> front + 1) % q -> maxSize;
}

// typedef struct node{
//     ElementType element;
//     struct node *link;
// }Node;

// typedef struct queue{
//     Node *front;
//     Node *rear;
// }Queue;

// // 进队操作
// void EnQueue(Queue *Q, ElementType x){
//     Node *p = (Node*)malloc(sizeof(Node));
//     p -> element = x;
//     p -> link = NULL;
//     q -> rear -> link = p;
//     q -> rear = p;
// }

// // 出队操作
// void DeQueue(Queue *q){
//     if(q -> front == NULL)
//         return;
//     Node *p = q -> front;
//     q -> front = p -> link;
//     free(p);
//     // 若出队后，队列为空，则需重置rear
//     if(q -> front == NULL)
//         q -> rear = NULL;
// }
