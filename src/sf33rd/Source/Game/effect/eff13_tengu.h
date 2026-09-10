#ifndef EFF13_TENGU_H
#define EFF13_TENGU_H

#include "structs.h"
#include "types.h"

void set_tengu_init_pos(WORK* ewk, WORK* mwk);
void set_tengu_my_home(WORK* ewk, WORK* mwk);
s32 check_tengu_attack(WORK* ewk, WORK* mwk, TAMA* twk);
void make_speed_xy_att(WORK* ewk, WORK* mwk, u8 xsw, u8 ysw);
void make_speed_xy_back(WORK* ewk, WORK* mwk, TAMA* twk);
void kotp_02000(WORK_Other* ewk, TAMA* twk);

#endif
