#ifndef _ANIMONATION_H_
#define _ANIMONATION_H_
#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include "tools.h"
#define ANIMONATION_SLEEP 0
#define ANIMONATION_NOSLEEP 1

void show_Logo(uint8_t if_sleep, uint32_t sleep_time);

#endif // !_ANIMONATION_H_