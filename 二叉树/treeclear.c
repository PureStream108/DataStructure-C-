void TreeClear(BinaryTree *bt);
void Clear(BTNode *t);

void TreeClear(BinaryTree *bt){
    Clear(bt -> root);
}

void Clear(BTNode *t){
    if(!t)
        return;
    Clear(t -> lChild);
    Clear(t -> rChild);
    free(t);   
    // 符合后序遍历思想，但是想要实现先序/中序并不能简单移动free，因为这会导致指针为空，让后续访问空地址错误
}

// 先序
// void Clear(BTNode *t){
//     if(!t) return;
    
//     // 关键：先保存子节点，否则释放后无法访问
//     BTNode *leftChild = t->lChild;
//     BTNode *rightChild = t->rChild;
    
//     free(t);            // 根
    
//     Clear(leftChild);   // 左
//     Clear(rightChild);  // 右
// }

// 中序
// void Clear(BTNode *t){
//     if(!t) return;
    
//     BTNode *rightChild = t->rChild;  // 先保存右孩子
    
//     Clear(t->lChild);   // 左
    
//     free(t);            // 根
    
//     Clear(rightChild);  // 右
// }