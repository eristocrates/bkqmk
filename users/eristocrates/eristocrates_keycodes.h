#pragma once
#include "charybdis.h"

// TODO keep in sync with keymapPostParse.ps1, bitwise_num, and rgb_matrix_stuff.h
// TODO ALWAYS KEEP _POINTER IN SYNC WITH RGB_MATRIX_STUFF
// TODO ALWAYS KEEP _NUMPAD IN SYNC WITH bitwise_num
enum layers {
    _CISTERN,
    _TYPINGAME,
    _COMBOREF,
    _SLICE,
    _BSLICE,
    _VIMFIGHTER,
    _SHIFTISHL,
    _SHIFTISHR,
    _ALTISHL,
    _ALTISHR,
    _ALTISHB,
    _BITNUM,
    _BITFUNC,
    _NUMPAD,
    _POINTER,
    _POINTEROPT,
    _MEDIA,
    _ONESHOT,
    _GAME,
    _THINQU,
    _THINQUL,
    _THINQUR,
    _KEYBOARD,
    _SECRET,
    _NAGINATA,
    _SHINGETA,
    _QWERTY,
    _RANDOM,
};

typedef enum {
    VIM,
    ARROW,
    NAV,
    BIN,
    SLICE_END,
} slice_state_t;

typedef enum {
    TD_NONE,
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
    TBW,
    TDW,

};
td_state_t cur_dance(tap_dance_state_t *state);

// For the tap dance. Put it here so it can be used in any keymap
void bspc_finished(tap_dance_state_t *state, void *user_data);
void bspc_reset(tap_dance_state_t *state, void *user_data);
void del_finished(tap_dance_state_t *state, void *user_data);
void del_reset(tap_dance_state_t *state, void *user_data);
void qu_finished(tap_dance_state_t *state, void *user_data);
void qu_reset(tap_dance_state_t *state, void *user_data);

// redo all keycodes and defines to be exacty 7 chars long. ie, KC_A to KC__T_A
enum keycodes {
    KC_TEST = SAFE_RANGE,

    // non modal digraphs
    KC_TH,
    KC_IN,
    KC_PH,
    KC_SH,
    KC_WH,
    KC_CH,

    KC_JTIL, // Japanese tilde

    // split spaces
    KC_LSPC,
    KC_RSPC,
    KC_LTAB,
    KC_RTAB,
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
    // modal combo/keys. most of these are subject to smart space
    MD_A,    // A
    MD_I,    // I
    MD_PS,   // 's
    MD_PLL,  // 'll
    MD_PVE,  // 've
    MD_PT,   // 't
    MD_PD,   // 'd
    MD_PM,   // 'm
    MD_PALL, // 'all
    MD_SCLN, // ;\n

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
    LTP_ARC,
    RTP_ARC,
    LHM_ARC,
    RHM_ARC,
    LBM_ARC,
    RBM_ARC,
    COM_ARC,
    DOT_ARC,
    // other magic
    // secrets
    SECRET1,
    SECRET2,
    SECRETR,
    SECRETC,
    SECRETT,
    SECRETL,
    SECRETG,
    // vim
    VIM_TOG,
    VIM_G_,
    VIM_GG,
    // math
    KC_SQRT,
    // randumb
    KC_RAND,
    FANCY_KEY,
    UCHAPPY,
    KC_QUOP,
    SKP_GRM, // skipgram key

    KC_DBCL, // mouse double click
    KC_MLTI, // mouse multi click
    RGB_MDE,
    CS__STP,
    CS_RSTP,
    KC_P00,
    // bitwise entry
    BIN___1,
    BIN___2,
    BIN___4,
    BIN___8,
    BIN__16,
    BIN__32,
    BIN__64,
    BIN_128,
    BIN_256,
    BIN_512,

    // TODO KEEP IN SYNC WITH ACTIONS MACRO
    // vim actions
    VM_LEFT,
    VM_DOWN,
    VM___UP,
    VM_RGHT,
    VM_NTRL,
    VM_HORI,
    VM_VERT,
    // vim operators
    VM_CHAN, // change
    VM_DELE, // delete
    VM_YANK, // yank
    VM_VISU, // visual
    VM_MRKQ, // ' mark jumps
    VM_MRKG, // ` mark jumps
    VM_FRMT, // formatting
    VM_FOLD, // folds
    VM_SRCH, // search

