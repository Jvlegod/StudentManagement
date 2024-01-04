#ifndef __SORT_TREE_H__
#define __SORT_TREE_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"
// 注:整段排序树的代码耦合度非常高

typedef struct _SortTree
{
    char id[255]; // 通过id索引
    struct _SortTree *left;
    struct _SortTree *right;
} SortTree;

SortTree *SortTree_Init(char *key);
void SortTree_insert(SortTree *root, char *key);
void SortTree_show(SortTree *root);
int SortTree_delete(SortTree *root, SortTree *sortTree, char *key);
SortTree *prev_SortTree(SortTree *root, SortTree *SortTree, char *key);

#endif // !__SORT_H__