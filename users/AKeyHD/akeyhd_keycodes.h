#pragma once
#include "charybdis.h"

// TODO keep in sync with keymapPostParse.ps1, bitwise_num, and rgb_matrix_stuff.h
enum layers {
    _AKEYHD,
    _COMBOREF,
    _VIMNAV,
    _VIMMOTION,
    _CTRLPR,
    _ALTPR,
    _GUIPR,
    _SYML,
    _SYMR,
    _POINTER, // TODO ALWAYS KEEP IN SYNC WITH RGB_MATRIX_STUFF
    _POINTEROPT,
    _MATH, // TODO ALWAYS KEEP IN SYNC WITH BITWISE_NUM
    _FUNCTION,
    _MEDIA,
    _ONESHOT,
    _GAME,
    _THINQU,
    _THINQUL,
    _THINQUR,
    _KEYBOARD,
    // 15 layer LT/LM threshold https://github.com/qmk/qmk_firmware/blob/master/docs/feature_layers.md#switching-and-toggling-layers-switching-and-toggling-layers
    _SECRET,
    _NAGINATA,
    _SHINGETA,
    _QWERTY,
    _RANDOM,
};

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
    MD_TO,   // to
    MD_FROM, // from
    MD_BUT,  // but
    MD_I,    // i
    MD_IPD,  // i'd
    MD_IPLL, // i'll
    MD_IPM,  // i'm
    MD_IPVE, // i've
    MD_YOUD, // you'd
    MD_YOUL, // you'll
    MD_YORE, // you're
    MD_YOVE, // you've
    MD_YOUR, // your
    MD_THEI, // their
    MD_THYR, // they're
    MD_THRE, // there
    MD_THEY, // they
    MD_THYD, // they'd
    MD_THYL, // they'll
    MD_HERE, // here
    MD_WHRE, // where
    MD_WEPR, // we're
    MD_WERE, // were
    MD_WEPD, // we'd
    MD_WELL, // well
    MD_WEPL, // we'll
    MD_WEPV, // we've
    MD_WHAT, // what
    MD_WITH, // with
    MD_PVE,  // 've
    MD_PS,   // 's

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

    KC_DBCL, // mouse double click
    RGB_MDE,
    CS__STP,
    CS_RSTP,
    // biwise entry
    BIN__1,
    BIN__2,
    BIN__4,
    BIN__8,
    BIN_16,

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

    // motion inputs
    MI_DOWN, // down
    MI_BACK, // left
    MI_FRNT, // right
    MI_JUMP, // up

    // fancy punctuation
    KC_ESLH,
    KC_DSLH,
    KC_DBSL,
    KC_DPIP,
    KC_DAMP,
    KC_DEQL,
    KC_TEQL,

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
    UP__DIR,
    SRCHSEL,

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

    // NEW_SAFE_RANGE // Use for keymap-specific codes
};
/* ---------- Aliases ---------- */
// unicode
#define UC__SPC UC(0x2800)
// binary tap holds
// TODO ALWAYS KEEP IN SYNC WITH LAYERS
#define BN1_DOT LT(11, KC_PDOT)
#define BN2_DC1 LT(11, KC_P1)
#define BN4_DC2 LT(11, KC_P2)
#define BN8_DC3 LT(11, KC_P3)
#define BN16_ET LT(11, KC_PENT) // really KC_RPRN but sending this to avoid collision
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

#define TH(k) LT(_AKEYHD, k)
#define SG(k) LT(_SHIFTPR, k)
#define CG(k) LT(_CTRLPR, k)
#define AG(k) LT(_ALTPR, k)
#define GG(k) LT(_GUIPR, k)

// base layers
#define BASE TO(_AKEYHD)
#define QWERTY TO(_QWERTY)
#define GAME TO(_GAME)
#define THINQU TO(_THINQU)

// layer taps
#define CTRL__R LT(_CTRLPR, KC_R)
#define ALT___T LT(_ALTPR, KC_T)
#define SML_SPC LT(_SYML, KC_SPC)
#define SMR_SPC LT(_SYMR, KC_SPC)
#define MATH_TB LT(_MATH, KC_TAB)
// default LTs
#define PT_Z LT(_POINTER, KC_Z)
#define PT_SLSH LT(_POINTER, KC_SLSH)

// momentary layer holds
#define THINQUL MO(_THINQUL)
#define THINQUR MO(_THINQUR)
#define VIMNAV MO(_VIMNAV)
#define FNCTION MO(_FUNCTION)

// one shot layers
#define SHRTCUT OSL(_FUNCTION)
#define MEDIA OSL(_MEDIA)
#define PNTROPT OSL(_POINTEROPT)
#define PNTRNAV OSL(_POINTERNAV)
#define OSLBASE OSL(_AKEYHD)

// toggle layers
#define VIMMTIN TG(_VIMMOTION)
#define KEYBRD TG(_KEYBOARD)
#define MATH TG(_MATH)
#define RANDOM TG(_RANDOM)

// TODO clean up these rejects from akeyhd_layout.h
#define PT_K LT(_POINTER, KC_K)
#define PT_H LT(_POINTER, KC_H)
#define VIMNV_S LT(_VIMNAV, KC_SPC)
#define PNT_T(k0) LT(_POINTER, k0)
#define _T(k0) LT(_ONESHOT, k0)
#define VIMNAV_T(k0) LT(_VIMNAV, k0)

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
#define F3_TH TH(KC_F3)
#define F5_TH TH(KC_F5)
#define F6_TH TH(KC_F6)
#define F11_TH TH(KC_F11)
#define F12_TH TH(KC_F12)

// charybdis formated
#define DPI_RMD DPI_RMOD
#define SDT_MOD S_D_MOD
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
