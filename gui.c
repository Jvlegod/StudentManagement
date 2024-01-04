#include "gui.h"

extern StudentManger_t manager;

void main_interface()
{
    uint8_t choice;
    printf("\033[1;31m========== 学生信息管理系统 ==========\033[0m\n");
    printf("\033[1;32m\t1. 查询学生信息\n");
    printf("\t2. 修改学生信息\n");
    printf("\t3. 退出\033[0m\n");
    printf("\033[1;34m======================================\033[0m\n");
    choice = getchar() - '0';
    switch (choice)
    {
    case 1:
        enter_State(INFORMATION_INTERFACE);
        break;
    case 2:
        enter_State(MODIFY_INTERFACE);
        break;
    case 3:
        enter_State(EXIT_INTERFACE);
        break;
    default:
        break;
    }
}

void information_interface()
{
    // 先展示画面
    manager.display(&manager);
    uint8_t choice;
    printf("\033[1;31m========== 学生信息管理系统 ==========\033[0m\n");
    printf("\033[1;32m\t1. 查询学生信息\n");
    printf("\t2. 修改学生信息\n");
    printf("\t3. 排序学生信息\n");
    printf("\t4. 返回上一界面\n");
    printf("\t5. 退出\033[0m\n");
    printf("\033[1;34m======================================\033[0m\n");
    choice = getchar() - '0';
    switch (choice)
    {
    case 1:
        break;
    case 2:
        enter_State(MODIFY_INTERFACE);
        break;
    case 3:
        set_nowait();
        printf("0.升序, 1.降序");
        int sort_method;
        scanf("%d", &sort_method);
        manager.sort(&manager, sort_method);
        // enter_State(SORT_INTERFACE);
        set_wait();
        break;
    case 4:
        back_State();
        break;
    case 5:
        enter_State(EXIT_INTERFACE);
        break;
    default:
        break;
    }
}

void modify_interface()
{
    uint8_t choice;
    printf("\033[1;31m========== 学生信息管理系统 ==========\033[0m\n");
    printf("\033[1;32m\t1. 增加学生\n");
    printf("\t2. 删除学生\n");
    printf("\t3. 返回上一界面\n");
    printf("\t4. 退出\033[0m\n");
    printf("\033[1;34m======================================\033[0m\n");
    choice = getchar() - '0';
    switch (choice)
    {
    case 1:
        enter_State(ADD_INTERFACE);
        break;
    case 2:
        set_nowait();
        printf("请输入删除学生的下标:\n");
        int indexOfNum = 0;
        scanf("%d", &indexOfNum);
        Student_t *s = manager.indexOfNum(&manager, indexOfNum);
        if (s == nullptr)
        {
            printf("\033[1;31m该序号不存在!\033[0m\n");
            getchar();
            getchar();
            fflush(stdin);
        }
        else
        {
            manager.delt(&manager, s);
        }
        set_wait();
        // enter_State(DELTE_INTERFACE);
        break;
    case 3:
        back_State();
        break;
    case 4:
        enter_State(EXIT_INTERFACE);
        break;
    default:
        break;
    }
}

void add_interface()
{
    uint8_t choice;
    printf("\033[1;31m========== 学生信息管理系统 ==========\033[0m\n");
    printf("\033[1;32m\t1. 头插\n");
    printf("\t2. 尾插\n");
    printf("\t3. 按序号插入\n");
    printf("\t4. 返回上一界面\n");
    printf("\t5. 退出\033[0m\n");
    printf("\033[1;34m======================================\033[0m\n");
    choice = getchar() - '0';

    Student_t *s;
    char name[NAME_LEN];
    int score;
    int age = -1;
    char id[ID_LEN];
    Sex_t sex;

    if (choice < 4)
    {
        set_nowait();
        printf("请依次输入学生的姓名、成绩、年龄、学号、性别(0表示女，1表示男):\n");
        scanf("%s %d %d %s %d", name, &score, &age, id, (int *)&sex);
        s = Student_init(name, score, age, id, sex);
        set_wait();
    }
    Student_t *temp = manager.indexOfId(&manager, id);
    if (temp != nullptr)
    {
        set_nowait();
        printf("\033[1;31m插入失败,该学号已存在!\033[0m\n");
        getchar();
        getchar();
        set_wait();
        return;
    }

    switch (choice)
    {
    case 1:
        manager.append(&manager, s, INSERT_HEAD);
        break;
    case 2:
        manager.append(&manager, s, INSERT_TAIL);
        break;
    case 3:
        set_nowait();
        printf("请输入要插入的序号(非负数):\n");
        int indexOfNum = 0;
        scanf("%d", &indexOfNum);
        manager.insert(&manager, s, indexOfNum);
        set_wait();
        break;
    case 4:
        back_State();
        break;
    case 5:
        enter_State(EXIT_INTERFACE);
        break;
    default:
        break;
    }
}

// 未开发
void sort_interface()
{
}

void delte_interface()
{
}