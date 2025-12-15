// 合并排序
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
void Merge(List *list, Entry *temp, int low, int n1, int n2);
void MergeSort(List *list);

int main(){
    List list;
    int testArray[] = {5, 1, 1, 4, 9180, 191, 141};
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
    
    MergeSort(&list);
    
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

// list是待排序序列，temp是临时创建的空间的首地址，n1和n2是子序列长度，low是子序列首地址
void Merge(List *list, Entry *temp, int low, int n1, int n2){
    int i = low;
    int j = low + n1; // i，j初始分别指向两个序列的第一个元素
    while(i <= low + n1 - 1 && j <= low + n1 + n2 - 1){
        if(list -> D[i].key <= list -> D[j].key)
            *temp++ = list -> D[i++];
        else
            *temp++ = list -> D[j++];
    }
    while(i <= low + n1 - 1)
        *temp++ = list -> D[i++];   // 剩余元素直接拷贝至temp
    while(j <= low + n1 + n2 - 1)
        *temp++ = list -> D[j++];   // 剩余元素直接拷贝至temp
}

void MergeSort(List *list){
    Entry temp[MaxSize];
    int low, n1, n2, i, size = 1;
    while(size < list -> n){
        low = 0;                                    // low是一对待合并序列中第一个序列的第一个元素的下标
        while(low + size < list -> n){
            n1 = size;
            if(low + size * 2 < list -> n)
                n2 = size;                          //计算第二个序列长度
            else
                n2 = list -> n - low - size;
            Merge(list, temp + low, low, n1, n2);
            low += n1 + n2;                         // 确定下一对待合并序列中第一个序列的第一个元素下标
        }
        for(i = 0; i < low; i++)
            list -> D[i] = temp[i];                    // 复制一趟合并排序结果
        size *= 2;                                  // 子序列长度翻倍
    }
}