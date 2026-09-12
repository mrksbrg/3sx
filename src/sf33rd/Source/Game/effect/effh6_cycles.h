#ifndef EFFH6_CYCLES_H
#define EFFH6_CYCLES_H

#include "structs.h"
#include "types.h"

extern s16 roll_rate_t;
extern s16 roll_rate;

void effh6_update_left_cycle(WORK_Other* ewk);
void effh6_update_down_cycle(WORK_Other* ewk, s16 delay);
void effh6_update_right_cycle(WORK_Other* ewk);

#endif
