#include "sf33rd/Source/Game/effect/effh6_cycles.h"

void effh6_update_right_cycle(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[2]) {
    case 0:
        ewk->wu.dir_timer = ewk->wu.dir_timer - roll_rate_t;
        ewk->wu.xyz[0].disp.pos = ewk->wu.xyz[0].disp.pos + roll_rate;
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0xFFFF;

        if (ewk->wu.routine_no[5] <= ewk->wu.xyz[0].disp.pos) {
            ewk->wu.xyz[0].disp.pos = ewk->wu.routine_no[5];
            ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0xFFFF;
            ewk->wu.routine_no[2]++;
            ewk->wu.dir_timer = ewk->wu.dir_timer - 48;
        }

        break;

    case 1:
        ewk->wu.dir_timer = ewk->wu.dir_timer - roll_rate_t;

        if (ewk->wu.dir_timer < 1) {
            ewk->wu.routine_no[2]++;
        }

        break;

    case 2:
        ewk->wu.xyz[0].disp.pos = ewk->wu.xyz[0].disp.pos - roll_rate;
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0xFFFF;

        if (ewk->wu.xyz[0].disp.pos < -127) {
            ewk->wu.routine_no[0]++;
        }

        break;
    }
}