    // motion inputs
    MI_DOWN, // down
    MI_BACK, // left
    MI_FRNT, // right
    MI_JUMP, // up

    // fancy punctuation
    KC_ESLH, // \\/
    KC_DSLH, // //
    KC_DBSL,
    KC_DPIP, // ||
    KC_SARW, // ->
    KC_DARW, // =>
    KC_TGRV, // ```
    KC_DAMP, // &&
    KC_NEQL, // !=
    KC_DEQL, // ==
    KCNDEQL, // !==
    KC_TEQL, // ===
    KCNTEQL, // !===

    KC_LEQL, // <=
    KCDLEQL, // <==
    KC_GEQL, // >=
    KCDGEQL, // >==
    KC_CEQL, // :=
    KC_DCLN, // ::
    KC_DPLS, // ++
    KC_DMNS, // --
    KC_LCCM, // /*
    KC_RCCM, // \*/
    KC_LGCM, // {{/*
    KC_RGCM, // \*/}}
    KCDLABK, // <<
    KCDRABK, // >>
    KC_RTAG, // />
    KC_DTCM, // .com
    KC_DTGV, // .gov
    KC_GMIL, // gmail
    RGX_NCG, // non capturing group (?:)
    RGX_PLA, // positive look ahead  (?=)
    RGX_NLA, // negative look ahead (?!)
    RGX_PLB, // positive look behind (?<=)
    RGX_NLB, // negative look behind (?<!)
    KC_ELIP, // ...
    CASE_TERM,

    NG_ATE,
    NG_ANCE,
    NG_BL,
    NG_BY,
    NG_COM,
    NG_CON,
    NG_DON,
    NG_DAY,
    NG_ERS,
    NG_FRO,
    NG_FUL,
    NG_GER,
    NG_GRE,
    NG_HER,
    NG_HEA,
    NG_IN,
    NG_ING,
    NG_JOY,
    NG_JECT,
    NG_KNO,
    NG_CK,
    NG_LIN,
    NG_LEA,
    NG_MAN,
    NG_MEN,
    NG_NTI,
    NG_NTE,
    NG_OME,
    NG_ONE,
    NG_PRO,
    NG_PLA,
    NG_QUA,
    NG_QUE,
    NG_RAT,
    NG_STR,
    NG_STI,
    NG_TER,
    NG_TED,
    NG_UST,
    NG_ULD,
    NG_VES,
    NG_VEN,
    NG_WAY,
    NG_WAS,
    NG_XPL,
    NG_XPE,
    NG_YTH,
    NG_YEA,
    NG_ZED,
    KC___WH,

    // slices
    SL_INDX,
    SL_MDLE,
    SL_RING,
    SL_PNKY,
    SL_STEP,
    SL_RSTP,

    /* physical layout comboref keys
    legend = hand_row_column/thumb button
    L = Left hand
    R = Right hand

    T = Top row
    M = Middle row
    B = Bottom row

    OUTR = Outer column
    PNKY = Pinky column
    RING = Ring column
    INDX = Index column
    INNR = Inner column

    LTHMB = Left Thumb button
    MTHMB = Middle Thumb  button
    RTHMB = Right Thumb button
    */
    LT_OUTR,
    LT_PNKY,
    LT_RING,
    LT_MDLE,
    LT_INDX,
    LT_INNR,
    RT_OUTR,
    RT_PNKY,
    RT_RING,
    RT_MDLE,
    RT_INDX,
    RT_INNR,
    LH_OUTR,
    LH_PNKY,
    LH_RING,
    LH_MDLE,
    LH_INDX,
    LH_INNR,
    RH_OUTR,
    RH_PNKY,
    RH_RING,
    RH_MDLE,
    RH_INDX,
    RH_INNR,
    LB_OUTR,
    LB_PNKY,
    LB_RING,
    LB_MDLE,
    LB_INDX,
    LB_INNR,
    RB_OUTR,
    RB_PNKY,
    RB_RING,
    RB_MDLE,
    RB_INDX,
    RB_INNR,
    L_LTHMB,
    L_MTHMB,
    L_RTHMB,
    R_LTHMB,
    R_MTHMB,

    // adapted frm callum
    // Custom oneshot mod implementation with no timers.
    OS_SHFT,
    OS_CTRL,
    OS__ALT,
    OS__GUI,

    SW_WIN, // Switch to next window         (cmd-tab)
    LR_LOCK,

