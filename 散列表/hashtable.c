#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define NoPresent -1
#define NeverUsed -99

typedef int BOOL;
typedef struct hashtable HashTable;

struct hashtable{
    int M;                // 散列表的长度
    int num;              // 散列表中存储的元素数量
    BOOL *empty;          // 标记数组是否为空
    int *elements;        // 元素数组，先假设每个数组只存一个关键字
};

void CreateHT(HashTable *ht, int size); // 初始化散列表，size表示长度
void DestoryHT(HashTable *ht);
bool IsEmpty(HashTable *ht);
void ClearHT(HashTable *ht);
bool IsFull(HashTable *ht);
int Hash(int M, int key);
int Search(HashTable *ht, int key);
bool Insert(HashTable *ht, int key);
bool Delete(HashTable *ht, int key);
void Output(HashTable *ht);

int main(){
    HashTable ht;
    int size = 10;
    //创建散列表
    CreateHT(&ht, 10);

    //插入元素
    Insert(&ht, 5);
    Insert(&ht, 15);
    Insert(&ht, 25);
    Insert(&ht, 35);
    Insert(&ht, 45);
    Insert(&ht, 55);
    Insert(&ht, 65);
    Insert(&ht, 75);
    Insert(&ht, 85);
    Insert(&ht, 95);

    //打印散列表
    printf("散列表内容：\n");
    Output(&ht);

    //搜索元素
    printf("搜索元素15: ");
    int pos = Search(&ht, 15);
    if(pos != NoPresent)
        printf("找到，位置在 %d\n", pos);
    else
        printf("未找到\n");

    //删除元素
    Delete(&ht, 15);
    printf("删除15后的散列表：\n");
    Output(&ht);

    //清空散列表
    ClearHT(&ht);
    printf("清空后的散列表：\n");
    Output(&ht);

    //销毁散列表
    DestoryHT(&ht);
    return 0;
}

void CreateHT(HashTable *ht, int size){
    ht -> M = size;
    ht -> empty = (BOOL*)malloc(sizeof(BOOL)*size);
    ht -> elements = (int*)malloc(sizeof(int)*size);
    ht -> num = 0;
    for(int i = 0; i < size; i++){     // 初始化一个空的散列表，每个格子都是没有被使用过的，且是True
        ht -> empty[i] = true;
        ht -> elements[i] = NeverUsed;
    }
}

void DestoryHT(HashTable *ht){
    free(ht -> empty);
    free(ht -> elements);
}

void ClearHT(HashTable *ht){  // 清空散列表，即全部变成True和NeverUsed
    for(int i = 0; i < ht -> M; i++){
        ht -> empty[i] = true;
        ht -> elements[i] = NeverUsed;
    }
    ht -> num = 0;
}

bool IsEmpty(HashTable *ht){
    if(ht -> num == 0)
        return true;
    else
        return false;
}

bool IsFull(HashTable *ht){
    if(ht -> num == ht -> M)
        return true;
    else
        return false;
}

// 除留余数法的散列函数
int Hash(int M, int key){
    return key % M;
}

// 查找关键字为key的元素，查找成功返回true，失败范围NoPresent
int Search(HashTable *ht, int key){
    int anchor, pos;
    anchor = pos = Hash(ht -> M, key); // 计算key的基地址
    do{                                //
        if(ht -> empty[pos])           // 判断探查过程中是否存在空地址，存在则失败
            return NoPresent;
        if(ht -> elements[pos] == key)    // 找到则返回所在位置
            return pos;                // 设置pos为下一个探查位置
        pos = (pos + 1) % ht -> M;     // 当pos==anchor说明已经搜索完整个散列表了
    }while(pos != anchor);
    return NoPresent;
}

bool Insert(HashTable *ht, int key){
    int anchor, pos;
    if(IsFull(ht))
        return false;
    if(Search(ht, key) != NoPresent)
        return false;
    pos = anchor = Hash(ht -> M, key);
    do{
        if(ht -> empty[pos]){           // 如果位置是空的就直接插入
            ht -> elements[pos] = key;
            ht -> empty[pos] = false;
            ht -> num++;
            return true;
        }
        pos = (pos + 1) % ht -> M;
    }while(pos != anchor);
    return false;
}

bool Delete(HashTable *ht, int key){
    if(IsEmpty(ht))
        return false;
    int pos = Search(ht, key);
    if(pos == NoPresent){    
        return false;
    }else{
        ht -> elements[pos] = NeverUsed;
        ht -> num--;                        // 删除元素不需要将empty改成true
        return true;
    }
}

void Output(HashTable *ht){
    for(int i = 0; i < ht -> M; i++){
        printf("%5d ", ht -> elements[i]);
    }
    printf("\n");
    for(int i = 0; i < ht -> M; i++){
        printf("%5d ", ht -> empty[i]);
    }
    printf("\n");
}

