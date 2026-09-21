/*
 * The branch menus more than one shared skeleton offers.
 *
 * A Branch_Menu_Args is one menu per area and the action they all branch to
 * (see com_sub.h). Six of them are written more than once across this folder -
 * one of them seven times, in six different files - and a menu written out
 * again is a menu that can drift. They are written once here instead.
 *
 * Each is named for the values it holds, in order, because that is all that is
 * known about them: the numbers are the arcade's and nothing in the port
 * explains what a menu means.
 */

#ifndef COM_BRANCH_MENUS_H
#define COM_BRANCH_MENUS_H

#include "sf33rd/Source/Game/com/com_sub.h"

extern const Branch_Menu_Args Branch_Menu_2_3_38_44_45;
extern const Branch_Menu_Args Branch_Menu_2_18_18_11_11;
extern const Branch_Menu_Args Branch_Menu_6_2D_FF_FF_FF;
extern const Branch_Menu_Args Branch_Menu_6_37_37_27_27;
extern const Branch_Menu_Args Branch_Menu_6_4B_36_3B_70;
extern const Branch_Menu_Args Branch_Menu_6_77_77_78_79;

#endif
