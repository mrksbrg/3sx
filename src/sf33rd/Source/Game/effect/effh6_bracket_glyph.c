#include "sf33rd/Source/Game/effect/effh6_text.h"

s16 effh6_select_bracket_character(s8 character, s16 chr) {
    if (character == '{') {
        chr = 0x7951;
    }

    if (character == '[') {
        chr = 0x7941;
    }

    if (character == ']') {
        chr = 0x793E;
    }

    if (character == '^') {
        chr = 0x7945;
    }

    if (character == '}') {
        chr = 0x7946;
    }

    if (character == '=') {
        chr = 0x7932;
    }

    if (character == '&') {
        chr = 0x7938;
    }

    return chr;
}
