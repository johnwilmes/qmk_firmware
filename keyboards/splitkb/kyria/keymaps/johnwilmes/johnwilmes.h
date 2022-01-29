#pragma once

#include "keyboard.h"

enum layers {
    _BASE    = 0,
    _FINGERS = COMBO_ONLY_FROM_LAYER,
    _LEFT_MOD,
    _RIGHT_MOD,
    _SYMBOLS,
    _BRACKETS,
    _NUMBERS,
    _HEX,
    _NAVIGATION,
    _SYSTEM1,
    _SYSTEM2,
    _SYSTEM3,
    _SYSTEM4,
    _MOUSE,
};

enum my_keycodes {
    FINGERS_START = SAFE_RANGE,
#define FINGERS_MACRO(...) __VA_ARGS__,
#include "fingers.def"
#undef FINGERS_MACRO
    FINGERS_END,

    APP_PREV,
    APP_NEXT,
    WIN_PREV,
    WIN_NEXT,

    BIGRAM_QU,
    LAYER_LOCK,
};

/* ADDITIONAL KEYS */

//#define MY_SPACE LT(_LEFT_MOD, KC_SPACE)
#define MY_SPACE KC_SPACE
//#define MY_DOT LT(_RIGHT_MOD, KC_DOT)
#define MY_DOT KC_DOT

#define MY_DASH KC_MINUS
#define MY_LINE KC_UNDERSCORE
#define MY_QUOTE KC_DOUBLE_QUOTE
#define MY_PLUS KC_PLUS
#define MY_EQUAL KC_EQUAL
#define MY_NOT KC_EXCLAIM
#define MY_ANGLE KC_LEFT_ANGLE_BRACKET
#define MY_GRAVE KC_GRAVE
#define MY_HASH KC_HASH
#define MY_REGEX KC_DOLLAR
#define MY_BOOL KC_AMPERSAND
#define MY_QUESTION KC_QUESTION

#define L_LEADER KC_F17
#define R_LEADER KC_F18
#define MY_MAGIC KC_F19

#define SYS_MOD(kc) C(A(kc))

#define LOCK_SCREEN SYS_MOD(KC_ESCAPE)
#define SYS_CLOSE SYS_MOD(KC_Q)
#define C_A_DEL C(A(KC_DELETE))

#define NOTIFICATIONS SYS_MOD(KC_N)
#define MESSAGES SYS_MOD(KC_DOT)
#define OVERVIEW_UP SYS_MOD(KC_PAGE_UP)
#define OVERVIEW_DOWN SYS_MOD(KC_PAGE_DOWN)
#define MAXIMIZE SYS_MOD(KC_M)
#define FULLSCREEN SYS_MOD(KC_F)

#define SYS_RUN SYS_MOD(KC_R)
#define TERMINAL SYS_MOD(KC_T)
#define BROWSER KC_WWW_HOME
#define PASSWORDS SYS_MOD(KC_P)

#define TAB_PREV C(KC_PAGE_UP)
#define TAB_NEXT C(KC_PAGE_DOWN)
#define TAB_MOVE_PREV S(TAB_PREV)
#define TAB_MOVE_NEXT S(TAB_NEXT)

#define WORKSPACE_PREV SYS_MOD(KC_UP)
#define WORKSPACE_NEXT SYS_MOD(KC_DOWN)
#define WS_MOVE_PREV S(WORKSPACE_PREV)
#define WS_MOVE_NEXT S(WORKSPACE_NEXT)
#define MON_MOVE_PREV S(SYS_MOD(KC_LEFT))
#define MON_MOVE_NEXT S(SYS_MOD(KC_RIGHT))

#define MEDIA_PREV KC_MEDIA_PREV_TRACK
#define MEDIA_NEXT KC_MEDIA_NEXT_TRACK
#define MEDIA_PLAY KC_MEDIA_PLAY_PAUSE
#define VOL_DOWN KC_AUDIO_VOL_DOWN
#define VOL_UP KC_AUDIO_VOL_UP
#define VOL_MUTE KC_AUDIO_MUTE
#define PRINT_SELECT S(KC_PRINT_SCREEN)
#define PRINT_WINDOW A(KC_PRINT_SCREEN)
#define PRINT_SCREEN KC_PRINT_SCREEN
#define SAVE_SELECT C(S(KC_PRINT_SCREEN))
#define SAVE_WINDOW C(A(KC_PRINT_SCREEN))
#define SAVE_SCREEN C(KC_PRINT_SCREEN)

#define MO_SYM MO(_SYMBOLS)
#define MO_BRKT MO(_BRACKETS)
#define MO_NUM MO(_NUMBERS)
#define MO_HEX MO(_HEX)
#define MO_NAV MO(_NAVIGATION)
#define MO_SYS1 MO(_SYSTEM1)
#define MO_SYS2 MO(_SYSTEM2)
#define MO_SYS3 MO(_SYSTEM3)
#define MO_SYS4 MO(_SYSTEM4)
#define MO_MOUSE MO(_MOUSE)

#define MY_RALT KC_LALT
#define OS_LSFT OSM(MOD_LSFT)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_LALT OSM(MOD_LALT)
#define OS_LGUI OSM(MOD_LGUI)
