#ifndef EFF79_H
#define EFF79_H

#include "structs.h"
#include "types.h"

// MARK: - Serialized

extern u8 OK_Appear79[2];
extern u8 Extra_Counter[2];

typedef struct {
    s16 player_id;
    s16 plate_id;
    s16 position_id;
    s16 delay;
    s16 target_background;
} Effect79InitArgs;

void effect_79_move(WORK_Other* ewk);
s32 effect_79_init(const Effect79InitArgs* args);

#endif
