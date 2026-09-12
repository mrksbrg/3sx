#include "sf33rd/Source/Game/effect/effh6_cycles.h"

void effh6_update_down_cycle(WORK_Other* ewk, s16 delay) {
    switch (ewk->wu.routine_no[2]) {
    case 0:
        ewk->wu.dir_timer = ewk->wu.dir_timer - roll_rate_t;
        ewk->wu.xyz[1].disp.pos = ewk->wu.xyz[1].disp.pos + roll_rate;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0xFFFF;

        if (ewk->wu.routine_no[6] <= ewk->wu.xyz[1].disp.pos) {
            ewk->wu.xyz[1].disp.pos = ewk->wu.routine_no[6];
            ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0xFFFF;
            ewk->wu.routine_no[2]++;
            ewk->wu.dir_timer = ewk->wu.dir_timer - delay;
        }

        break;

    case 1:
        ewk->wu.dir_timer = ewk->wu.dir_timer - roll_rate_t;

        if (ewk->wu.dir_timer < 1) {
            ewk->wu.routine_no[2]++;
        }

        break;

    case 2:
        ewk->wu.xyz[1].disp.pos = ewk->wu.xyz[1].disp.pos + roll_rate;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0xFFFF;
        if (256 <= ewk->wu.xyz[1].disp.pos) {
            ewk->wu.routine_no[0]++;
        }

        break;
    }
}
