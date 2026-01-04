#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define maxSize 100         // 可存储的非零元上限
typedef int ElemType;       
typedef struct term Term;
typedef struct sparsematrix SparseMatrix;

struct term{
    int col, row;   // 非零元在稀疏矩阵中的列下标col和行下标row
    ElemType value; // 非零元的值
};

struct sparsematrix{
    int m, n, t;            // m是矩阵行数，n是矩阵列数，t是实际非零元个数
    Term table[maxSize];    // 存储非零元的三元组表
};