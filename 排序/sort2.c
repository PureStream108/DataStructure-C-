// 直接插入算法
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

void InsertSort(List *list);

int main(){

}

void InsertSort(List *list){
    int i, j;           // i标识待插入元素下标
    Entry insertItem;   // 每一趟待插入元素
    for(i = 1; i < list -> n; i++){
        insertItem = list -> D[i];
        for(j = i - 1; j >= 0; j--){        // 不断将有序序列中元素向后运动，为待插入元素空出位置
            if(insertItem.key < list -> D[j].key)
                list -> D[j + 1] = list -> D[j];
            else
                break;
        }
        list -> D[j + 1] = insertItem; // 待插入元素有序存放至有序序列中
    }
}