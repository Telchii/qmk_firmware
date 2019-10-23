// Helpful Cheatsheet: https://jayliu50.github.io/qmk-cheatsheet/
// QMK Docs: https://beta.docs.qmk.fm/readme

#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0
#define _FN1 1
#define _EMOJI 2

enum custom_keycodes {
    SHAREX_SNIP = SAFE_RANGE,  // Specify SAFE_RANGE on the first item only.
    SHAREX_GIF,
};

enum unicode_names {
    INTERROBANG,
    POOP,
    THINKING,
    THUMBSUP,
    FIRE,
    LAUGH,
    MIDDLE_FINGER,

    //Unicodes for Emoji Layer
    REG_A,
    REG_B,
    REG_B_RED,
    REG_C,
    REG_D,
    REG_E,
    REG_F,
    REG_G,
    REG_H,
    REG_I,
    REG_J,
    REG_K,
    REG_L,
    REG_M,
    REG_N,
    REG_O,
    REG_P,
    REG_Q,
    REG_R,
    REG_S,
    REG_T,
    REG_U,
    REG_V,
    REG_W,
    REG_X,
    REG_Y,
    REG_Z,
    DIGIT_0,
    DIGIT_1,
    DIGIT_2,
    DIGIT_3,
    DIGIT_4,
    DIGIT_5,
    DIGIT_6,
    DIGIT_7,
    DIGIT_8,
    DIGIT_9,
};

// See QMK unicode page for info: https://beta.docs.qmk.fm/features/feature_unicode
const uint32_t PROGMEM unicode_map[] = {
    [INTERROBANG] = 0x203D,   //‽
    [POOP]        = 0x1F4A9,  //💩
    [THINKING]    = 0x1F914,  //🤔
    [THUMBSUP]    = 0x1F44D,  //👍
    [FIRE]        = 0x1F44D,  //🔥
    [LAUGH]       = 0x1F44D,  //😂
    [MIDDLE_FINGER] =0x1f595, //🖕

    //Regional indicators
    [REG_A]       = 0x1F1E6,
    [REG_B]       = 0x1F1E7,
    [REG_C]       = 0x1F1E8,
    [REG_D]       = 0x1F1E9,
    [REG_E]       = 0x1F1EA,
    [REG_F]       = 0x1F1EB,
    [REG_G]       = 0x1F1EC,
    [REG_H]       = 0x1F1ED,
    [REG_I]       = 0x1F1EE,
    [REG_J]       = 0x1F1EF,
    [REG_K]       = 0x1F1F0,
    [REG_L]       = 0x1F1F1,
    [REG_M]       = 0x1F1F2,
    [REG_N]       = 0x1F1F3,
    [REG_O]       = 0x1F1F4,
    [REG_P]       = 0x1F1F5,
    [REG_Q]       = 0x1F1F6,
    [REG_R]       = 0x1F1F7,
    [REG_S]       = 0x1F1F8,
    [REG_T]       = 0x1F1F9,
    [REG_U]       = 0x1F1FA,
    [REG_V]       = 0x1F1FB,
    [REG_W]       = 0x1F1FC,
    [REG_X]       = 0x1F1FD,
    [REG_Y]       = 0x1F1FE,
    [REG_Z]       = 0x1F1FF,

    //Digits
    [DIGIT_0] = 0x30,
    [DIGIT_1] = 0x31,
    [DIGIT_2] = 0x32,
    [DIGIT_3] = 0x33,
    [DIGIT_4] = 0x34,
    [DIGIT_5] = 0x35,
    [DIGIT_6] = 0x36,
    [DIGIT_7] = 0x37,
    [DIGIT_8] = 0x38,
    [DIGIT_9] = 0x39,

};

// LED Reset values
uint32_t BackupModeCapsLock, BackupModeLayerChange;
uint16_t BackupHueCapsLock, BackupHueLayerChange;
uint8_t  BackupSatCapsLock, BackupSatLayerChange, BackupValCapsLock, BackupValLayerChange;

// Forward Function Declarations
void SetDefaultLed(void);
void SetCapslockLed(void);
void SetLayerLed(int layer);

