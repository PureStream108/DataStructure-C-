// 堆排序
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MaxSize 100

typedef struct entry Entry;
typedef int KeyType;
typedef int DataType;
typedef struct maxheap MaxHeap;

struct entry {
    KeyType key;   // 排序关键字
    DataType data; // 其他数据项
};

struct maxheap {
    int n;
    Entry D[MaxSize];
};

void Swap(Entry *D, int i, int j);
void AdjustDown(Entry heap[], int current, int border);
void HeapSort(MaxHeap *hp);

int main() {
    MaxHeap heap;
    int testArray[] = {5, 1, 1, 4, 9180, 191, 141};
    heap.n = sizeof(testArray) / sizeof(testArray[0]);

    for (int i = 0; i < heap.n; i++) {
        heap.D[i].key = testArray[i];
        heap.D[i].data = testArray[i];
    }
    
    printf("排序前: ");
    for (int i = 0; i < heap.n; i++) {
        printf("%d ", heap.D[i].key);
    }
    printf("\n");
    
    HeapSort(&heap);
    
    printf("排序后: ");
    for (int i = 0; i < heap.n; i++) {
        printf("%d ", heap.D[i].key);
    }
    printf("\n");
    
    return 0;
}

void Swap(Entry *D, int i, int j) {
    if (i == j) return;
    Entry temp = D[i];
    D[i] = D[j];
    D[j] = temp;
}

void AdjustDown(Entry heap[], int current, int border) {
    int parent = current;
    Entry temp = heap[parent]; // 保存当前节点（整个结构体）
    
    while (2 * parent + 1 <= border) { // 存在左子节点
        int child = 2 * parent + 1; // 默认左子节点
        
        // 选择较大的子节点（大顶堆）
        if (child + 1 <= border && heap[child].key < heap[child + 1].key) {
            child++; // 选择右子节点
        }
        
        // 如果父节点大于等于子节点，满足堆性质
        if (temp.key >= heap[child].key) {
            break;
        }
        
        // 将较大子节点上移（移动整个结构体）
        heap[parent] = heap[child];
        parent = child; // 继续向下检查
    }
    
    // 将保存的节点放到正确位置
    heap[parent] = temp;
}

void HeapSort(MaxHeap *hp) {
    for (int i = (hp -> n - 2) / 2; i >= 0; i--) {
        AdjustDown(hp -> D, i, hp -> n - 1);
    }
    for (int i = hp -> n - 1; i > 0; i--) {
        Swap(hp -> D, 0, i);
        AdjustDown(hp ->D, 0, i - 1);
    }
}