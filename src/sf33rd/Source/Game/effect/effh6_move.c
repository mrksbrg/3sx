#include "sf33rd/Source/Game/effect/effh6.h"
#include "sf33rd/Source/Game/effect/effh6_cycles.h"
#include "common.h"
#include "sf33rd/Source/Game/effect/effect.h"
#include "sf33rd/Source/Game/engine/workuser.h"
#include "sf33rd/Source/Game/rendering/aboutspr.h"
#include "sf33rd/Source/Game/screen/staff.h"

s16 roll_rate_t;
s16 roll_rate;

static void update_h6_scroll(WORK_Other* ewk) {
    switch (ewk->wu.dir_step) {
    default:
        ewk->wu.xyz[1].disp.pos = ewk->wu.xyz[1].disp.pos + roll_rate;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0xFFFF;

        if (256 <= ewk->wu.xyz[1].disp.pos) {
            ewk->wu.routine_no[0]++;
        }

        break;

    case 1:
        break;
    }

    if (Suicide[4]) {
        ewk->wu.routine_no[0] = 2;
    }

    sort_push_request4(&ewk->wu);
}

static void update_h6_wait(WORK_Other* ewk) {
    ewk->wu.dir_timer = ewk->wu.dir_timer - roll_rate_t;

    if (ewk->wu.dir_timer < 1) {
        ewk->wu.routine_no[0]++;
    }
}

static void update_h6_down_exit(WORK_Other* ewk) {
    ewk->wu.xyz[1].disp.pos = ewk->wu.xyz[1].disp.pos + roll_rate;
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0xFFFF;

    if (256 <= ewk->wu.xyz[1].disp.pos) {
        ewk->wu.routine_no[0]++;
    }
}

static void update_h6_up_exit(WORK_Other* ewk) {
    ewk->wu.xyz[1].disp.pos = ewk->wu.xyz[1].disp.pos - roll_rate;
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0xFFFF;

    if (0 < ewk->wu.xyz[1].disp.pos) {
        return;
    }

    ewk->wu.routine_no[0]++;
}

static void initialize_h6_move(WORK_Other* ewk) {
    ewk->wu.routine_no[0]++;
    ewk->wu.disp_flag = 1;
    roll_rate = 1;
    roll_rate_t = 1;

    if (!ewk->wu.dir_step) {
        ewk->wu.old_cgnum = ewk->wu.cg_number = 0;
        ewk->wu.cg_number++;
        ewk->wu.cg_number &= 0x7FFF;
    }

    ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0xFFFF;
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0xFFFF;
}

static void update_h6_direction(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        effh6_update_left_cycle(ewk);
        break;

    case 1:
        effh6_update_down_cycle(ewk, 30);
        break;

    case 2:
        effh6_update_right_cycle(ewk);
        break;

    case 3:
        update_h6_wait(ewk);
        break;

    case 4:
        effh6_update_down_cycle(ewk, 60);
        break;

    case 6:
        update_h6_down_exit(ewk);
        break;

    case 7:
        update_h6_up_exit(ewk);
        break;
    }
}

static void update_h6_active(WORK_Other* ewk) {
    if (ewk->wu.dir_step) {
        update_h6_scroll(ewk);
        return;
    }

    update_h6_direction(ewk);
    if (Suicide[4]) {
        ewk->wu.routine_no[0] = 2;
    }

    sort_push_request3(&ewk->wu);
}

void effect_H6_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case 0:
        initialize_h6_move(ewk);
        break;

    case 1:
        update_h6_active(ewk);
        break;

    case 2:
        ewk->wu.disp_flag = 0;
        ewk->wu.routine_no[0]++;
        break;

    case 3:
        ewk->wu.routine_no[0]++;
        break;

    default:
        push_effect_work(&ewk->wu);
        break;
    }
}
