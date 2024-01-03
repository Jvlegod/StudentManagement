#include "global.h"

StudentManger_t manager;
GUI_Stack_t gui_stack;
GUI_State state = MAIN_INTERFACE;
#ifdef __linux__
extern struct termios oldt, newt;
#endif

struct termios oldt, newt;

void back_State()
{
    state = GUIStack_pop(&gui_stack);
}

void enter_State(GUI_State val)
{
    GUIStack_push(&gui_stack, state);
    state = val;
}

void GUIStack_Init(GUI_Stack_t *stack)
{
    for (int i = 0; i < STACK_MAXLEN; i++)
    {
        stack->data[i] = -1;
    }

    stack->top = -1;
}

bool GUIStack_push(GUI_Stack_t *stack, GUI_State val)
{
    if (GUIStack_iffull(stack))
    {
        return false;
    }

    stack->top++;
    stack->data[stack->top] = val;
    return true;
}

GUI_State GUIStack_pop(GUI_Stack_t *stack)
{
    if (GUIStack_ifempty(stack))
    {
        return -1;
    }
    GUI_State ret = stack->data[stack->top];
    stack->top--;
    return ret;
}

bool GUIStack_ifempty(GUI_Stack_t *stack)
{
    if (stack->top <= -1)
    {
        return true;
    }
    return false;
}

bool GUIStack_iffull(GUI_Stack_t *stack)
{
    if (stack->top >= STACK_MAXLEN)
    {
        return true;
    }
    return false;
}

void set_nowait()
{
#ifdef __linux__
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
}

void set_wait()
{
#ifdef __linux__
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
#endif
}