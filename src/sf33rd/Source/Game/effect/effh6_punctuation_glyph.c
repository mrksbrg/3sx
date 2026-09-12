#include "sf33rd/Source/Game/effect/effh6_text.h"

s16 effh6_select_punctuation_character(s8 character, s16 chr) {
    if (character == '-') {
        chr = 0x7931;
    }

    if (character == '\"') {
        chr = 0x792B;
    }

    if (character == '%') {
        chr = 0x793A;
    }

    if (character == '|') {
        chr = 0x7947;
    }

    if (character == '(') {
        chr = 0x7934;
    }

    if (character == ')') {
        chr = 0x7935;
    }

    if (character == '*') {
        chr = 0x7940;
    }

    return chr;
}
