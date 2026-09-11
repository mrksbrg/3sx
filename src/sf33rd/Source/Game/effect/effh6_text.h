#ifndef EFFH6_TEXT_H
#define EFFH6_TEXT_H

#include "structs.h"
#include "types.h"

s16 effh6_configure_early_text_path(WORK_Other_CONN* ewk, s16 X, s16 Y, s16 Original_Color);
s16 effh6_configure_late_text_path(WORK_Other_CONN* ewk, s16 X, s16 Y, s16 Original_Color);
s16 effh6_select_bracket_character(s8 character, s16 chr);
s16 effh6_select_punctuation_character(s8 character, s16 chr);

#endif
