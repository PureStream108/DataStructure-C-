//快速排序
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MaxSize 100

typedef struct entry Entry;
typedef struct list List;
typedef int KeyType;
typedef int DataType;

struct entry{
    KeyType key;   // 排序关键字，应为可比较类型
    DataType data; // data包含数据元素中的其他数据项
};

struct list{
    int n;              // 待排序元素数量
    Entry D[MaxSize];   // 静态数组存储数据元素
};

void Swap(Entry *D, int i, int j);
int Partition(List *list, int low, int high);
void QuickSort(List *list, int low, int high);

int main() {
    List list;
    int testArray[] = {5, 1, 1, 4, 9180, 191, 141};
    list.n = sizeof(testArray) / sizeof(testArray[0]);

    for (int i = 0; i < list.n; i++) {
        list.D[i].key = testArray[i];
        list.D[i].data = testArray[i];
    }
    
    printf("排序前: ");
    for (int i = 0; i < list.n; i++) {
        printf("%d ", list.D[i].key);
    }
    printf("\n");
    
    QuickSort(&list, 0, list.n - 1);
    
    printf("排序后: ");
    for (int i = 0; i < list.n; i++) {
        printf("%d ", list.D[i].key);
    }
    printf("\n");
    
    return 0;
}

void Swap(Entry *D, int i, int j){
    Entry temp;
    if(i == j)
        return;
    temp = *(D + i);
    *(D + i) = *(D + j);
    *(D + j) = temp;
}

int Partition(List *list, int low, int high){
    int i = low - 1;
    int j = high + 1;
    Entry pivot = list -> D[low]; // pivot是分割元素
    do{
        do{
            i++;
        }while (i <= high && list->D[i].key < pivot.key); // i前进，直到遇到大于分割
        do{
            j --;
        }while (j >= low && list->D[j].key > pivot.key);  // j前进，直到遇到小于分割
        if(i < j)
            Swap(list -> D, i, j);
    }while(i < j);
    Swap(list -> D, low, j);
    return j;   // 此时j是分割元素的下标
}

void QuickSort(List *list, int low, int high){
    if(low < high){
        int p = Partition(list, low, high);
        QuickSort(list, low, p);
        QuickSort(list, p + 1, high);
    }
}