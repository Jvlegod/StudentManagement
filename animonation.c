#include "animonation.h"

char *jvleArt =
    "  JJJJJ  V           V   L        EEEEE\n"
    "    J      V         V    L        E\n"
    "    J       V       V     L        EEEE\n"
    "    J        V     V      L        E\n"
    "J   J         V   V       L        E\n"
    " JJJ           V V        LLLLL    EEEEE\n";

void show_Logo(uint8_t if_sleep, uint32_t sleep_time)
{
    printf("\033[2J");

    printf("\033[H");

    for (int i = 0; i < 39; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            printf("\033[1;%dm%c\033[0m", 31 + i, jvleArt[i * 6 + j]);
        }
        fflush(stdout);
        if (if_sleep == ANIMONATION_SLEEP)
        {
            usleep(sleep_time);
        }
    }

    printf("\033[0m");
    puts("");
}