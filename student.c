#include <stdlib.h>
#include "student.h"
#include "list.h"

// 接收数组
char *recv_buffer[ID_LEN];
int recv_idx;

static void Student_fromcopyTo(Student_t *s1, Student_t *s2)
{
    memcpy(s2->name, s1->name, sizeof(s1->name));
    s2->score = s1->score;
    s2->age = s1->age;
    s2->sex = s1->sex;
    memcpy(s2->id, s1->id, sizeof(s1->id));
}

static void swapStudent(Student_t *s1, Student_t *s2)
{
    Student_t s3;
    Student_fromcopyTo(s1, &s3);
    Student_fromcopyTo(s2, s1);
    Student_fromcopyTo(&s3, s2);
}

bool StudentManager_init(StudentManger_t *manage, int maxlen)
{
    // 初始化链表
    klist_init(&manage->all);
    manage->sortTree = SortTree_Init("-1");

    manage->capacity = maxlen;

    manage->append = StudentManager_add;
    manage->get_len = StudentManager_get_len;
    manage->display = StudentManager_display;
    manage->delt = StudentManager_delete;
    manage->insert = StudentManager_insert;
    manage->indexOfNum = StudentManager_indexOfNum;
    manage->indexOfId = StudentManager_indexOfId;
    manage->indexOfName = StudentManager_indexOfName;
    manage->sort = StudentManager_sort;

    return true;
}

Student_t *Student_init(const char *name, int score, int age, const char *id, Sex_t sex)
{
    Student_t *s = (Student_t *)malloc(sizeof(Student_t));
    memcpy(s->name, name, sizeof(name));
    s->score = score;
    s->age = age;
    s->sex = sex;
    memcpy(s->id, id, sizeof(id));

    s->get_name = Student_get_name;
    s->get_score = Student_get_score;
    s->get_age = Student_get_age;
    s->get_sex = Student_get_sex;
    s->get_id = Student_get_id;
    return s;
}

bool Student_free(Student_t *s)
{
    if (s == nullptr)
    {
        return false;
    }
    free(s);
    return true;
}

bool StudentManager_add(struct _StudentManger *manage, Student_t *s, uint8_t METHOD)
{
    switch (METHOD)
    {
    case INSERT_HEAD:
        klist_push(&manage->all, &s->node);
        SortTree_insert(manage->sortTree, s->id);
        break;
    case INSERT_TAIL:
        klist_append(&manage->all, &s->node);
        SortTree_insert(manage->sortTree, s->id);
        break;
    default:
        return false;
        break;
    }
    return true;
}

void StudentManager_display(struct _StudentManger *manage, Student_t *target)
{
    int len = manage->get_len(manage);
    printf("序号\t姓名\t性别\t年龄\t学号\t分数\n");

    klist_node_t *temp = manage->all.head.next;
    for (int i = 0; i < len; i++)
    {
        Student_t *s = KLIST_STRUCT_ADDR(temp, Student_t, node);
        char sex[5];
        memset(sex, 0, sizeof(sex));
        if (s->sex == BOY)
        {
            strcpy(sex, "boy");
        }
        else
        {
            strcpy(sex, "girl");
        }

        // 加入单体查询
        if (s != SHOW_ALL && target == s)
        {
            printf("\033[1;32m%d\t%s\t%s\t%d\t%s\t%d\033[0m\n", i, s->name, sex, s->age, s->id, s->score);
        }
        else
        {
            printf("%d\t%s\t%s\t%d\t%s\t%d\n", i, s->name, sex, s->age, s->id, s->score);
        }

        // 整体查询
        // printf("%d\t%s\t%s\t%s\t%d\n", i, s->name, sex, s->id, s->score);

        temp = temp->next;
    }
    puts("");
}

bool StudentManager_delete(struct _StudentManger *manage, Student_t *s)
{
    int n = manage->get_len(manage);
    if (n <= 0)
    {
        return false;
    }

    SortTree_delete(manage->sortTree, manage->sortTree, s->id);
    bool ret = klist_delete(&manage->all, &s->node);
    Student_free(s);

    if (!ret)
    {
        return false;
    }
    return true;
}

bool StudentManager_insert(struct _StudentManger *manage, Student_t *s, int idx)
{
    int n = manage->get_len(manage);
    // 容量是否满
    if (n >= manage->capacity)
    {
        return false;
    }

    // 链表为空
    if (n == 0)
    {
        klist_push(&manage->all, &s->node);
        SortTree_insert(manage->sortTree, s->id);
        return true;
    }

    // 检查是否超界
    if (idx >= n)
    {
        idx = n - 1;
    }

    // 为负数则在开头插入
    if (idx <= -1)
    {
        klist_push(&manage->all, &s->node);
        SortTree_insert(manage->sortTree, s->id);
        return true;
    }

    klist_node_t *node = manage->all.head.next;
    for (int i = 0; i < idx; i++)
    {
        node = node->next;
    }

    if (node != nullptr)
    {
        klist_insert(&manage->all, node, &s->node);
        SortTree_insert(manage->sortTree, s->id);
        return true;
    }
    return false;
}

