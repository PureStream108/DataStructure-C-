#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct btnote BTNode;
typedef struct binarytree BinaryTree;
typedef char ElemType;

struct btnote{
    ElemType element;  // ElemType element 自己随便定类型
    BTNode *lChild;    // 左子树
    BTNode *rChild;    // 右子树
};

struct binarytree{
    BTNode *root;          // 创建二叉树
};

// 前置声明，避免顺序问题
void CreateTree(BinaryTree *bt);
BTNode* NewNode(ElemType x, BTNode *ln, BTNode *rn);
void MakeTree(BinaryTree *bt, ElemType x, BinaryTree *left, BinaryTree *right);
void ClearTree(BinaryTree *bt);
int TreeSize(BinaryTree *bt);
int Size(BTNode *t);

int main(){
    BinaryTree a, b, x, y, z;
    int size;
    CreateTree(&a);CreateTree(&b);CreateTree(&x);CreateTree(&y);CreateTree(&z);
    MakeTree(&y, 'P', &a, &b);    // 初始AB都为NULL，所以y结点只包含根节点P；
    MakeTree(&z, 'u', &a, &b);    // 同上
    MakeTree(&x, 'r', &y, &z);    
    // 现在X的根结点为r，然后左右结点分别为P，u，且y,z现在重置为空(这与maketree的最后一句对应)
    MakeTree(&y, 'e', &a, &b);
    MakeTree(&z, 'S', &y, &x);   // 现在z根结点为S，然后左子树为e，右结点为x(r-P,r-u)
    // 现在整体为 <S,e>,<S,r>,<r,P>,<r-u>
    printf("结点数量：\n");
    size = TreeSize(&z);
    printf("%d", size);
    ClearTree(&z);    // 动态清空二叉树
    return 0;
}


void CreateTree(BinaryTree *bt){
    bt -> root = NULL;        // 设置根节点为空即可
}

BTNode* NewNode(ElemType x, BTNode *ln, BTNode *rn){    // 动态数组：新结点带一个自己的元素和左右孩子
    BTNode *p = (BTNode *)malloc(sizeof(BTNode));
    p -> element = x;
    p -> lChild = ln;
    p -> rChild = rn;
}

bool Root(BinaryTree *bt, ElemType *x){   // 若二叉树非空则X为根结点的值，如果没找到值就是空结点
    if(bt -> root){
        x = &bt -> root -> element;
        return true;
    } else {
        return false;
    }
}

void MakeTree(BinaryTree *bt, ElemType x, BinaryTree *left, BinaryTree *right){ // 定义左右子树
    if(bt -> root || left == right)
        return;
    bt -> root = NewNode(x, left -> root, right -> root); // 调用NewNode来创建新的二叉树
    left -> root = right -> root = NULL;                  // 将原本的左右结点重置为空
}


// 递归清空树
void ClearTree(BinaryTree *bt){
    if(bt->root){
        BinaryTree left, right;
        left.root = bt->root->lChild;
        right.root = bt->root->rChild;
        ClearTree(&left);
        ClearTree(&right);
        free(bt->root);
        bt->root = NULL;
    }
}

int TreeSize(BinaryTree *bt){
    return Size(bt -> root);
}

int Size(BTNode *t){
    if(!t)
        return 0;
    else
        return Size(t -> lChild) + Size(t -> rChild) + 1;
        // 如果 +1 放在最后就是说明符合后序遍历思想，最前面：先序，中间：中序
}