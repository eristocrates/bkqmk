#pragma once
#include "charybdis.h"

enum layers {
    _BRAINROT = 0,
    _LSHIFTGR,
    _RSHIFTGR,
    _MATH,
    _VIMMOTION,
    _VIMNUM,
    _FUNCTION,
    _MEDIA,
    _LAYER,
    _GAME,
    _THINQU,
    _THINQUL,
    _THINQUR,
    _KEYBOARD,
    _POINTER,
    _SECRET,
    // 15 layer LT/LM threshold https://github.com/qmk/qmk_firmware/blob/master/docs/feature_layers.md#switching-and-toggling-layers-switching-and-toggling-layers
    _NAGINATA,
    _SHINGETA,
    _QWERTY,
    _RANDOM,
};

enum keycodes {
    KC_TEST = SAFE_RANGE,

    // digraphs
    KC_TH,
    KC_IN,
    TH_QU,
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

    // adapted from possumvibes
    // OS-specific utilities
    IS_WIN, // TODO find of the non window OS possum was using was mac or linux
    // TODO look into auto os detection, or possibly raw hid os reporting
    LOCKSCR,
    ALT_F4,
    DMENU,

    // Layer modes and how to escape them
    VIMMOTIONMODE,
    POINTERMODE,
    LSHIFTGRMODE,
    RSHIFTGRMODE,
    MATHMODE,
    FUNMODE,
    NAVMODE,
    SYMMODE,
    MCRMODE,
    PANIC,

    // "Paired" macros: Undo/Redo, Comment/Uncomment, QMK Compile/Flash
    UND_RED,
    COMMENT,
    UNCOMNT,

    // Custom markup and programming syntax
    ANGLEBR,
    BRCKETS, // self-closing brackets: <|>, [|]  {|}
    MD_LINK,
    MD_CODE, // Markdown: [links|]() and ```codeblocks|  ```
    GET_SET, // { get; set; }
    RPR_SCL, // ); ();
    LMBD_FN, // () =>

    // Quick "not typing all that" strings
    KY_QU,
    KY_V1,
    KY_V2,
    KY_V3,

    // Vim macros: exactly what it says on the tin (words shiftable to Words)
    VI_ZZ,
    VI_ZQ,
    VI_YAW,
    VI_YIW,
    VI_YA,
    VI_YI,
    VI_AW,
    VI_IW,
    // TODO collect as many vim motions as possible!

    // Swapper keys: Windows, tabs, and generic Reverse
    SW_WIN,
    SW_TAB,
    SW_REV,

    // Locking Mods and how to escape them
    ML_LCTL,
    ML_LSFT,
    ML_LALT,
    ML_LGUI,
    CLEAR,

    // N-Shot Mods: "normal" callum-style n-shot mods (now featuring MULTI MODS!!!)
    OS_LSFT,
    OS_LCTL,
    OS_LALT,
    OS_LGUI,
    OS_LGLC,
    TS_LCTL,
    OSR_SFT, // and also n-shot Thumbshift (see n-shot mods for rolling differences)

    // NEW_SAFE_RANGE // Use for keymap-specific codes
};
/* ---------- Aliases ---------- */
#define BASE TO(_BRAINROT)
#define QWERTY TO(_QWERTY)
#define GAME TO(_GAME)
#define THINQU TO(_THINQU)
#define THINQUL MO(_THINQUL)
#define THINQUR MO(_THINQUR)

#define LAYER MO(_LAYER)
#define SHRTCUT OSL(_FUNCTION)
#define KEYBRD TG(_KEYBOARD)
#define MEDIA OSL(_MEDIA)
#define MATH TG(_MATH)
#define RANDOM TG(_RANDOM)
#define VIMNAV MO(_VIMMOTION)
#define VIMNUM MO(_VIMNUM)

#define TH_2 LT(_BRAINROT, KC_2)
// oneshot layers
#define MAT_OSL OSL(_MATH)
#define SHC_OSL OSL(_FUNCTION)

// mouse button aliases for ease of use
#define LCLICK KC_BTN1
#define RCLICK KC_BTN2
#define MCLICK KC_BTN3

// window manager shortcuts
#define LSTDESK G(KC_TILD)
#define LSTNODE G(KC_GRV)
#define GC_LEFT G(C(KC_LEFT))
#define GC_RGHT G(C(KC_RGHT))

#define TMUXPRE C(KC_SPC)

// Shortcuts
#define S_CUT S(KC_DEL)
#define S_COPY C(KC_INS)
#define S_PASTE S(KC_INS)
#define S_SAVE C(KC_S)
#define S_BACK A(KC_LEFT)
#define S_FWD A(KC_RIGHT)

// Macros
#define TH(k) LT(_BRAINROT, k)
#define TH_QU TH(KC_Q) // tap qu, hold q
#define F3_TH TH(KC_F3)
#define F5_TH TH(KC_F5)
#define F6_TH TH(KC_F6)
#define F11_TH TH(KC_F11)
#define F12_TH TH(KC_F12)

/* Japanese specific */
#define KC_ZKHK KC_GRAVE
#define KC_RO KC_INT1
#define KC_KANA KC_INT2
#define KC_JYEN KC_INT3
#define KC_JPY KC_INT3
#define KC_HENK KC_INT4
#define KC_MHEN KC_INT5
