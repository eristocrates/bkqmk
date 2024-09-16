#include "utilities.h"

void send_string_with_caps_word(const char *str) {
    if (is_caps_word_on()) {
        // Add shift modifier for each character in the string
        while (*str) {
            // register_code(KC_LSFT);
            add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to next key.
            send_char(*str);
            // unregister_code(KC_LSFT);
            str++;
        }
    } else {
        // Send the string as is
        SEND_STRING(str);
    }
}

void call_keycode(uint16_t keycode) {
    keyrecord_t record;
    record.event.pressed = true;
    process_record_user(keycode, &record);
    record.event.pressed = false;
    process_record_user(keycode, &record);
}

// from tzarc's https://github.com/tzarc/qmk_userspace/blob/d78282b1d977749dca65d8275878143cef31c4c3/users/tzarc/tzarc_names.c#L12
static const char *const keycode_display_map[][2] = {
    [KC_A]             = {"a", "A"},
    [KC_B]             = {"b", "B"},
    [KC_C]             = {"c", "C"},
    [KC_D]             = {"d", "D"},
    [KC_E]             = {"e", "E"},
    [KC_F]             = {"f", "F"},
    [KC_G]             = {"g", "G"},
    [KC_H]             = {"h", "H"},
    [KC_I]             = {"i", "I"},
    [KC_J]             = {"j", "J"},
    [KC_K]             = {"k", "K"},
    [KC_L]             = {"l", "L"},
    [KC_M]             = {"m", "M"},
    [KC_N]             = {"n", "N"},
    [KC_O]             = {"o", "O"},
    [KC_P]             = {"p", "P"},
    [KC_Q]             = {"q", "Q"},
    [KC_R]             = {"r", "R"},
    [KC_S]             = {"s", "S"},
    [KC_T]             = {"t", "T"},
    [KC_U]             = {"u", "U"},
    [KC_V]             = {"v", "V"},
    [KC_W]             = {"w", "W"},
    [KC_X]             = {"x", "X"},
    [KC_Y]             = {"y", "Y"},
    [KC_Z]             = {"z", "Z"},
    [KC_1]             = {"1", "!"},
    [KC_2]             = {"2", "@"},
    [KC_3]             = {"3", "#"},
    [KC_4]             = {"4", "$"},
    [KC_5]             = {"5", "%"},
    [KC_6]             = {"6", "^"},
    [KC_7]             = {"7", "&"},
    [KC_8]             = {"8", "*"},
    [KC_9]             = {"9", "("},
    [KC_0]             = {"0", ")"},
    [KC_ENTER]         = {"Ent", "Ent"},
    [KC_ESCAPE]        = {"Esc", "Esc"},
    [KC_BACKSPACE]     = {"Bksp", "Bksp"},
    [KC_TAB]           = {"Tab", "Tab"},
    [KC_SPACE]         = {"Spc", "Spc"},
    [KC_MINUS]         = {"-", "_"},
    [KC_EQUAL]         = {"=", "="},
    [KC_LEFT_BRACKET]  = {"[", "{"},
    [KC_RIGHT_BRACKET] = {"]", "}"},
    [KC_BACKSLASH]     = {"\\", "|"},
    [KC_NONUS_HASH]    = {"#", "#"},
    [KC_SEMICOLON]     = {";", ":"},
    [KC_QUOTE]         = {"'", "\""},
    [KC_GRAVE]         = {"`", "~"},
    [KC_COMMA]         = {",", "<"},
    [KC_DOT]           = {".", ">"},
    [KC_SLASH]         = {"/", "?"},
    [KC_CAPS_LOCK]     = {"Caps", "Caps"},
    [KC_F1]            = {"F1", "F1"},
    [KC_F2]            = {"F2", "F2"},
    [KC_F3]            = {"F3", "F3"},
    [KC_F4]            = {"F4", "F4"},
    [KC_F5]            = {"F5", "F5"},
    [KC_F6]            = {"F6", "F6"},
    [KC_F7]            = {"F7", "F7"},
    [KC_F8]            = {"F8", "F8"},
    [KC_F9]            = {"F9", "F9"},
    [KC_F10]           = {"F10", "F10"},
    [KC_F11]           = {"F11", "F11"},
    [KC_F12]           = {"F12", "F12"},
    [KC_PRINT_SCREEN]  = {"PScr", "PScr"},
    [KC_SCROLL_LOCK]   = {"ScrL", "ScrL"},
    [KC_PAUSE]         = {"Paus", "Paus"},
    [KC_INSERT]        = {"Ins", "Ins"},
    [KC_HOME]          = {"Home", "Home"},
    [KC_PGUP]          = {"PgUp", "PgUp"},
    [KC_DELETE]        = {"Del", "Del"},
    [KC_END]           = {"End", "End"},
    [KC_PAGE_DOWN]     = {"PgDn", "PgDn"},
    [KC_RIGHT]         = {"Rght", "Rght"},
    [KC_LEFT]          = {"Left", "Left"},
    [KC_DOWN]          = {"Up", "Up"},
    [KC_UP]            = {"Down", "Down"},
    [KC_NUM_LOCK]      = {"NumL", "NumL"},

    [VM_LEFT] = {"\tLeft Action", ""},
    [VM_DOWN] = {"\tDown Action", ""},
    [VM___UP] = {"\tUp Action", ""},
    [VM_RGHT] = {"\tRight Action", ""},
    [VM_NTRL] = {"\tNeutral Action", ""},
    [VM_HORI] = {"\tHorizontal Action", ""},
    [VM_VERT] = {"\tVertical Action", ""},
    [VM_CHAN] = {"\tChange Action", ""},
    [VM_DELE] = {"\tDelete Action", ""},
    [VM_YANK] = {"\tYank Action", ""},
    [VM_VISU] = {"\tVisual Action", ""},
    [VM_MRKQ] = {"\tQuote Mark Action", ""},
    [VM_MRKG] = {"\tGrave Mark Action", ""},
    [VM_FRMT] = {"\tFormat Action", ""},
    [VM_FOLD] = {"\tFold Action", ""},
    [VM_SRCH] = {"\tFold Action", ""},
    [MI_DOWN] = {"Down Input", ""},
    [MI_BACK] = {"Back Input", ""},
    [MI_FRNT] = {"Front Input", ""},
    [MI_JUMP] = {"Jump Input", ""},
};

