#include <stdio.h>
#include "student.h"
#include "global.h"

extern StudentManger_t manager;
extern GUI_State state;
extern GUI_State old_state;

static int if_debug = 0;

int main(int argc, char *argv[])
{

    // 初始化
    StudentManager_init(&manager, 100);

    if (argc > 1 && strcmp(argv[1], "debug") == 0)
    {
        if_debug = 1;
    }
    if (if_debug == 0)
    {
        while (1)
        {
            switch (state)
            {
            case MAIN_INTERFACE:
                main_interface();
                break;
            case INFORMATION_INTERFACE:
                information_interface();
                break;
            case ADD_INTERFACE:
                add_interface();
                break;
            case MODIFY_INTERFACE:
                modify_interface();
                break;
            case DELTE_INTERFACE:
                delte_interface();
                break;
            case EXIT_INTERFACE:
                goto exit;
                break;
            default:
                break;
            }
            CLEAR;
        }
    }

    Student_t *s1;
    Student_t *s2;
    Student_t *s3;
    Student_t *s4;
    s1 = Student_init("mkk", 100, 18, "123132", BOY);
    s2 = Student_init("pzj", 13, 19, "2131234", BOY);
    s3 = Student_init("tzl", 123, 19, "245422", GIRL);
    s4 = Student_init("pzy", 32, 19, "123523", GIRL);
    manager.display(&manager);
    manager.append(&manager, s1, INSERT_TAIL);
    manager.display(&manager);
    manager.append(&manager, s2, INSERT_HEAD);
    manager.display(&manager);
    manager.append(&manager, s3, INSERT_TAIL);
    manager.display(&manager);
    printf("长度%d\n", manager.get_len(&manager));
    manager.append(&manager, s4, INSERT_HEAD);
    manager.display(&manager);
    printf("长度%d\n", manager.get_len(&manager));
    manager.delt(&manager, s2);
    manager.display(&manager);
    printf("长度%d\n", manager.get_len(&manager));
    printf("上升排序:\n");
    manager.sort(&manager, SORT_UPPER);
    manager.display(&manager);
    printf("下降排序:\n");
    manager.sort(&manager, SORT_LOWER);
    manager.display(&manager);
exit:
    return 0;
}