    // https://getreuer.info/posts/keyboards/macros/index.html
    SRCHSEL,
    UP__DIR,
    CUR_DIR,
    HOM_DIR, // ~/

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
    SHIFTGRMODE,
    CTLGRMODE,
    MATHMODE,
    FUNMODE,
    NAVMODE,
    SYMMODE,
    MCRMODE,
    K_CLEAR,
    PANIC,
    BITWISE,
    NUMPAD,

    EXP_AND,

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
    KYTQU,
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
    // SW_WIN,
    SW_TAB,
    SW_REV,

    // Locking Mods and how to escape them
    ML_LCTL,
    ML_LSFT,
    ML_LALT,
    ML_LGUI,

    // N-Shot Mods: "normal" callum-style n-shot mods (now featuring MULTI MODS!!!)
    OS_LSFT,
    OS_LCTL,
    OS_LALT,
    OS_LGUI,
    OS_LGLC,
    TS_LCTL,
    OSR_SFT, // and also n-shot Thumbshift (see n-shot mods for rolling differences)
    OS__MEH,
    OS_HYPR,
    OS__CAG,

    YT__ADD, // yomitan add
    YT_VIEW, // yomitan view
    YT_PLAY, // yomitan play

    NEW_SAFE_RANGE, // Use for keymap-specific codes
};
/* ---------- Aliases ---------- */
#define KC_DGSC LT(_POINTER, KC_1)
#define KC_SNPE LT(_POINTER, KC_2)

#define PLS_FUN LT(_BITFUNC, KC_PPLS)

// home row mods
#define LWKEY_C LGUI_T(KC_C)
#define LTALT_S LALT_T(KC_S)
#define LCTRL_T LCTL_T(KC_T)
#define LSHFT_N LSFT_T(KC_N)
#define LHYPR_D HYPR_T(KC_D)
#define LMEH__F MEH_T(KC_F)
#define LCAG__Y LCAG_T(KC_Y)
#define RSHFT_U RSFT_T(KC_U)
#define RCTRL_A RCTL_T(KC_A)
#define RTALT_I RALT_T(KC_I)
#define RWKEY_H RGUI_T(KC_H)
#define RHYPR_O HYPR_T(KC_O)
#define RMEH_DT MEH_T(KC_DOT)
#define RCAG__L RCAG_T(KC_L)

#// vim fighter
#define VF___UP VM___UP
#define VF_LEFT VM_LEFT
#define VF_DOWN VM_DOWN
#define VF_RGHT VM_RGHT
#define VF_NTRL VM_NTRL

// unicode
#define UC__SPC UC(0x2800)
// macros

#define OSMLGUI OSM(MOD_LGUI)
#define OSMRGUI OSM(MOD_RGUI)
#define OSMLSFT OSM(MOD_LSFT)
#define OSMRSFT OSM(MOD_RSFT)
#define OSMLCTL OSM(MOD_LCTL)
#define OSMRCTL OSM(MOD_RCTL)
#define OSMLALT OSM(MOD_LALT)
#define OSMRALT OSM(MOD_RALT)
#define OSMMEH OSM(MOD_MEH)
#define OSMHYPR OSM(MOD_HYPR)

#define TH(k) LT(0, k)
#define SG(k) LT(_SHIFTPR, k)
#define CG(k) LT(_SHIFTISHL, k)
#define AG(k) LT(_SHIFTISHR, k)
#define GG(k) LT(_ALTISHB, k)

// base layers
#define BASE TO(0)
#define QWERTY TO(_QWERTY)
#define GAME TO(_GAME)
#define TYPING TO(_TYPINGAME)
#define THINQU TO(_THINQU)

// layer taps
#define SFSHL_R LT(_SHIFTISHL, KC_R)
#define SFSHLCR LT(_SHIFTISHL, S(KC_R))
#define ALT___T LT(_SHIFTISHR, KC_T)
#define CTRL__S LT(_SHIFTISHL, KC_S)
#define SFSHR_E LT(_SHIFTISHR, KC_E)
#define SFSHRCE LT(_SHIFTISHR, S(KC_E))
#define ALTLSPC LT(_ALTISHL, KC_SPC)
#define ALTRSPC LT(_ALTISHR, KC_SPC)
#define NUM_PAD LT(_NUMPAD, SW_WIN)
#define NUM_SPC LT(_NUMPAD, KC_SPC)
#define BITWISEZ LT(_BITNUM, KC_Z)
#define BSESLCE LT(_BSLICE, KC_SPC)
//  default LTs
#define PT_Z LT(_POINTER, KC_Z)
#define PT_SLSH LT(_POINTER, KC_SLSH)

