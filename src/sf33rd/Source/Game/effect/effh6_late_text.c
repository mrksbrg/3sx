#include "sf33rd/Source/Game/effect/effh6_text.h"

s16 effh6_configure_late_text_path(WORK_Other_CONN* ewk, s16 X, s16 Y, s16 Original_Color) {
    switch (Original_Color) {
    case 5:
        Original_Color = 1;
        ewk->wu.routine_no[1] = 5;
        ewk->wu.xyz[0].disp.pos = X;
        ewk->wu.xyz[1].disp.pos = Y;
        break;

    case 6:
        ewk->wu.routine_no[1] = 6;
        ewk->wu.routine_no[6] = Y;
        ewk->wu.xyz[0].disp.pos = X;
        ewk->wu.xyz[1].disp.pos = -32;
        break;

    case 7:
        ewk->wu.routine_no[1] = 7;
        ewk->wu.routine_no[6] = Y;
        ewk->wu.xyz[0].disp.pos = X;
        ewk->wu.xyz[1].disp.pos = 256;
        break;

    case 8:
        ewk->wu.routine_no[1] = 6;
        ewk->wu.routine_no[6] = Y;
        ewk->wu.xyz[0].disp.pos = X;
        ewk->wu.xyz[1].disp.pos = -32;
        break;

    case 9:
        ewk->wu.dir_step = 2;
        ewk->wu.routine_no[1] = 0;
        ewk->wu.routine_no[6] = Y;
        ewk->wu.xyz[0].disp.pos = X;
        ewk->wu.xyz[1].disp.pos = 0;
        ewk->wu.my_col_code = 0x202B;
        break;
    }

    return Original_Color;
}