static const char *key_name_hid(uint16_t keycode, bool shifted) {
    if (keycode > KC_NUM_LOCK && keycode < VM_LEFT && keycode > MI_JUMP) {
        return "Unknown";
    }
    return keycode_display_map[keycode][shifted ? 1 : 0];
}
const char *key_name(uint16_t keycode, bool shifted) {
    /*
    char buf1[16];
    char buf2[16];
    (void)buf1;
    (void)buf2;
    */
    switch (keycode) {
        case KC_A ... KC_NUM_LOCK:
        case VM_LEFT:
        case VM_DOWN:
        case VM___UP:
        case VM_RGHT:
        case VM_NTRL:
        case VM_HORI:
        case VM_VERT:
        case VM_CHAN:
        case VM_DELE:
        case VM_YANK:
        case VM_VISU:
        case VM_MRKQ:
        case VM_MRKG:
        case VM_FRMT:
        case VM_FOLD:
        case VM_SRCH:
        case MI_DOWN:
        case MI_BACK:
        case MI_FRNT:
        case LTP_ARC:
        case RTP_ARC:
        case LHM_ARC:
        case RHM_ARC:
        case LBM_ARC:
        case RBM_ARC:

        case MI_JUMP: {
            const char *name = key_name_hid(keycode, shifted);
            if (!name) return "Unknown";
            return name;
        }
        default:
            return "";
    }
}
