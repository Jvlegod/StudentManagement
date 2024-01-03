#include <stdio.h>
#include "student.h"
#include "global.h"
#ifdef __linux__
#include <pthread.h>
#include "animonation.h"
extern char *jvleArt;
#define GOON_ANIMONATION 0
static uint8_t if_over_animonation = GOON_ANIMONATION;
#endif

extern StudentManger_t manager;
extern GUI_State state;
extern GUI_Stack_t gui_stack;
static int if_debug = 0;

#ifdef __linux__
static void *threadFunction(void *arg)
{
    fd_set fds;
    struct timeval timeout;

    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);

    timeout.tv_sec = 4;
    timeout.tv_usec = 0;

    int result = select(STDIN_FILENO + 1, &fds, NULL, NULL, &timeout);

    if (result == -1)
    {
        perror("select error");
        exit(1);
    }
    else if (result == 0)
    {
        return NULL;
    }
    else
    {
        if_over_animonation = getchar();
    }
    return NULL;
}
#endif

int main(int argc, char *argv[])
{

    // 初始化
    CLEAR;
    StudentManager_init(&manager, 100);
    set_wait();
    GUIStack_Init(&gui_stack);
#ifdef __linux__
    pthread_t tid;
    if (pthread_create(&tid, NULL, threadFunction, NULL) != 0)
    {
        fprintf(stderr, "Error creating thread.\n");
        return 1;
    }

    printf("\033[2J");

    printf("\033[H");

    for (int i = 0; i < 39; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            printf("\033[1;%dm%c\033[0m", 31 + i, jvleArt[i * 6 + j]);
        }
        fflush(stdout);
        if (if_over_animonation == GOON_ANIMONATION)
        {
            usleep(100000);
        }
    }

    printf("\033[0m");
    puts("");

    if (pthread_join(tid, NULL) != 0)
    {
        fprintf(stderr, "Error joining thread.\n");
        return 1;
    }
#endif

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

    // 测试
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
    set_nowait();
    return 0;
}