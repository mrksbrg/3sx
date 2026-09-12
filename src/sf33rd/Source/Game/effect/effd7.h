#ifndef EFFD7_H
#define EFFD7_H

#include "structs.h"
#include "types.h"

typedef struct {
    s16 duration;
    s16 target_x;
    s16 target_y;
    s16 vertical_speed;
} BallTrajectoryD7;

void effect_D7_move(WORK_Other* ewk);
void cal_speeds_effD7(WORK_Other* ewk, const BallTrajectoryD7* trajectory);
void ball_init_position_effD7(WORK_Other* ewk, PLW* mwk);
u8 screen_range_check_effD7(WORK* wk);
s32 effect_D7_init(PLW* wk);

#endif
