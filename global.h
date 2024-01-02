#ifndef __GLOBAL_H__
#define __GLOBAL_H__
#include <stdlib.h>
#include "student.h"

#ifdef _WIN32
#define CLEAR system("cls")
#elif __linux__
#define CLEAR system("clear")
#else
#endif

typedef enum _GUI_State
{
    MAIN_INTERFACE,
    INFORMATION_INTERFACE,
    ADD_INTERFACE,
    DELTE_INTERFACE,
    MODIFY_INTERFACE,
    EXIT_INTERFACE
} GUI_State;

void set_State(GUI_State val);

#endif // !__GLOBAL_H__