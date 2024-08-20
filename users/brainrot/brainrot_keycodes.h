#pragma once
#include "charybdis.h"

// TODO keep in sync with keymapPostParse.ps1
enum layers {
    _BRAINROT = 0,
    _COMBOREF,
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
    _POINTEROPT,
    // 15 layer LT/LM threshold https://github.com/qmk/qmk_firmware/blob/master/docs/feature_layers.md#switching-and-toggling-layers-switching-and-toggling-layers
    _SECRET,
    _NAGINATA,
    _SHINGETA,
    _QWERTY,
    _RANDOM,
};

typedef enum {
    TD_NONE = 0,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool       is_press_action;
    td_state_t state;
} td_tap_t;

enum tap_dances {
    TD_BSPC = 0,
    TD_DEL,
    TD_A,
    TD_B,
    TD_C,
    TD_D,
    TD_E,
    TD_F,
    TD_G,
    TD_H,
    TD_I,
    TD_J,
    TD_K,
    TD_L,
    TD_M,
    TD_N,
    TD_O,
    TD_P,
    TD_QU,
    TD_R,
    TD_S,
    TD_T,
    TD_U,
    TD_V,
    TD_W,
    TD_X,
    TD_Y,
    TD_Z,

};
td_state_t cur_dance(tap_dance_state_t *state);

// For the tap dance. Put it here so it can be used in any keymap
void bspc_finished(tap_dance_state_t *state, void *user_data);
void bspc_reset(tap_dance_state_t *state, void *user_data);
void del_finished(tap_dance_state_t *state, void *user_data);
void del_reset(tap_dance_state_t *state, void *user_data);
void qu_finished(tap_dance_state_t *state, void *user_data);
void qu_reset(tap_dance_state_t *state, void *user_data);

// redo all keycodes and defines to be exacty 7 chars long. ie, KC_A to KC____A
enum keycodes {
    KC_TEST = SAFE_RANGE,

    // non modal digraphs
    KC_TH,
    KC_IN,
    KC_PH,
    KC_SH,
    KC_WH,
    KC_CH,

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
    MD_AND,  // and/&, "and "/" & "
    MD_THE,  // the/"the "
    MD_FOR,  // for/"for "
    MD_YOU,  // you/"you "
    MD_GH,   // gh/"gh "
    MD_LY,   // ly/"ly "
    MD_ING,  // ing/"ing "
    MD_SION, // sion/"sion "
    MD_TION, // tion/"tion "
    MD_OULD, // ould/"ould "
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
    COM_ARC,
    DOT_ARC,
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

    /* physical layout comboref keys
    legend = hand_row_column/thumb button
    L = Left hand
    R = Right hand

    T = Top row
    M = Middle row
    B = Bottom row

    Out = Outer column
    Pin = Pinky column
    Rin = Ring column
    Ind = Index column
    Inn = Inner column

    LThmb = Left Thumb button
    MThmb = Middle Thumb  button
    RThmb = Right Thumb button
    */
    L_T_Out,
    L_T_Pin,
    L_T_Rin,
    L_T_Mid,
    L_T_Ind,
    L_T_Inn,
    R_T_Out,
    R_T_Pin,
    R_T_Rin,
    R_T_Mid,
    R_T_Ind,
    R_T_Inn,
    L_H_Out,
    L_H_Pin,
    L_H_Rin,
    L_H_Mid,
    L_H_Ind,
    L_H_Inn,
    R_H_Out,
    R_H_Pin,
    R_H_Rin,
    R_H_Mid,
    R_H_Ind,
    R_H_Inn,
    L_B_Out,
    L_B_Pin,
    L_B_Rin,
    L_B_Mid,
    L_B_Ind,
    L_B_Inn,
    R_B_Out,
    R_B_Pin,
    R_B_Rin,
    R_B_Mid,
    R_B_Ind,
    R_B_Inn,
    L_LThmb,
    L_MThmb,
    L_RThmb,
    R_LThmb,
    R_MThmb,

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
// base layers
#define BASE TO(_BRAINROT)
#define QWERTY TO(_QWERTY)
#define GAME TO(_GAME)
#define THINQU TO(_THINQU)

// layer taps
#define LAYR_TB LT(_LAYER, KC_TAB)
#define LSHGR_R LT(_LSHIFTGR, KC_R)
#define RSHGR_T LT(_RSHIFTGR, KC_T)
// default LTs
#define PT_Z LT(_POINTER, KC_Z)
#define PT_SLSH LT(_POINTER, KC_SLSH)

// momentary layer holds
#define THINQUL MO(_THINQUL)
#define THINQUR MO(_THINQUR)
#define LAYER MO(_LAYER)
#define VIMNAV MO(_VIMMOTION)
#define VIMNUM MO(_VIMNUM)

// one shot layers
#define SHRTCUT OSL(_FUNCTION)
#define MEDIA OSL(_MEDIA)
#define PNTROPT OSL(_POINTEROPT)

#define KEYBRD TG(_KEYBOARD)
#define MATH TG(_MATH)
#define RANDOM TG(_RANDOM)

// TODO clean up these rejects from brainrot_layout.h
#define PT_K LT(_POINTER, KC_K)
#define PT_H LT(_POINTER, KC_H)
#define VIMNV_S LT(_VIMMOTION, KC_SPC)
#define PNT_T(k0) LT(_POINTER, k0)
#define _T(k0) LT(_LAYER, k0)
#define VIMNAV_T(k0) LT(_VIMMOTION, k0)
#define LSHGR_T(k0) LT(_LSHIFTGR, k0)

// TODO go through these and apply them
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
// #define TH_QU TH(KC_Q) // tap qu, hold q
#define TD_QU TH(TD_QU) // tap qu, double tap ctrl+q, hold q
#define F3_TH TH(KC_F3)
#define F5_TH TH(KC_F5)
#define F6_TH TH(KC_F6)
#define F11_TH TH(KC_F11)
#define F12_TH TH(KC_F12)

// charybdis formated
#define DPI_RMD DPI_RMOD
#define SD__MOD S_D_MOD
#define SD_RMOD S_D_RMOD

/* Japanese specific */
#define KC_ZKHK KC_GRAVE
#define KC_RO KC_INT1
#define KC_KANA KC_INT2
#define KC_JYEN KC_INT3
#define KC_JPY KC_INT3
#define KC_HENK KC_INT4
#define KC_MHEN KC_INT5
