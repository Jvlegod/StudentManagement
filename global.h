#ifndef __GLOBAL_H__
#define __GLOBAL_H__
#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#ifdef __linux__
#include <unistd.h>
#include <termios.h>
#endif

#ifdef _WIN32
#define CLEAR system("cls")
#elif __linux__
#define CLEAR system("clear")
#else
#endif

#define STACK_MAXLEN 255

typedef enum _GUI_State
{
    MAIN_INTERFACE,
    INFORMATION_INTERFACE,
    ADD_INTERFACE,
    DELTE_INTERFACE,
    MODIFY_INTERFACE,
    SORT_INTERFACE,
    EXIT_INTERFACE
} GUI_State;

typedef struct _GUI_Stack
{
    GUI_State data[STACK_MAXLEN];
    int top;
} GUI_Stack_t;

void GUIStack_Init(GUI_Stack_t *stack);
bool GUIStack_push(GUI_Stack_t *stack, GUI_State val);
GUI_State GUIStack_pop(GUI_Stack_t *stack);
bool GUIStack_ifempty(GUI_Stack_t *stack);
bool GUIStack_iffull(GUI_Stack_t *stack);
void enter_State(GUI_State val);
void back_State();
void set_nowait();
void set_wait();

#endif // !__GLOBAL_H__