#pragma once
#include "charybdis.h"

// TODO keep in sync with keymapPostParse.ps1
enum layers {
    _BRAINROT,
    _COMBOREF,
    _SHIFTGR,
    _CTRLGR,
    _ALTGR,
    _GUIGR,
    _POINTER,
    _POINTEROPT,
    _POINTERNAV,
    _MATH,
    _VIMMOTION,
    _FUNCTION,
    _MEDIA,
    _NSHOT,
    _GAME,
    _THINQU,
    _THINQUL,
    _THINQUR,
    // 15 layer LT/LM threshold https://github.com/qmk/qmk_firmware/blob/master/docs/feature_layers.md#switching-and-toggling-layers-switching-and-toggling-layers
    _KEYBOARD,
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
    LTP_ARC,
    RTP_ARC,
    LBM_ARC,
    RBM_ARC,
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
    CLEAR,
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
    SW_WIN,
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
// macros

#define TH(k) LT(_BRAINROT, k)
#define SG(k) LT(_SHIFTGR, k)
#define CG(k) LT(_CTRLGR, k)
#define AG(k) LT(_ALTGR, k)
#define GG(k) LT(_GUIGR, k)

// base layers
#define BASE TO(_BRAINROT)
#define QWERTY TO(_QWERTY)
#define GAME TO(_GAME)
#define THINQU TO(_THINQU)

// layer taps
#define GUGR_TB LT(_GUIGR, KC_TAB)
#define SHFGR_R LT(_SHIFTGR, KC_R)
#define RSHGR_T LT(_CTRLGR, KC_T)
// default LTs
#define PT_Z LT(_POINTER, KC_Z)
#define PT_SLSH LT(_POINTER, KC_SLSH)

// momentary layer holds
#define THINQUL MO(_THINQUL)
#define THINQUR MO(_THINQUR)
#define VIMNAV MO(_VIMMOTION)

// one shot layers
#define SHRTCUT OSL(_FUNCTION)
#define MEDIA OSL(_MEDIA)
#define PNTROPT OSL(_POINTEROPT)
#define PNTRNAV OSL(_POINTERNAV)

#define KEYBRD TG(_KEYBOARD)
#define MATH TG(_MATH)
#define RANDOM TG(_RANDOM)

// TODO clean up these rejects from brainrot_layout.h
#define PT_K LT(_POINTER, KC_K)
#define PT_H LT(_POINTER, KC_H)
#define VIMNV_S LT(_VIMMOTION, KC_SPC)
#define PNT_T(k0) LT(_POINTER, k0)
#define _T(k0) LT(_NSHOT, k0)
#define VIMNAV_T(k0) LT(_VIMMOTION, k0)

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

// custom base tap holds
#define TH____A TH(KC_A)
#define TH____B TH(KC_B)
#define TH____C TH(KC_C)
#define TH____D TH(KC_D)
#define TH____E TH(KC_E)
#define TH____F TH(KC_F)
#define TH____G TH(KC_G)
#define TH____H TH(KC_H)
#define TH____I TH(KC_I)
#define TH____J TH(KC_J)
#define TH____K TH(KC_K)
#define TH____L TH(KC_L)
#define TH____M TH(KC_M)
#define TH____N TH(KC_N)
#define TH____O TH(KC_O)
#define TH____P TH(KC_P)
#define TH____Q TH(KC_Q)
#define TH___QU TH(KC_Q) // tap qu, hold q
#define TH____R TH(KC_R)
#define TH____S TH(KC_S)
#define TH____T TH(KC_T)
#define TH____U TH(KC_U)
#define TH____V TH(KC_V)
#define TH____W TH(KC_W)
#define TH____X TH(KC_X)
#define TH____Y TH(KC_Y)
#define TH____Z TH(KC_Z)

// custom Shift tap holds
#define SLTOUTR SG(LT_OUTR)
#define SLTPNKY SG(LT_PNKY)
#define SLTRING SG(LT_RING)
#define SLTMDLE SG(LT_MDLE)
#define SLTINDX SG(LT_INDX)
#define SLTINNR SG(LT_INNR)
#define SRTOUTR SG(RT_OUTR)
#define SRTPNKY SG(RT_PNKY)
#define SRTRING SG(RT_RING)
#define SRTMDLE SG(RT_MDLE)
#define SRTINDX SG(RT_INDX)
#define SRTINNR SG(RT_INNR)
#define SLHOUTR SG(LH_OUTR)
#define SLHPNKY SG(LH_PNKY)
#define SLHRING SG(LH_RING)
#define SLHMDLE SG(LH_MDLE)
#define SLHINDX SG(LH_INDX)
#define SLHINNR SG(LH_INNR)
#define SRHOUTR SG(RH_OUTR)
#define SRHPNKY SG(RH_PNKY)
#define SRHRING SG(RH_RING)
#define SRHMDLE SG(RH_MDLE)
#define SRHINDX SG(RH_INDX)
#define SRHINNR SG(RH_INNR)
#define SLBOUTR SG(LB_OUTR)
#define SLBPNKY SG(LB_PNKY)
#define SLBRING SG(LB_RING)
#define SLBMDLE SG(LB_MDLE)
#define SLBINDX SG(LB_INDX)
#define SLBINNR SG(LB_INNR)
#define SRBOUTR SG(RB_OUTR)
#define SRBPNKY SG(RB_PNKY)
#define SRBRING SG(RB_RING)
#define SRBMDLE SG(RB_MDLE)
#define SRBINDX SG(RB_INDX)
#define SRBINNR SG(RB_INNR)
#define SLLTHMB SG(L_LTHMB)
#define SLMTHMB SG(L_MTHMB)
#define SLRTHMB SG(L_RTHMB)
#define SRLTHMB SG(R_LTHMB)
#define SRMTHMB SG(R_MTHMB)

// custom Ctrl tap holds
#define CLTOUTR CG(LT_OUTR)
#define CLTPNKY CG(LT_PNKY)
#define CLTRING CG(LT_RING)
#define CLTMDLE CG(LT_MDLE)
#define CLTINDX CG(LT_INDX)
#define CLTINNR CG(LT_INNR)
#define CRTOUTR CG(RT_OUTR)
#define CRTPNKY CG(RT_PNKY)
#define CRTRING CG(RT_RING)
#define CRTMDLE CG(RT_MDLE)
#define CRTINDX CG(RT_INDX)
#define CRTINNR CG(RT_INNR)
#define CLHOUTR CG(LH_OUTR)
#define CLHPNKY CG(LH_PNKY)
#define CLHRING CG(LH_RING)
#define CLHMDLE CG(LH_MDLE)
#define CLHINDX CG(LH_INDX)
#define CLHINNR CG(LH_INNR)
#define CRHOUTR CG(RH_OUTR)
#define CRHPNKY CG(RH_PNKY)
#define CRHRING CG(RH_RING)
#define CRHMDLE CG(RH_MDLE)
#define CRHINDX CG(RH_INDX)
#define CRHINNR CG(RH_INNR)
#define CLBOUTR CG(LB_OUTR)
#define CLBPNKY CG(LB_PNKY)
#define CLBRING CG(LB_RING)
#define CLBMDLE CG(LB_MDLE)
#define CLBINDX CG(LB_INDX)
#define CLBINNR CG(LB_INNR)
#define CRBOUTR CG(RB_OUTR)
#define CRBPNKY CG(RB_PNKY)
#define CRBRING CG(RB_RING)
#define CRBMDLE CG(RB_MDLE)
#define CRBINDX CG(RB_INDX)
#define CRBINNR CG(RB_INNR)
#define CLLTHMB CG(L_LTHMB)
#define CLMTHMB CG(L_MTHMB)
#define CLRTHMB CG(L_RTHMB)
#define CRLTHMB CG(R_LTHMB)
#define CRMTHMB CG(R_MTHMB)

// custom Alt tap holds
#define ALTOUTR AG(LT_OUTR)
#define ALTPNKY AG(LT_PNKY)
#define ALTRING AG(LT_RING)
#define ALTMDLE AG(LT_MDLE)
#define ALTINDX AG(LT_INDX)
#define ALTINNR AG(LT_INNR)
#define ARTOUTR AG(RT_OUTR)
#define ARTPNKY AG(RT_PNKY)
#define ARTRING AG(RT_RING)
#define ARTMDLE AG(RT_MDLE)
#define ARTINDX AG(RT_INDX)
#define ARTINNR AG(RT_INNR)
#define ALHOUTR AG(LH_OUTR)
#define ALHPNKY AG(LH_PNKY)
#define ALHRING AG(LH_RING)
#define ALHMDLE AG(LH_MDLE)
#define ALHINDX AG(LH_INDX)
#define ALHINNR AG(LH_INNR)
#define ARHOUTR AG(RH_OUTR)
#define ARHPNKY AG(RH_PNKY)
#define ARHRING AG(RH_RING)
#define ARHMDLE AG(RH_MDLE)
#define ARHINDX AG(RH_INDX)
#define ARHINNR AG(RH_INNR)
#define ALBOUTR AG(LB_OUTR)
#define ALBPNKY AG(LB_PNKY)
#define ALBRING AG(LB_RING)
#define ALBMDLE AG(LB_MDLE)
#define ALBINDX AG(LB_INDX)
#define ALBINNR AG(LB_INNR)
#define ARBOUTR AG(RB_OUTR)
#define ARBPNKY AG(RB_PNKY)
#define ARBRING AG(RB_RING)
#define ARBMDLE AG(RB_MDLE)
#define ARBINDX AG(RB_INDX)
#define ARBINNR AG(RB_INNR)
#define ALLTHMB AG(L_LTHMB)
#define ALMTHMB AG(L_MTHMB)
#define ALRTHMB AG(L_RTHMB)
#define ARLTHMB AG(R_LTHMB)
#define ARMTHMB AG(R_MTHMB)

// custom Gui tap holds
#define GLTOUTR GG(LT_OUTR)
#define GLTPNKY GG(LT_PNKY)
#define GLTRING GG(LT_RING)
#define GLTMDLE GG(LT_MDLE)
#define GLTINDX GG(LT_INDX)
#define GLTINNR GG(LT_INNR)
#define GRTOUTR GG(RT_OUTR)
#define GRTPNKY GG(RT_PNKY)
#define GRTRING GG(RT_RING)
#define GRTMDLE GG(RT_MDLE)
#define GRTINDX GG(RT_INDX)
#define GRTINNR GG(RT_INNR)
#define GLHOUTR GG(LH_OUTR)
#define GLHPNKY GG(LH_PNKY)
#define GLHRING GG(LH_RING)
#define GLHMDLE GG(LH_MDLE)
#define GLHINDX GG(LH_INDX)
#define GLHINNR GG(LH_INNR)
#define GRHOUTR GG(RH_OUTR)
#define GRHPNKY GG(RH_PNKY)
#define GRHRING GG(RH_RING)
#define GRHMDLE GG(RH_MDLE)
#define GRHINDX GG(RH_INDX)
#define GRHINNR GG(RH_INNR)
#define GLBOUTR GG(LB_OUTR)
#define GLBPNKY GG(LB_PNKY)
#define GLBRING GG(LB_RING)
#define GLBMDLE GG(LB_MDLE)
#define GLBINDX GG(LB_INDX)
#define GLBINNR GG(LB_INNR)
#define GRBOUTR GG(RB_OUTR)
#define GRBPNKY GG(RB_PNKY)
#define GRBRING GG(RB_RING)
#define GRBMDLE GG(RB_MDLE)
#define GRBINDX GG(RB_INDX)
#define GRBINNR GG(RB_INNR)
#define GLLTHMB GG(L_LTHMB)
#define GLMTHMB GG(L_MTHMB)
#define GLRTHMB GG(L_RTHMB)
#define GRLTHMB GG(R_LTHMB)
#define GRMTHMB GG(R_MTHMB)
