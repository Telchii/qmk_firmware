//Helpful Cheatsheet: https://jayliu50.github.io/qmk-cheatsheet/
//QMK Docs: https://beta.docs.qmk.fm/readme

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
    THUMBSUP
};

//LED State Flags
bool CapslockEnabled = false, 
     LayerChange = false;

//LED Reset values
uint32_t BackupModeCapsLock, BackupModeLayerChange;
uint16_t BackupHueCapsLock,  BackupHueLayerChange;
uint8_t  BackupSatCapsLock,  BackupSatLayerChange,
         BackupValCapsLock,  BackupValLayerChange;

//Function pre-declarations. Should probably go in its own header file...
void CapslockLED(void);
void BackupLEDStateCapsLock(void);
void RestoreLEDStateCapsLock(void);
void LayerChangeLED(int layer);
void BackupLEDStateLayerChange(void);
void RestoreLEDStateLayerChange(void);

//https://docs.qmk.fm/#/keycodes
//Row 1: double KC_BSPC on right side intentional.
//Row 5: double KC_SPC on right side intentional.
//
//Row key counts:
// 1: 19 keys
// 2: 17 keys
// 3: 16 keys
// 4: 16 keys
// 5: 15 keys
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
    X(THINKING),    KC_MUTE, _______, _______,  _______, _______, _______, LCTL(LSFT(KC_PSCREEN)), _______, _______, _______, _______, _______, _______, KC_VOLU, KC_PGDOWN, \
    X(THUMBSUP),    KC_MSTP, _______, _______,  _______, _______, LCTL(LALT(KC_DEL)), _______, _______, _______, _______, _______, KC_MPRV, KC_VOLD, KC_MNXT
  )
};

//See QMK unicode page for info: https://beta.docs.qmk.fm/features/feature_unicode
cosnt uint32_t PROGMEM unicode_map[] = {
    [INTERROBANG] = 0x203D,     //‽
    [POOP]        = 0x1F4A9,    //💩
    [THINKING]    = 0x1F914,    //🤔
    [THUMBSUP]    = 0x1F44D,    //👍
};

void matrix_init_user(void) {
    rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL);
};

void matrix_scan_user(void) {
  switch(biton32(layer_state)) {
    case (_BASE):
        if (LayerChange) {
            LayerChange = false;
            RestoreLEDStateLayerChange();
        }
        break;
    case(_FN1):
        LayerChange = true;
        BackupLEDStateLayerChange();
        LayerChangeLED(1);
        break;
  }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_CAPSLOCK:
      CapslockLED();
      break;
  }

  //return true => continue and "handle normally" the keypress.
  //return false => we've handled it here, don't continue to handle normally.
  //src (read through the whole linked section): https://beta.docs.qmk.fm/features/feature_macros#the-new-way-send_string-and-process_record_user
  return true; 
};

void CapslockLED(void) {
  if(CapslockEnabled) {
    BackupLEDStateCapsLock();

    //Set to static mode
    rgblight_mode(RGBLIGHT_MODE_KNIGHT);

    //Set values
    //rgblight_setrgb_range(RGB_YELLOW, 0, 3);
    //rgblight_setrgb_range(RGB_ORANGE, 4, 7);
    rgblight_sethsv(HSV_YELLOW, 255, 192); //192 ~= 75% of 255
  } else {
    RestoreLEDStateCapsLock();
  }

  //Flash out LED buffers to LEDs
  rgblight_set();
};

// --- Caps Lock LED Helpers ---
void BackupLEDStateCapsLock(void) {
  //https://beta.docs.qmk.fm/features/feature_rgblight#query
  BackupModeCapsLock = rgblight_get_mode();
  BackupHueCapsLock  = rgblight_get_hue();
  BackupSatCapsLock  = rgblight_get_sat();
  BackupValCapsLock  = rgblight_get_val();
};

void RestoreLEDStateCapsLock(void) {
  //https://beta.docs.qmk.fm/features/feature_rgblight#effect-mode-change
  rgblight_sethsv(BackupHueCapsLock, BackupSatCapsLock, BackupValCapsLock);
  rgblight_mode(BackupModeCapsLock);
};

// --- Layer Change LED Helpers ---
void LayerChangeLED(int layer) {
  switch(layer) {
    case(1): //_FN1
      rgblight_setrgb(RGB_CYAN);
      break;
  }

  //Flash out LED buffers to LEDs
  rgblight_set();
}

void BackupLEDStateLayerChange(void) {
  BackupModeLayerChange = rgblight_get_mode();
  BackupHueLayerChange  = rgblight_get_hue();
  BackupSatLayerChange  = rgblight_get_sat();
  BackupValLayerChange  = rgblight_get_val();
};

void RestoreLEDStateLayerChange(void) {
  rgblight_sethsv(BackupHueLayerChange, BackupSatLayerChange, BackupValLayerChange);
  rgblight_mode(BackupModeLayerChange);
};
