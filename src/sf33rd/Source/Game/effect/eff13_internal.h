#ifndef EFF13_INTERNAL_H
#define EFF13_INTERNAL_H

#include "structs.h"

void enter_kotp_hit_phase(WORK_Other* ewk);
void enter_kotp_landing_phase(WORK_Other* ewk, TAMA* twk);
void finish_kotp_07(WORK_Other* ewk);
s32 kotp_remains_on_screen(WORK_Other* ewk);
void resolve_kotp_12_hit(WORK_Other* ewk, TAMA* twk);

#endif
