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
    manager.display(&manager, SHOW_ALL);
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
        // 加入单体查询
        set_nowait();
        printf("\033[1;34m输入-1查询全部,或者输入id查询\033[0m\n");
        char *id[ID_LEN];
        scanf("%s", id);
        if (strcmp(id, "-1") == 0)
        {
            manager.display(&manager, SHOW_ALL);
        }
        else
        {
            Student_t *s = manager.indexOfId(&manager, id);
            manager.display(&manager, s);
            getchar();
            getchar();
        }
        set_wait();
        break;
    case 2:
        enter_State(MODIFY_INTERFACE);
        break;
    case 3:
        set_nowait();
        printf("\033[1;34m0.升序, 1.降序\033[0m\n");
        set_wait();
        uint8_t sort_method;
        sort_method = getchar();
        manager.sort(&manager, sort_method - '0');
        // enter_State(SORT_INTERFACE);
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
    printf("\t3. 修改学生\n");
    printf("\t4. 返回上一界面\n");
    printf("\t5. 退出\033[0m\n");
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
        // 修改学生信息
        set_nowait();
        printf("请输入要查询学生的id:\n");
        char tid[ID_LEN];
        memset(tid, 0, sizeof(ID_LEN));
        scanf("%s", tid);
        Student_t *ts = manager.indexOfId(&manager, tid);
        if (ts != nullptr)
        {
            char name[NAME_LEN];
            int score;
            int age = -1;
            char id[ID_LEN];
            Sex_t sex;

            memset(id, 0, sizeof(id));

            printf("请依次输入学生的姓名、成绩、年龄、学号、性别(0表示女，1表示男):\n");
            scanf("%s %d %d %s %d", name, &score, &age, id, (int *)&sex);
            memcpy(ts->name, name, sizeof(name));
            ts->score = score;
            ts->age = age;
            ts->sex = sex;
            memcpy(ts->id, id, sizeof(id));
        }
        else
        {
            printf("\033[1;31m插入失败,该学号不存在!\033[0m\n");
            getchar();
            getchar();
        }
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

    memset(id, 0, sizeof(id));

    if (choice < 4)
    {
        set_nowait();
        printf("请依次输入学生的姓名、成绩、年龄、学号、性别(0表示女，1表示男):\n");
        scanf("%s %d %d %s %d", name, &score, &age, id, (int *)&sex);
        s = Student_init(name, score, age, id, sex);

        // 检查id是否重复
        Student_t *temp = manager.indexOfId(&manager, id);
        if (temp != nullptr)
        {
            printf("\033[1;31m插入失败,该学号已存在!\033[0m\n");
            getchar();
            getchar();
            set_wait();
            return;
        }

        // 不支持中文
        // 检查姓名是否合法
        int name_len = strlen(name);
        for (int i = 0; i < name_len; i++)
        {
            if ((name[i] < 'a' || name[i] > 'z') || (name[i] < 'A' && name[i] > 'Z'))
            {
                printf("\033[1;31m插入失败,该姓名不合法!\033[0m\n");
                getchar();
                getchar();
                set_wait();
                return;
            }
        }
        // 检查年龄是否合法
        if (age <= 0 || age > 150)
        {
            printf("\033[1;31m插入失败,该年龄不合法!\033[0m\n");
            getchar();
            getchar();
            set_wait();
            return;
        }

        // 检查学号是否合法
        int str_len = strlen(id);
        if (str_len < 0 || str_len > 50)
        {
            printf("\033[1;31m插入失败,该学号不合法!\033[0m\n");
            getchar();
            getchar();
            set_wait();
            return;
        }

        // 检查性别是否输入正确
        if (sex != (Sex_t)0 && sex != (Sex_t)1)
        {
            printf("\033[1;31m插入失败,该性别输入不合法!\033[0m\n");
            getchar();
            getchar();
            set_wait();
            return;
        }
        set_wait();
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