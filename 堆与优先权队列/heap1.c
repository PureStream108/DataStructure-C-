#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX_SIZE 100
typedef int ElemType;

// 向下调整算法
// heap:存放序列元素的数组 current:当前待调整元素在序列中的位置
// border:待调整序列的边界
void AdjustDown(ElemType heap[], int current, int border);
void CreatHeap(ElemType heap[], int n); // 建堆算法
void PrintHeap(ElemType heap[], int n);

int main(){
    ElemType heap[] = {9, 5, 8, 3, 7, 1, 6, 2, 4};
    int n = sizeof(heap) / sizeof(heap[0]);

    printf("Origin\n");
    PrintHeap(heap, n);
    printf("\n");

    printf("Now\n");
    CreatHeap(heap, n);
    PrintHeap(heap, n);

    return 0;
}

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

void CreatHeap(ElemType heap[], int n){
    int i;
    for(i = (n-2)/2; i > -1; i--)      // 从最后一个叶结点的双亲方向到根结点
        AdjustDown(heap, i, n - 1);
}

// 打印堆(层次遍历)
void PrintHeap(ElemType heap[], int n){
    printf("Heap: \n");
    for(int i = 0; i < n; i++){
        if(i != n - 1)
            printf("%d -> ", heap[i]);
        else
            printf("%d", heap[i]);
    }
    printf("\n");
}