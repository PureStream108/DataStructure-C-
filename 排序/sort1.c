#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

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

void Swap(Entry *D, int i. int j);
int FindMin(List *list, int startIndex);
void SelectSort(List *list);

int main(){

}

void Swap(Entry *D, int i, int j){
    Entry temp;
    if(i == j)
        return;
    temp = *(D + i);
    *(D + i) = *(D + j);
    *(D + j) = temp;
}

int FindMin(List *list, int startIndex){
    int n = list -> n - startIndex;
    int min = list -> D[startIndex];
    int count = startIndex;
    for(int i = startIndex; i < n; i++){
        if(min > list -> D[i]){
            min = list -> D[i];
            count = i;
        }
    }
    return count;
}

void SelectSort(List *list){
    int minIndex, startIndex = 0;
    while(startIndex < list -> n - 1){
        minIndex = FindMin(*list, startIndex);
        Swap(list -> D, startIndex, minIndex);
        startIndex++;
    }
}