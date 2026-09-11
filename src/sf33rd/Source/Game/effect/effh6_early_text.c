#include "sf33rd/Source/Game/effect/effh6_text.h"

s16 effh6_configure_early_text_path(WORK_Other_CONN* ewk, s16 X, s16 Y, s16 Original_Color) {
    switch (Original_Color) {
    case 0:
        ewk->wu.routine_no[1] = 0;
        ewk->wu.routine_no[5] = X;
        ewk->wu.xyz[0].disp.pos = 384;
        ewk->wu.xyz[1].disp.pos = Y;
        break;

    case 1:
        ewk->wu.routine_no[1] = 1;
        ewk->wu.routine_no[6] = Y;
        ewk->wu.xyz[0].disp.pos = X;
        ewk->wu.xyz[1].disp.pos = 0;
        break;

    case 2:
        Original_Color = 0;
        ewk->wu.routine_no[1] = 2;
        ewk->wu.routine_no[5] = X;
        ewk->wu.xyz[0].disp.pos = -64;
        ewk->wu.xyz[1].disp.pos = Y;
        break;

    case 3:
        ewk->wu.routine_no[1] = 3;
        ewk->wu.xyz[0].disp.pos = X;
        ewk->wu.xyz[1].disp.pos = Y;
        break;

    case 4:
        Original_Color = 1;
        ewk->wu.routine_no[1] = 4;
        ewk->wu.routine_no[6] = Y;
        ewk->wu.xyz[0].disp.pos = X;
        ewk->wu.xyz[1].disp.pos = 0;
        break;
    }

    return Original_Color;
}