// https://docs.qmk.fm/#/keycodes
// Row 1: double KC_BSPC on right side intentional.
// Row 5: double KC_SPC on right side intentional.
//
// Row key counts:
// 1: 19 keys
// 2: 17 keys
// 3: 16 keys
// 4: 16 keys
// 5: 15 keys (space between 7 and 8)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_65_with_macro(
    KC_ESC,  KC_PAUS, KC_GRV,  KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,   KC_7,   KC_8,    KC_9,     KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC, KC_DELETE, \
    KC_F5,   KC_F2,   KC_TAB,  KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,   KC_U,   KC_I,    KC_O,     KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME, \
    KC_F10,  KC_F4,   KC_CAPSLOCK, KC_A, KC_S,    KC_D,    KC_F,    KC_G,    KC_H,   KC_J,   KC_K,    KC_L,     KC_SCLN, KC_QUOT, KC_ENT,  KC_END, \
    KC_F11,  KC_F10,  KC_LSFT, KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,    KC_N,   KC_M,   KC_COMM, KC_DOT,   KC_SLSH, KC_RSFT, KC_UP,   KC_PGUP, \
    KC_F12,  KC_F12,  KC_LCTL, MO(_FN1), KC_LGUI, KC_LALT, KC_SPC,           KC_SPC, KC_SPC, KC_RALT, MO(_FN1), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [_FN1] = LAYOUT_65_with_macro(
    KC_PAUS,        KC_PSCR, _______,          KC_F1,    KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_BSPC, KC_DELETE, \
    X(INTERROBANG), KC_F6,   _______,          RGB_TOG,  RGB_VAI, RGB_MOD,  RGB_HUI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    X(POOP),        KC_F8,   X(LAUGH),         _______,  RGB_VAD, RGB_RMOD, RGB_HUD, LCTL(KC_PSCREEN), _______, _______, _______, _______, _______, _______, KC_CALC, _______, \
    X(THINKING),    KC_MUTE, X(FIRE),          _______,  _______, _______,  _______, LCTL(LSFT(KC_PSCREEN)),    _______, _______, _______, _______, _______, _______, KC_VOLU, KC_PGDOWN, \
    X(THUMBSUP),    KC_MSTP, X(MIDDLE_FINGER), _______,  _______, _______,  LCTL(LALT(KC_DEL)),                 _______, _______, _______, _______, _______, KC_MPRV, KC_VOLD, KC_MNXT
  ),

  [_EMOJI] = LAYOUT_65_with_macro(
    KC_ESC, KC_PAUS, KC_GRV,      X(DIGIT_1), X(DIGIT_2), X(DIGIT_3), X(DIGIT_4), X(DIGIT_5), X(DIGIT_6), X(DIGIT_7), X(DIGIT_8), X(DIGIT_9), X(DIGIT_0), KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC, KC_DELETE, \
    KC_F5,  KC_F2,   KC_TAB,      X(REG_Q),   X(REG_W),   X(REG_E),   X(REG_R),   X(REG_T),   X(REG_Y),   X(REG_U),   X(REG_I),   X(REG_O),   X(REG_P),   KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME, \
    KC_F10, KC_F4,   KC_CAPSLOCK, X(REG_A),   X(REG_S),   X(REG_D),   X(REG_F),   X(REG_G),   X(REG_H),   X(REG_J),   X(REG_K),   X(REG_L),   KC_SCLN,    KC_QUOT, KC_ENT,  KC_END,  \
    KC_F11, KC_F10,  KC_LSFT,     X(REG_Z),   X(REG_X),   X(REG_C),   X(REG_V),   X(REG_B),   X(REG_N),   X(REG_M),   KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT, KC_UP,   KC_PGUP, \
    KC_F12, KC_F12,  KC_LCTL,     MO(_FN1),   KC_LGUI,    KC_LALT,    KC_SPC,                 KC_SPC,     KC_SPC,     KC_RALT,    MO(_FN1),   KC_RCTL,    KC_LEFT, KC_DOWN, KC_RGHT
  ),
};

void SetDefaultLed(void) {
    rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL);
}

void SetCapslockLed(void) {
    rgblight_setrgb(RGB_YELLOW);
    rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
}

void SetLayerLed(int layer) {
    switch (layer) {
        case (_EMOJI): // 2
            rgblight_setrgb(RGB_CORAL);
            rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
            break;
        case (_FN1):  // 1
            rgblight_setrgb(RGB_CYAN);
            rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
            break;
        case (_BASE):  // 0
        default:
            SetDefaultLed();
            break;
    }
}

bool CapslockFlag = false, UpdateForCapslockOff = false;

void matrix_init_user(void) {
    SetDefaultLed();
    set_unicode_input_mode(UC_LNX);
};

int  PreviousScan = 55, CurrentScan = 33; //Arbitrary, different default values
void matrix_scan_user(void) {
    CurrentScan = biton32(layer_state);
    if ((CurrentScan != PreviousScan && !CapslockFlag) || UpdateForCapslockOff) {
        PreviousScan = CurrentScan;
        UpdateForCapslockOff = false;

        switch (CurrentScan) {
            case (_BASE):
                SetLayerLed(_BASE);
                break;
            case (_FN1):
                SetLayerLed(_FN1);
                break;
            case (_EMOJI):
                SetLayerLed(_EMOJI);
                break;
        }
    }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_CAPSLOCK:
            if (record->event.pressed) {
                CapslockFlag = !CapslockFlag;
                if (CapslockFlag) {
                    UpdateForCapslockOff = false;
                    SetCapslockLed();
                } else {
                    UpdateForCapslockOff = true;
                }
            }  // else (key release) do nothing
            break;
    }

    // return true => continue and "handle normally" the keypress.
    // return false => we've handled it here, don't continue to handle normally.
    // src (read through the whole linked section): https://beta.docs.qmk.fm/features/feature_macros#the-new-way-send_string-and-process_record_user
    return true;
};
