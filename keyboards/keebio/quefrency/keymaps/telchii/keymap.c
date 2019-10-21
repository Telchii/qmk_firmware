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

enum custom_keycodes {
    SHAREX_SNIP = SAFE_RANGE,  // Specify SAFE_RANGE on the first item only.
    SHAREX_GIF,
};

enum unicode_names {
    INTERROBANG,
    POOP,
    THINKING,
    THUMBSUP };

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
    MT(LCTL(LSFT(KC_ESC)), KC_ESC),      KC_PAUS, KC_GRV,  KC_1,    KC_2,    KC_3,   KC_4,   KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC, MT(LCA(KC_DELETE), KC_DELETE), \
    KC_F5,   KC_F2,   KC_TAB,  KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,   KC_U,   KC_I,    KC_O,     KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME, \
    KC_F10,  KC_F4,   KC_CAPSLOCK, KC_A, KC_S,    KC_D,    KC_F,    KC_G,    KC_H,   KC_J,   KC_K,    KC_L,     KC_SCLN, KC_QUOT, KC_ENT,  KC_END, \
    KC_F11,  KC_F10,  KC_LSFT, KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,    KC_N,   KC_M,   KC_COMM, KC_DOT,   KC_SLSH, KC_RSFT, KC_UP,   KC_PGUP, \
    KC_F12,  KC_F12,  KC_LCTL, MO(_FN1), KC_LGUI, KC_LALT, KC_SPC,           KC_SPC, KC_SPC, KC_RALT, MO(_FN1), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [_FN1] = LAYOUT_65_with_macro(
    KC_PAUS,        KC_PSCR, _______, KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,  LCTL(KC_PAUS),  LCTL(KC_PAUS), \
    X(INTERROBANG), KC_F6,   _______, RGB_TOG,  RGB_VAI, RGB_HUI, RGB_HUD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    X(POOP),        KC_F8,   _______, RGB_RMOD, RGB_VAD, RGB_MOD, _______, LCTL(KC_PSCREEN), _______, _______, _______, _______, _______, _______, KC_CALC, _______, \
    X(THINKING),    KC_MUTE, _______, _______,  _______, _______, _______, LCTL(LSFT(KC_PSCREEN)),    _______, _______, _______, _______, _______, _______, KC_VOLU, KC_PGDOWN, \
    X(THUMBSUP),    KC_MSTP, _______, _______,  _______, _______, LCTL(LALT(KC_DEL)),        _______, _______, _______, _______, _______, KC_MPRV, KC_VOLD, KC_MNXT
  )
};
// See QMK unicode page for info: https://beta.docs.qmk.fm/features/feature_unicode
const uint32_t PROGMEM unicode_map[] = {
    [INTERROBANG] = 0x203D,   //‽
    [POOP]        = 0x1F4A9,  //💩
    [THINKING]    = 0x1F914,  //🤔
    [THUMBSUP]    = 0x1F44D,  //👍
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
