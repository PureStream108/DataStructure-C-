// 冒泡排序
// 每一趟都把最大的排在最后
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
void BubbleSort(List *list);

int main(){
    List list;
    int testArray[] = {7, 34, 114, 5, 14, 19};
    list.n = sizeof(testArray) / sizeof(testArray[0]);

    for(int i = 0; i < list.n; i++){
        list.D[i].key = testArray[i];
        list.D[i].data = testArray[i];
    }
    
    printf("排序前: ");
    for (int i = 0; i < list.n; i++) {
        printf("%d ", list.D[i].key);
    }
    printf("\n");
    
    BubbleSort(&list);
    
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

void BubbleSort(List *list){
    int i, j;
    for(i = list -> n - 1; i > 0; i--){
        bool isSwap = false;
        for(j = 0; j < i; j++){
            if(list -> D[j].key > list -> D[j + 1].key){
                Swap(list -> D, j, j + 1);
                isSwap = true;
            }
        }
        if(!isSwap)
            break;
    }
}