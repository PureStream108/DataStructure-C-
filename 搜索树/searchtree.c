#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct entry T;
typedef struct btnode BTNode;
typedef struct btree BTree;
typedef int KeyType;
typedef int DataType;

bool BtSearch(BTree bt, KeyType k, T *x);      // 二叉搜索树的递归调用
BTNode *Find(BTNode *p, KeyType k);            // 二叉搜索树的递归调用
bool BtSearchWhile(BTree bt, KeyType k, T *x); // 二叉搜索树的迭代调用
bool Insert(BTree *bt, T x);                   // 插入操作

struct entry{
    KeyType Key;
    DataType Data;
};

// 定义搜索树节点类型BTNode, 包含集合项、左右子树根结点指针
struct btnode{
    T Element;
    struct BTNode *lChild, *rChild;
};

// 定义搜索树类型BTree，包含根结点
struct btree{
    BTNode *root;
};

// 主函数
int main(){

}

bool BtSearch(BTree bt, KeyType k, T *x){
    BTNode *p = Find(bt.root, k);
    if(p){
        *x = p -> Element;      // 获取搜索到的值
        return true;
    }
    return false;
}

BTNode *Find(BTNode *p, KeyType k){
    if(!p)
        return NULL;
    if(k < p -> Element.Key)        // 如果k比根结点小，那就去左子树找，因为左子树固定比根结点小
        return Find(p -> rlhild, k);
    if(k > p -> Element.Key)        // 如果k比根结点大，那就去右子树找，因为右子树固定比根结点大
        return Find(p -> rChild, k);
    return p;
}

// 二叉搜索树的迭代调用
bool BtSearchWhile(BTree bt, KeyType k, T *x){
    BTNode *p = bt.root;
    while(p){
        if ( k < p -> Element.Key)
            p = p -> lChild;
        else if (k > p -> Element.Key)
            p = p -> rChild;
        else{
            *x = p -> Element;
            return true;
        }
    }
    return false;
}

// 搜索树插入操作
bool Insert(BTree *bt, T x){
    BTNode *p = bt -> root, *q, *r;    // p指针从根结点出发一直到搜索结束
    KeyType k = x.Key;
    while(p){
        q = p;                         // q指针记录搜索失败处的上一层结点
        if ( k < p -> Element.Key)
            p = p -> lChild;
        else if (k > p -> Element.Key)
            p = p -> rChild;
        else
            return false;
    }
    r = NewNode(x);                   // 生成新结点
    if(!bt -> root)
        root = r;                     // r作用是指向新结点
    else if (k < q -> Element.Key)
        q -> lChild = r;              // q指针作用是记录新结点的双亲
    else 
        q - > rChild = r;
    return true;
}