#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAXSIZE 100

typedef struct stack Stack;
typedef int ElementType;

struct stack{
    int top;                // 表示栈顶位置下标
    int maxSize;            // 表示堆栈最大容量
    ElementType *element;   // 堆栈数组首地址
};

void Create(Stack *S, int mSize);
void Destroy(Stack *S);
void Clear(Stack *S);
bool IsFull(Stack *S);
bool IsEmpty(Stack *S);
void Top(Stack *S, ElementType *x);
void Push(Stack *S, ElementType x);
void Pop(Stack *S);

int main(){
    Stack S;
    Create(&S, MAXSIZE);
    int a[6] = {7, 1, 8, 9, 2, 11};
    int b[6] = {};

    for(int i = 0; i < 6; i++)
        Push(&S, a[i]);

    for(int i = 0; i < 6; i++){
        Top(&S, &b[i]);
        Pop(&S);
    }
    for(int i = 0; i < 6; i++)
        printf("%d ", b[i]);

    Clear(&S);
    if(IsEmpty(&S))
        printf("栈空");
    else
        printf("Er");

    Destroy(&S);
    return 0;
}

void Create(Stack *S, int mSize){
    S -> maxSize = mSize;
    S -> element = (ElementType*)malloc(sizeof(ElementType)*mSize);
    S -> top = -1;
}

void Destroy(Stack *S){
    S -> maxSize = -1;
    free(S -> element);
    S -> top = -1;
}

void Clear(Stack *S){
    S -> top = -1;
}

bool IsFull(Stack *S){
    return S -> top == S -> maxSize - 1;
}

bool IsEmpty(Stack *S){
    return S -> top == -1;
}

void Top(Stack *S, ElementType *x){
    if(IsEmpty(S))
        return;
    *x = S -> element[S -> top];
}

void Push(Stack *S, ElementType x){
    if(IsFull(S))
        return;

    S -> top++;
    S -> element[S -> top] = x;
}

void Pop(Stack *S){
    if(IsEmpty(S))
        return;
    S -> top--;
}

// typedef struct node{
//     ElementType element;
//     struct node *link;
// }Node;

// typedef struct stack{
//     Node *top;
// }Stack;

// void Push(Stack *S, ElementType x){
//     Node *p = (Node*)malloc(sizeof(Node));
//     p -> element = x;
//     p -> link = NULL;
//     p -> link = S -> top;
//     S -> top = p;
// }

// void Pop(Stack *S){
//     if(S -> top == NULL)
//         return;
//     Node *p = S -> top;
//     S -> top = p -> link;
//     free(p);
// }