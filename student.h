#ifndef __STUDENT__
#define __STUDENT__
#include "tools.h"
#include "list.h"
#include "sortTree.h"
#include "global.h"
#include <stdio.h>
#include <string.h>

#define NAME_LEN 255
#define STUDENT_LEN 255
#define ID_LEN 255

// 排序方法
#define SORT_UPPER 0 // 升序
#define SORT_LOWER 1 // 降序

// 插入方法
#define INSERT_HEAD 0 // 头插
#define INSERT_TAIL 1 // 尾插

typedef enum
{
    GIRL,
    BOY,
} Sex_t;

typedef struct _Student
{
    klist_node_t node; // 链表结点

    char name[NAME_LEN]; // 姓名
    int score;           // 分数（暂时只看单科的成绩）
    int age;             // 年龄
    Sex_t sex;           // 性别
    char id[ID_LEN];     // 学号
} Student_t;

typedef struct _StudentManger
{
    kdouble_list_t all; // 全体学生的名单
    SortTree *sortTree;
    int capacity; // 容量

    // 增加
    bool (*append)(struct _StudentManger *manage, Student_t *s, uint8_t METHOD); // 加入学生
    bool (*insert)(struct _StudentManger *manage, Student_t *s, int idx);        // 在序号idx后插入,如果idx为-1则再头结点处插入
    // 查找
    Student_t *(*indexOfNum)(struct _StudentManger *manage, int idx);           // 索引序号为idx的学生
    Student_t *(*indexOfId)(struct _StudentManger *manage, const char *id);     // 索引学号为id的学生
    Student_t *(*indexOfName)(struct _StudentManger *manage, const char *name); // 索引名字为idx的学生
    void (*display)(struct _StudentManger *manage);                             // 显示学生信息
    int (*get_len)(struct _StudentManger *manage);
    // 删除
    bool (*delt)(struct _StudentManger *manage, Student_t *s); // 删除学生
    // 排序
    void (*sort)(struct _StudentManger *manage, uint8_t METHOD); // 对学生进行排序
} StudentManger_t;

Student_t *Student_init(const char *name, int score, int age, const char *id, Sex_t sex);
bool Student_free(Student_t *s);

bool StudentManager_init(StudentManger_t *manage, int maxlen);                        // 初始化学生列表
bool StudentManager_add(struct _StudentManger *manage, Student_t *s, uint8_t METHOD); // 加入学生
int StudentManager_get_len(struct _StudentManger *manage);                            // 获取学生的人数
void StudentManager_display(struct _StudentManger *manage);                           // 展示成绩
bool StudentManager_delete(struct _StudentManger *manage, Student_t *s);
bool StudentManager_insert(struct _StudentManger *manage, Student_t *s, int idx);       // 在索引点插入元素
Student_t *StudentManager_indexOfNum(struct _StudentManger *manage, int idx);           // 索引序号
Student_t *StudentManager_indexOfId(struct _StudentManger *manage, const char *id);     // 索引学号
Student_t *StudentManager_indexOfName(struct _StudentManger *manage, const char *name); // 索引姓名
bool StudentManager_sort(struct _StudentManger *manage, uint8_t METHOD);                // 排序

#endif // !__STUDENT__
