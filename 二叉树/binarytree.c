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
void PreOrderTree(BinaryTree *tree);
void PreOrder(BTNode *t);
void InOrderTree(BinaryTree *bt);
void InOrder(BTNode *t);
void PostOrderTree(BinaryTree *bt);
void PostOrder(BTNode *t);


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


// 先序遍历(本质上是一种递归)
// 访问根结点 -> 遍历左子树 -> 遍历右子树
void PreOrderTree(BinaryTree *bt){
    PreOrder(bt -> root);
}

// O(n) n为结点数量
void PreOrder(BTNode* t){
    if(!t)
        return;   // 空树则直接返回
    printf("%c -> ", t -> element);  // 打印值
    PreOrder(t -> lChild);    // 先访问左子树，若空则下一步访问右子树
    PreOrder(t -> rChild);
}

// 中序遍历，先从最左边的一个结点开始遍历
// 遍历左子树 -> 遍历根结点 -> 遍历右子树
void InOrderTree(BinaryTree *bt){
    InOrder(bt -> root);
}

void InOrder(BTNode* t){
    if(!t)
        return;
    InOrder(t -> lChild);           // 中序遍历左子树
    printf("%c -> ", t -> element); // 访问根结点
    InOrder(t -> rChild);           // 中序遍历右子树
}

// 后序遍历
// 遍历左子树 -> 遍历右子树 -> 访问根结点
void PostOrderTree(BinaryTree *bt){
    PostOrder(bt -> root);
}

void PostOrder(BTNode* t){
    if(!t)
        return;
    PostOrder(t -> lChild);         // 后序遍历左子树
    PostOrder(t -> rChild);         // 后序遍历右子树
    printf("%c -> ", t -> element); // 访问根结点
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

int main(){
    BinaryTree a, b, x, y, z;
    CreateTree(&a);CreateTree(&b);CreateTree(&x);CreateTree(&y);CreateTree(&z);
    MakeTree(&y, 'P', &a, &b);    // 初始AB都为NULL，所以y结点只包含根节点P；
    MakeTree(&z, 'u', &a, &b);    // 同上
    MakeTree(&x, 'r', &y, &z);    
    // 现在X的根结点为r，然后左右结点分别为P，u，且y,z现在重置为空(这与maketree的最后一句对应)
    MakeTree(&y, 'e', &a, &b);
    MakeTree(&z, 'S', &y, &x);   // 现在z根结点为S，然后左子树为e，右结点为x(r-P,r-u)
    // 现在整体为 <S,e>,<S,r>,<r,P>,<r-u>
    printf("先序遍历：\n");
    PreOrderTree(&z); // 先序遍历二叉树
    printf("\n");
    printf("中序遍历：\n");
    InOrderTree(&z);  // 中序遍历
    printf("\n");
    printf("后序遍历：\n");
    PostOrderTree(&z); // 后序遍历
    ClearTree(&z);    // 动态清空二叉树
    return 0;
}