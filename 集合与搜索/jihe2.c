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

int BinarySearch(ListSet L, ElemType x, int low, int high);

int main(){
    int arr[] = {11, 34, 56, 65, 78};// 有序表

    ListSet list;
    list.n = 6;
    list.maxLength = 10;
    list.element = (ElemType*)malloc(list.maxLength*sizeof(ElemType));
    for(int i = 0; i < list.n; i++)
        list.element[i] = arr[i];

    // 二分法（有序表）
    printf("二分查询（有序表）：\n");
    int y = BinarySearch(list, 65, 0, list.n - 1);
    if(y == -1)
        printf("搜索失败\n");
    else
        printf("搜索成功, 下标为 %d, 元素为 %d\n", y, list.element[y]);
    
}

int BinarySearch(ListSet L, ElemType x, int low, int high){
    if(low <= high){
        int m = (low + high) / 2;
        if(L.element[m] > x)
            return BinarySearch(L, x, low, m - 1); // 中点比x大，说明x在左半边
        else if(L.element[m] < x)
            return BinarySearch(L, x, m + 1, high);// 中点比x小，说明x在右半边
        else
            return m;
    }
    else
        return -1;
}

// int BinarySearch(ListSet L, ElemType x){
//     int m, low = 0;
//     int high = L.n - 1;
//     while(low <= high){
//      	m = (low + high) / 2;
//         if(L.element[m] > x)
//             return BinarySearch(L, x, low, m - 1); // 中点比x大，说明x在左半边
//         else if(L.element[m] < x)
//             return BinarySearch(L, x, m + 1, high);// 中点比x小，说明x在右半边
//         else
//             return m;
//     }    
//     return -1;
// }