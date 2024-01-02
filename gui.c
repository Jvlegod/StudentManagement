#include "gui.h"

extern StudentManger_t manager;
extern GUI_State state;
extern GUI_State old_state;

void main_interface()
{
    int choice;
    printf("\033[1;31m========== 学生信息管理系统 ==========\033[0m\n");
    printf("\033[1;32m\t1. 查询学生信息\n");
    printf("\t2. 修改学生信息\n");
    printf("\t3. 退出\033[0m\n");
    printf("\033[1;34m======================================\033[0m\n");
    printf("请选择功能（输入相应的数字）: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        set_State(INFORMATION_INTERFACE);
        break;
    case 2:
        set_State(MODIFY_INTERFACE);
        break;
    case 3:
        set_State(EXIT_INTERFACE);
        break;
    default:
        break;
    }
}

void information_interface()
{
    // 先展示画面
    manager.display(&manager);
    int choice;
    printf("\033[1;31m========== 学生信息管理系统 ==========\033[0m\n");
    printf("\033[1;32m\t1. 查询学生信息\n");
    printf("\t2. 修改学生信息\n");
    printf("\t3. 返回上一界面\n");
    printf("\t4. 退出\033[0m\n");
    printf("\033[1;34m======================================\033[0m\n");
    printf("请选择功能（输入相应的数字）: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        break;
    case 2:
        set_State(MODIFY_INTERFACE);
        break;
    case 3:
        set_State(old_state);
        break;
    case 4:
        set_State(EXIT_INTERFACE);
        break;
    default:
        break;
    }
}

void modify_interface()
{
    int choice;
    printf("\033[1;31m========== 学生信息管理系统 ==========\033[0m\n");
    printf("\033[1;32m\t1. 查询学生信息\n");
    printf("\t2. 增加学生\n");
    printf("\t3. 删除学生\n");
    printf("\t4. 返回上一界面\n");
    printf("\t5. 退出\033[0m\n");
    printf("\033[1;34m======================================\033[0m\n");
    printf("请选择功能（输入相应的数字）: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        set_State(INFORMATION_INTERFACE);
        break;
    case 2:
        set_State(ADD_INTERFACE);
        break;
    case 3:
        set_State(DELTE_INTERFACE);
        break;
    case 4:
        set_State(old_state);
        break;
    case 5:
        set_State(EXIT_INTERFACE);
        break;
    default:
        break;
    }
}

void add_interface()
{
    int choice;
    printf("========== 学生信息管理系统 ==========\n");
    printf("\t1. 新建学生信息\n");
    printf("\t2. 增加学生\n");
    printf("\t3. 删除学生\n");
    printf("\t4. 返回上一界面\n");
    printf("\t5. 退出\n");
    printf("======================================\n");
    printf("请选择功能（输入相应的数字）: ");
    scanf("%d", &choice);

    Student_t *s;
    char name[NAME_LEN];
    int score;
    int age = -1;
    char id[ID_LEN];
    Sex_t sex;

    switch (choice)
    {
    case 1:
        printf("请依次输入学生的姓名、成绩、年龄、学号、性别(0表示女，1表示男):\n");
        scanf("%s %d %d %s %d", name, &score, &age, id, &sex);
        s = Student_init(name, score, age, id, sex);

        int method;

        printf("请选择：0.头插，1.尾插:");
        scanf("%d", &method);
        manager.append(&manager, s, method);
        break;
    case 2:
        set_State(ADD_INTERFACE);
        break;
    case 3:
        set_State(DELTE_INTERFACE);
        break;
    case 4:
        set_State(old_state);
        break;
    case 5:
        set_State(EXIT_INTERFACE);
        break;
    default:
        break;
    }
}

void delte_interface()
{
}