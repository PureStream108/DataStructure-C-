#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct listset ListSet;
typedef int ElemType;
const ElemType MaxNum = 1e5;

struct listset{
    int n;
    int maxLength;
    ElemType *element;
};

int SeqSearch(ListSet L, ElemType x);         // 无序表顺序搜索
int SeqSearchOrder(ListSet L, ElemType x);    // 有序表顺序搜索
int SeqSearchSentry(ListSet L, ElemType x);   // 有哨兵的有序表顺序搜索

int main(){
    int arr1[] = {1, 7, 4, 7, 3, 8};  // 无序表
    int arr2[] = {11, 34, 56, 65, 78};// 有序表

    // 无序表
    ListSet list1;
    list1.n = 6;
    list1.maxLength = 10;
    list1.element = (ElemType*)malloc(list1.maxLength*sizeof(ElemType));
    for(int i = 0; i < list1.n; i++)
        list1.element[i] = arr1[i];
    
    // 有序表
    ListSet list2;
    list2.n = 6;
    list2.maxLength = 10;
    list2.element = (ElemType*)malloc(list2.maxLength*sizeof(ElemType));
    for(int i = 0; i < list2.n; i++)
        list2.element[i] = arr2[i];

    // 哨兵版
    ListSet list3;
    list3.n = list2.n;
    list3.maxLength = list2.maxLength + 1;    // 多的一个用于存放哨兵
    list3.element = (ElemType*)malloc(list3.maxLength*sizeof(ElemType));
    for(int i = 0; i < list3.n; i++)
        list3.element[i] = arr2[i];

    // 顺序搜索（无序表）
    printf("顺序搜索（无序表）：\n");
    // 这里你也可以scanf_s自定义一个
    int x = SeqSearch(list1, 3);
    if(x == -1)
        printf("搜索失败\n");
    else
        printf("搜索成功, 下标为 %d, 元素为 %d\n", x, list1.element[x]);

    // 顺序搜索（有序表）
    printf("顺序搜索（有序表）：\n");
    int y = SeqSearchOrder(list2, 56);
    if(y == -1)
        printf("搜索失败\n");
    else
        printf("搜索成功, 下标为 %d, 元素为 %d\n", y, list2.element[y]);

    // 顺序搜索（有序表有哨兵）
    printf("顺序搜索（有序表有哨兵）：\n");
    int z = SeqSearchSentry(list3, 99);
    if(z == -1)
        printf("搜索失败\n");
    else
        printf("搜索成功, 下标为 %d, 元素为 %d\n", z, list3.element[z]);

    free(list1.element);
    free(list2.element);
    free(list3.element);
    
    return 0;

}

int SeqSearch(ListSet L, ElemType x){
    for(int i = 0; i < L.n; i++)
        if(L.element[i] == x)      // 一个一个搜索直到搜索到为止
            return i;
    return -1;
}

int SeqSearchOrder(ListSet L, ElemType x){
    for(int i = 0; i < L.n; i++){
        if (L.element[i] == x)
            return i;
        else if(L.element[i] > x)    // 顺序表中是从小到大排列的
            return -1;
    }
    return -1;
}

int SeqSearchSentry(ListSet L, ElemType x){
    L.element[L.n] = MaxNum;              // 将最后一个设置为无穷大
    for(int i = 0; L.element[i] < x; i++) // 让L中的每个元素跟x比较，若匹配到了最后一个哨兵还没有x，就说明搜索失败
        if(L.element[i] == x)             // 一个一个搜索直到搜索到为止
            return i;
    return -1;
}