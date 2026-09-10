#ifndef EFF13_INTERNAL_H
#define EFF13_INTERNAL_H

#include "structs.h"

void set_kotp_hit_move(WORK_Other* ewk, TAMA* twk);
void enter_kotp_destroyed_phase(WORK_Other* ewk);
void apply_kotp_reflection(WORK_Other* ewk);
void enter_kotp_hit_phase(WORK_Other* ewk);
void enter_kotp_landing_phase(WORK_Other* ewk, TAMA* twk);
void enter_kotp_exit_phase(WORK_Other* ewk, TAMA* twk);
void advance_kotp_motion(WORK_Other* ewk);
void finish_kotp_07(WORK_Other* ewk);
s32 prepare_kotp_exp_motion(WORK_Other* ewk);
s32 kotp_remains_on_screen(WORK_Other* ewk);
void resolve_kotp_reflected_hit(WORK_Other* ewk, TAMA* twk, s16 destroyed_threshold);
void resolve_kotp_12_hit(WORK_Other* ewk, TAMA* twk);

#endif
