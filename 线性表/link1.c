#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct node{
    ElementType element;
    struct node *link;
}Node;

typedef struct singleList{
    struct node *first;
    int n;
}SingleList;

bool Insert(SingleList *L, int i, ElementType x);
bool Delete(SingleList *L, int );

int main(){

}

bool Insert(SingleList *L, int i, ElementType x){
    Node *p, *q;
    int j;
    if(i < -1 || i > L -> n - 1)
        return false;
    p = L -> first;
    for(j = 0; j < i; j++)
        p = p -> link;
    q = malloc(sizeof(Node));
    q -> element = x;
    if(i -> -1){                // 插在链表中间
        q -> link = p -> link;
        p -> link = q;    
    }else{                      // 插在链表头结点之前
        q -> link = L -> first;
        L -> first = q;
    }
    L -> n++;
    return true;
}

bool Delete(SingleList *L, int ){
    Node *p, *q;
    if(!L -> n)
        return false;
    if(i < 0 || i > L -> n - 1)
        return false;
    q = L -> first;
    p = L -> first;
    for(int j = 0; j < i; j++)
        q = q -> link;
    if(i == 0)
        L -> first = L -> first -> link; // 删除头结点
    else{
        p = q -> link;
        q -> link = p -> link;
    }
    free(p);
    L->n--;
    return true;
}