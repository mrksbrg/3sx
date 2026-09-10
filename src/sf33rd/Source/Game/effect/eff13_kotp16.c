/**
 * @file eff13_kotp16.c
 * Accelerating projectile behavior for effect 13.
 */

#include "sf33rd/Source/Game/effect/eff13_kotp16.h"
#include "sf33rd/Source/Game/effect/eff13_internal.h"
#include "sf33rd/Source/Game/engine/charset.h"
#include "sf33rd/Source/Game/engine/pls02.h"
#include "sf33rd/Source/Game/engine/workuser.h"

static void accelerate_kotp_16(WORK_Other* ewk) {
    add_mvxy_speed(&ewk->wu);

    if (ewk->wu.rl_flag) {
        ewk->wu.xyz[0].cal += 0x38000;
    } else {
        ewk->wu.xyz[0].cal += -0x38000;
    }
}

static s32 prepare_kotp_16_motion(WORK_Other* ewk) {
    if (ewk->wu.hit_stop) {
        if (ewk->wu.hit_stop == 1) {
            ewk->wu.hit_stop = 0;
        } else {
            ewk->wu.hit_stop--;
            return 0;
        }
    } else {
        accelerate_kotp_16(ewk);
    }

    return 1;
}

void kotp_16000(WORK_Other* ewk, TAMA* twk) {
    enter_kotp_hit_phase(ewk);

    switch (ewk->wu.routine_no[1]) {
    case 0:
        if (!prepare_kotp_16_motion(ewk)) {
            break;
        }

        cal_mvxy_speed(&ewk->wu);
        char_move(&ewk->wu);

        if (ewk->wu.cg_type == 0xFF) {
            set_char_move_init(&ewk->wu, 0, twk->ernm);
            ewk->wu.routine_no[1] = 2;
            ewk->wu.routine_no[2] = 0;
            break;
        }

        if ((ewk->wu.xyz[1].disp.pos + ewk->wu.cg_jphos) <= 0) {
            enter_kotp_landing_phase(ewk, twk);
            break;
        }

        if (kotp_remains_on_screen(ewk)) {
            break;
        }

        set_char_move_init(&ewk->wu, 0, twk->ernm);
        ewk->wu.routine_no[1] = 2;
        ewk->wu.routine_no[2] = 0;
        break;

    case 1:
        resolve_kotp_12_hit(ewk, twk);
        break;

    case 2:
        finish_kotp_07(ewk);
        break;
    }
}