// momentary layer holds
#define THINQUL MO(_THINQUL)
#define THINQUR MO(_THINQUR)
#define VIMNAV MO(_SLICE)
#define MO_NUMP MO(_NUMPAD)

// one shot layers
#define SHRTCUT OSL(_BITNUM)
#define MEDIA OSL(_MEDIA)
#define PNTROPT OSL(_POINTEROPT)
#define PNTRNAV OSL(_POINTERNAV)
#define OSLBASE OSL(0)

// toggle layers
#define VIMFGHT TG(_VIMFIGHTER)
#define KEYBRD TG(_KEYBOARD)
#define MATH TG(_NUMPAD)
#define RANDOM TG(_RANDOM)

// TODO clean up these rejects from eristocrates_layout.h
#define PT_K LT(_POINTER, KC_K)
#define PT_H LT(_POINTER, KC_H)
#define VIMNV_S LT(_SLICE, KC_SPC)
#define PNT_T(k0) LT(_POINTER, k0)
#define _T(k0) LT(_ONESHOT, k0)
#define VIMNAV_T(k0) LT(_SLICE, k0)

// TODO go through these and apply them
// oneshot layers
#define MAT_OSL OSL(_NUMPAD)
#define SHC_OSL OSL(_BITNUM)

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

// standardized width keycodes
#define KC___UP KC_UP
#define KC____A KC_A
#define KC____B KC_B
#define KC____C KC_C
#define KC____D KC_D
#define KC____E KC_E
#define KC____F KC_F
#define KC____G KC_G
#define KC____H KC_H
#define KC____I KC_I
#define KC____J KC_J
#define KC____K KC_K
#define KC____L KC_L
#define KC____M KC_M
#define KC____N KC_N
#define KC____O KC_O
#define KC____P KC_P
#define KC____Q KC_Q
#define KC____R KC_R
#define KC____S KC_S
#define KC____T KC_T
#define KC____U KC_U
#define KC____V KC_V
#define KC____W KC_W
#define KC____X KC_X
#define KC____Y KC_Y
#define KC____Z KC_Z
#define KC__DOT KC_DOT

// custom tap holds grouped by row
#define GLTOUTR GG(LT_OUTR)
#define CLTOUTR CG(LT_OUTR)
#define ALTOUTR AG(LT_OUTR)

#define GLTPNKY GG(LT_PNKY)
#define CLTPNKY CG(LT_PNKY)
#define ALTPNKY AG(LT_PNKY)

#define GLTRING GG(LT_RING)
#define CLTRING CG(LT_RING)
#define ALTRING AG(LT_RING)

#define GLTMDLE GG(LT_MDLE)
#define CLTMDLE CG(LT_MDLE)
#define ALTMDLE AG(LT_MDLE)

#define GLTINDX GG(LT_INDX)
#define CLTINDX CG(LT_INDX)
#define ALTINDX AG(LT_INDX)

#define GLTINNR GG(LT_INNR)
#define CLTINNR CG(LT_INNR)
#define ALTINNR AG(LT_INNR)
// arcane

#define GRTOUTR GG(RT_OUTR)
#define CRTOUTR CG(RT_OUTR)
#define ARTOUTR AG(RT_OUTR)
// arcane

#define GRTPNKY GG(RT_PNKY)
#define CRTPNKY CG(RT_PNKY)
#define ARTPNKY AG(RT_PNKY)

#define GRTRING GG(RT_RING)
#define CRTRING CG(RT_RING)
#define ARTRING AG(RT_RING)

#define GRTMDLE GG(RT_MDLE)
#define CRTMDLE CG(RT_MDLE)
#define ARTMDLE AG(RT_MDLE)

#define GRTINDX GG(RT_INDX)
#define CRTINDX CG(RT_INDX)
#define ARTINDX AG(RT_INDX)

#define GRTINNR GG(RT_INNR)
#define CRTINNR CG(RT_INNR)
#define ARTINNR AG(RT_INNR)

#define GLHOUTR GG(LH_OUTR)
#define CLHOUTR CG(LH_OUTR)
#define ALHOUTR AG(LH_OUTR)