int StudentManager_get_len(struct _StudentManger *manage)
{
    return klist_len(&manage->all);
}

Student_t *StudentManager_indexOfNum(struct _StudentManger *manage, int idx)
{
    int n = manage->get_len(manage);

    if (n == 0)
    {
        return nullptr;
    }

    if (idx >= n)
    {
        return nullptr;
    }

    klist_node_t *node = manage->all.head.next;
    for (int i = 0; i < idx; i++)
    {
        node = node->next;
    }

    if (node)
    {
        return KLIST_STRUCT_ADDR(node, Student_t, node);
    }

    return nullptr;
}

Student_t *StudentManager_indexOfId(struct _StudentManger *manage, const char *id)
{
    int n = manage->get_len(manage);

    if (n == 0)
    {
        return nullptr;
    }

    klist_node_t *node = manage->all.head.next;
    while (node && node != &manage->all.tail)
    {
        Student_t *s = KLIST_STRUCT_ADDR(node, Student_t, node);

        if (strcmp(s->id, id) == 0)
        {
            return s;
        }

        node = node->next;
    }

    return nullptr;
}

Student_t *StudentManager_indexOfName(struct _StudentManger *manage, const char *name)
{
    int n = manage->get_len(manage);

    if (n == 0)
    {
        return nullptr;
    }

    klist_node_t *node = manage->all.head.next;
    while (node && node != &manage->all.tail)
    {
        Student_t *s = KLIST_STRUCT_ADDR(node, Student_t, node);

        if (strcmp(s->name, name) == 0)
        {
            return s;
        }

        node = node->next;
    }

    return nullptr;
}

bool StudentManager_sort(struct _StudentManger *manage, uint8_t METHOD)
{
    if (manage->get_len(manage) == 0)
    {
        return false;
    }

    Student_t s_arr[STUDENT_LEN];

    switch (METHOD)
    {
    case SORT_UPPER:

        // 冒泡排序
        // for (klist_node_t *node = manage->all.tail.prev; node != &manage->all.head; node = node->prev)
        // {
        //     for (klist_node_t *nodej = manage->all.head.next; (nodej->next != nullptr) && (nodej->next->next != node); nodej = nodej->next)
        //     {
        //         Student_t *pnode = KLIST_STRUCT_ADDR(nodej, Student_t, node);
        //         Student_t *nnode = KLIST_STRUCT_ADDR(nodej->next, Student_t, node);
        //         if (pnode->score < nnode->score)
        //         {
        //             swapStudent(pnode, nnode);
        //         }
        //     }
        // }

        recv_idx = 0;
        SortTree_show(manage->sortTree);

        memset(s_arr, 0, sizeof(Student_t) * STUDENT_LEN);

        for (int i = 1; i < recv_idx; i++)
        {
            Student_t *ts = manage->indexOfId(manage, recv_buffer[i]);
            Student_fromcopyTo(ts, &s_arr[i]);
        }

        recv_idx--;

        for (klist_node_t *node = manage->all.head.next; node != nullptr && node != &manage->all.tail; node = node->next)
        {
            Student_t *s2 = KLIST_STRUCT_ADDR(node, Student_t, node);
            Student_fromcopyTo(&s_arr[recv_idx--], s2);
        }
        break;
    case SORT_LOWER:
        // 二叉排序树
        recv_idx = 0;
        SortTree_show(manage->sortTree);

        memset(s_arr, 0, sizeof(Student_t) * STUDENT_LEN);

        for (int i = 1; i < recv_idx; i++)
        {
            Student_t *ts = manage->indexOfId(manage, recv_buffer[i]);
            Student_fromcopyTo(ts, &s_arr[i]);
        }
        recv_idx = 1;

        for (klist_node_t *node = manage->all.head.next; node != nullptr && node != &manage->all.tail; node = node->next)
        {
            Student_t *s2 = KLIST_STRUCT_ADDR(node, Student_t, node);
            Student_fromcopyTo(&s_arr[recv_idx++], s2);
        }
        break;
    default:
        return false;
        break;
    }
    return true;
}

const char *Student_get_name(struct _Student *s)
{
    return s->name;
}

const int Student_get_score(struct _Student *s)
{
    return s->score;
}

const int Student_get_age(struct _Student *s)
{
    return s->age;
}

const Sex_t Student_get_sex(struct _Student *s)
{
    return s->sex;
}

const char *Student_get_id(struct _Student *s)
{
    return s->id;
}