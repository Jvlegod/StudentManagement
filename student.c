#include "student.h"
#include <stdlib.h>
#include "list.h"

static void swapStudent(struct _StudentManger *manage, Student_t *s1, Student_t *s2)
{
    Student_t s3;
    memcpy(s3.name, s1->name, sizeof(s1->name));
    s3.score = s1->score;
    s3.age = s1->age;
    s3.sex = s1->sex;
    memcpy(s3.id, s1->id, sizeof(s1->id));

    memcpy(s1->name, s2->name, sizeof(s2->name));
    s1->score = s2->score;
    s1->age = s2->age;
    s1->sex = s2->sex;
    memcpy(s1->id, s2->id, sizeof(s2->id));

    memcpy(s2->name, s3.name, sizeof(s3.name));
    s2->score = s3.score;
    s2->age = s3.age;
    s2->sex = s3.sex;
    memcpy(s2->id, s3.id, sizeof(s3.id));
}

bool StudentManager_init(StudentManger_t *manage, int maxlen)
{
    // 初始化链表
    klist_init(&manage->all);

    manage->capacity = maxlen;

    manage->append = StudentManager_add;
    manage->get_len = StudentManager_get_len;
    manage->display = StudentManager_display;
    manage->delt = StudentManager_delete;
    manage->insert = StudentManager_insert;
    manage->indexOf = StudentManager_indexOf;
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
        break;
    case INSERT_TAIL:
        klist_append(&manage->all, &s->node);
        break;
    default:
        return false;
        break;
    }
    return true;
}

void StudentManager_display(struct _StudentManger *manage)
{
    int len = manage->get_len(manage);
    printf("序号\t姓名\t性别\t学号\t分数\n");

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
        printf("%d\t%s\t%s\t%s\t%d\n", i, s->name, sex, s->id, s->score);
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

    // 检查是否超界
    if (idx >= n)
    {
        idx = n;
    }

    // 为负数则在开头插入
    if (idx <= -1)
    {
        klist_push(&manage->all, &s->node);
    }

    klist_node_t *node = manage->all.head.next;
    for (int i = 0; i < idx; i++)
    {
        node = node->next;
    }

    if (node != nullptr)
    {
        klist_insert(&manage->all, node, &s->node);
        return true;
    }
    return false;
}

int StudentManager_get_len(struct _StudentManger *manage)
{
    return klist_len(&manage->all);
}

Student_t *StudentManager_indexOf(struct _StudentManger *manage, int idx)
{
    int n = manage->get_len(manage);

    if (idx >= n)
    {
        return false;
    }

    klist_node_t *node = manage->all.head.next;
    for (int i = 0; i < idx; i++)
    {
        node = node->next;
    }

    if (!node)
    {
        return KLIST_STRUCT_ADDR(node, Student_t, node);
    }

    return nullptr;
}

bool StudentManager_sort(struct _StudentManger *manage, uint8_t METHOD)
{
    switch (METHOD)
    {
    case SORT_UPPER:
        for (klist_node_t *node = manage->all.tail.prev; node != &manage->all.head; node = node->prev)
        {
            for (klist_node_t *nodej = manage->all.head.next; (nodej->next != nullptr) && (nodej->next->next != node); nodej = nodej->next)
            {
                Student_t *pnode = KLIST_STRUCT_ADDR(nodej, Student_t, node);
                Student_t *nnode = KLIST_STRUCT_ADDR(nodej->next, Student_t, node);
                if (pnode->score < nnode->score)
                {
                    swapStudent(manage, pnode, nnode);
                }
            }
        }
        break;
    case SORT_LOWER:
        for (klist_node_t *node = manage->all.tail.prev; node != &manage->all.head; node = node->prev)
        {
            for (klist_node_t *nodej = manage->all.head.next; (nodej->next != nullptr) && (nodej->next->next != node); nodej = nodej->next)
            {
                Student_t *pnode = KLIST_STRUCT_ADDR(nodej, Student_t, node);
                Student_t *nnode = KLIST_STRUCT_ADDR(nodej->next, Student_t, node);
                if (pnode->score > nnode->score)
                {
                    swapStudent(manage, pnode, nnode);
                }
            }
        }
        break;
    default:
        return false;
        break;
    }
    return true;
}