#define GLHPNKY GG(LH_PNKY)
#define CLHPNKY CG(LH_PNKY)
#define ALHPNKY AG(LH_PNKY)

#define GLHRING GG(LH_RING)
#define CLHRING CG(LH_RING)
#define ALHRING AG(LH_RING)

#define GLHMDLE GG(LH_MDLE)
#define CLHMDLE CG(LH_MDLE)
#define ALHMDLE AG(LH_MDLE)

#define GLHINDX GG(LH_INDX)
#define CLHINDX CG(LH_INDX)
#define ALHINDX AG(LH_INDX)

#define GLHINNR GG(LH_INNR)
#define CLHINNR CG(LH_INNR)
#define ALHINNR AG(LH_INNR)
// backspace

#define GRHOUTR GG(RH_OUTR)
#define CRHOUTR CG(RH_OUTR)
#define ARHOUTR AG(RH_OUTR)
// delete

#define GRHPNKY GG(RH_PNKY)
#define CRHPNKY CG(RH_PNKY)
#define ARHPNKY AG(RH_PNKY)

#define GRHRING GG(RH_RING)
#define CRHRING CG(RH_RING)
#define ARHRING AG(RH_RING)

#define GRHMDLE GG(RH_MDLE)
#define CRHMDLE CG(RH_MDLE)
#define ARHMDLE AG(RH_MDLE)

#define GRHINDX GG(RH_INDX)
#define CRHINDX CG(RH_INDX)
#define ARHINDX AG(RH_INDX)

#define GRHINNR GG(RH_INNR)
#define CRHINNR CG(RH_INNR)
#define ARHINNR AG(RH_INNR)
#define TH___QU TH(KC_Q) // tap qu, hold q

#define GLBOUTR GG(LB_OUTR)
#define CLBOUTR CG(LB_OUTR)
#define ALBOUTR AG(LB_OUTR)
// core leader key

#define GLBPNKY GG(LB_PNKY)
#define CLBPNKY CG(LB_PNKY)
#define ALBPNKY AG(LB_PNKY)

#define GLBRING GG(LB_RING)
#define CLBRING CG(LB_RING)
#define ALBRING AG(LB_RING)

#define GLBMDLE GG(LB_MDLE)
#define CLBMDLE CG(LB_MDLE)
#define ALBMDLE AG(LB_MDLE)

#define GLBINDX GG(LB_INDX)
#define CLBINDX CG(LB_INDX)
#define ALBINDX AG(LB_INDX)

#define GLBINNR GG(LB_INNR)
#define CLBINNR CG(LB_INNR)
#define ALBINNR AG(LB_INNR)
// arcane

#define GRBOUTR GG(RB_OUTR)
#define CRBOUTR CG(RB_OUTR)
#define ARBOUTR AG(RB_OUTR)
// arcane

#define GRBPNKY GG(RB_PNKY)
#define CRBPNKY CG(RB_PNKY)
#define ARBPNKY AG(RB_PNKY)
// parenthesis opening

#define GRBRING GG(RB_RING)
#define CRBRING CG(RB_RING)
#define ARBRING AG(RB_RING)
// comma

#define GRBMDLE GG(RB_MDLE)
#define CRBMDLE CG(RB_MDLE)
#define ARBMDLE AG(RB_MDLE)
// period

#define GRBINDX GG(RB_INDX)
#define CRBINDX CG(RB_INDX)
#define ARBINDX AG(RB_INDX)
// parenthesis closing

#define GRBINNR GG(RB_INNR)
#define CRBINNR CG(RB_INNR)
#define ARBINNR AG(RB_INNR)
// test

#define GLLTHMB GG(L_LTHMB)
#define CLLTHMB CG(L_LTHMB)
#define ALLTHMB AG(L_LTHMB)
// math/tab

#define GLMTHMB GG(L_MTHMB)
#define CLMTHMB CG(L_MTHMB)
#define ALMTHMB AG(L_MTHMB)

#define GLRTHMB GG(L_RTHMB)
#define CLRTHMB CG(L_RTHMB)
#define ALRTHMB AG(L_RTHMB)
// left space

#define GRLTHMB GG(R_LTHMB)
#define CRLTHMB CG(R_LTHMB)
#define ARLTHMB AG(R_LTHMB)
// right space

#define GRMTHMB GG(R_MTHMB)
#define CRMTHMB CG(R_MTHMB)
#define ARMTHMB AG(R_MTHMB)
