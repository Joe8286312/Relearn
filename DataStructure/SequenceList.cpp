#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>   // 使用 bool 类型

#define INIT_SIZE 10    // 初始容量
#define ElemType int

typedef struct {
    ElemType *data;
    int length;
    int capacity;       // 当前容量，名称更清晰
} SeqList;

// 初始化
void InitList(SeqList *L) {
    L->data = (ElemType *)malloc(INIT_SIZE * sizeof(ElemType));
    if (L->data == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }
    L->length = 0;
    L->capacity = INIT_SIZE;
}

// 销毁列表
void DestroyList(SeqList *L) {
    free(L->data);
    L->data = NULL;
    L->length = 0;
    L->capacity = 0;
}

// 判空
bool IsEmpty(const SeqList *L) {
    return L->length == 0;
}

// 判满（仅在静态容量时有用，若支持动态扩容则无需此函数）
bool IsFull(const SeqList *L) {
    return L->length == L->capacity;
}

// 扩容（内部使用）
static void ExpandCapacity(SeqList *L) {
    int newCapacity = L->capacity * 2;
    ElemType *newData = (ElemType *)realloc(L->data, newCapacity * sizeof(ElemType));
    if (newData == NULL) {
        printf("扩容失败！\n");
        exit(1);
    }
    L->data = newData;
    L->capacity = newCapacity;
}

// 插入：成功返回 true，失败返回 false
bool Insert(SeqList *L, int pos, ElemType elem) {
    if (pos < 1 || pos > L->length + 1) {
        printf("插入位置非法！\n");
        return false;
    }
    // 如果容量不足，先扩容
    if (L->length == L->capacity) {
        ExpandCapacity(L);
    }
    // 后移元素
    for (int i = L->length - 1; i >= pos - 1; i--) {
        L->data[i + 1] = L->data[i];
    }
    L->data[pos - 1] = elem;
    L->length++;
    return true;
}

// 删除：成功返回 true，并通过 e 返回被删元素值
bool Delete(SeqList *L, int pos, ElemType *e) {
    if (pos < 1 || pos > L->length) {
        printf("删除位置非法！\n");
        return false;
    }
    *e = L->data[pos - 1];
    // 前移元素
    for (int i = pos; i < L->length; i++) {
        L->data[i - 1] = L->data[i];
    }
    L->length--;
    return true;
}

// 按位查找：成功返回 true，并通过 e 返回元素值
bool GetElem(const SeqList *L, int pos, ElemType *e) {
    if (pos < 1 || pos > L->length) {
        printf("查找位置非法！\n");
        return false;
    }
    *e = L->data[pos - 1];
    return true;
}

// 按值查找：返回第一个匹配的位置（从1开始），未找到返回0
int LocateElem(const SeqList *L, ElemType elem) {
    for (int i = 0; i < L->length; i++) {
        if (L->data[i] == elem) {
            return i + 1;
        }
    }
    return 0;
}

// 打印列表
void PrintList(const SeqList *L) {
    if (IsEmpty(L)) {
        printf("列表为空\n");
        return;
    }
    for (int i = 0; i < L->length; i++) {
        printf("第%d个元素：%d\n", i + 1, L->data[i]);
    }
    printf("\n");
}

int main() {
    SeqList L;
    InitList(&L);

    Insert(&L, 1, 10);
    Insert(&L, 2, 20);
    Insert(&L, 3, 30);
    PrintList(&L);

    Insert(&L, 2, 33);   // 在位置2插入
    PrintList(&L);

    ElemType elem;
    if (GetElem(&L, 2, &elem)) {
        printf("位置%d上的元素为：%d\n", 2, elem);
    }
    
    printf("元素%d是第%d个元素\n", 20, LocateElem(&L, 20));
    printf("\n");

    ElemType e;
    if (Delete(&L, 4, &e)) {
        printf("删除了元素：%d\n", e);
    }
    PrintList(&L);

    DestroyList(&L);
    return 0;
}
