#include "global.h"

StudentManger_t manager;

GUI_State state = MAIN_INTERFACE;
GUI_State old_state = MAIN_INTERFACE;

void set_State(GUI_State val)
{
    old_state = state;
    state = val;
}
