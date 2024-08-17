#pragma once
#include "charybdis.h"

enum keycodes {
    KC_TEST = SAFE_RANGE,
    // digraphs
    KC_TH,
    KC_IN,
    KC_QU,
    // split spaces
    KC_LSPC,
    KC_RSPC,
    // shortcuts
    SH_RMDT, // remote desktop window toggle
    SCN_TOG, // yomitan scan modifier
    /*
    semantic keys
    The keycode's behavior is based on the semantics or meaning of the current context. The keycode understands the environment (active window) and acts accordingly.
    */
    SM_COPY,
    SM_CUT,
    SM_PASTE,
    SM_SAVE,
    SM_SNAP,
    // modal keys
    MD_DTSC, // period/semicolon
    MD_AND,  // and/&
    MD_BSPC, // backspace/backspace word
    MD_DEL,  // delete/delete word
    MD_IME,  // romaji/kana
    MD_YES,  // confirmation key, usually enter
    MD_NO,   // rejection key, usually escape
    MD_RNPO, // round parenthesis open
    MD_RNPC, // round parenthesis close
    MD_SQPO, // square bracket pair open
    MD_SQPC, // square bracket pair close
    MD_CRPO, // curly braces open
    MD_CRPC, // curly braces close
    // arcane keys
    LT_ARC,
    RT_ARC,
    LB_ARC,
    RB_ARC,
    // secrets
    SECRET1,
    SECRET2,
    // vim
    VIM_TOG,
    VIM_G_,
    VIM_GG,
    // math
    KC_SQRT,
    // randumb
    KC_RAND,
};

/* Japanese specific */
#define KC_ZKHK KC_GRAVE
#define KC_RO KC_INT1
#define KC_KANA KC_INT2
#define KC_JYEN KC_INT3
#define KC_JPY KC_INT3
#define KC_HENK KC_INT4
#define KC_MHEN KC_INT5
