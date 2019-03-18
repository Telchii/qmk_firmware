#include QMK_KEYBOARD_H

typedef enum {
    SINGLE_TAP, SINGLE_HOLD, DOUBLE
} tap_dance_state_enum;

enum {
  TD_KEY = 0
};

static tap_dance_state_enum tap_dance_state;
static bool tap_dance_active = false;
static uint16_t timer;
volatile uint8_t firstrun = true;

void dance_cycle(bool override_timer) {
  if (tap_dance_active)
  {
    if (timer_elapsed(timer) > 100 || override_timer)
    {
      switch (tap_dance_state)
      {
		case SINGLE_TAP: 
		{
		  rgblight_enable_noeeprom();
		  rgblight_setrgb(0xff, 0xff, 0xff);
          rgblight_increase_hue_noeeprom();
		  break;
		}
		
        case SINGLE_HOLD:
        {
		  rgblight_enable_noeeprom();
		  rgblight_setrgb(0x0, 0xff, 0xff);
          rgblight_increase_hue_noeeprom();
          break;
        }

        case DOUBLE:
        {
		  rgblight_setrgb(0xff, 0x0, 0xff);
          rgblight_enable_noeeprom();
          break;
        }

        default:
		  rgblight_decrease_hue_noeeprom();
          break;
      }

      timer = timer_read();
    }
  }
}

void dance_finished(qk_tap_dance_state_t *state, void* user_data) {
  // Determine the current state
  switch (state->count)
  {
    case 1:
    {
      // if (state->interrupted || state->pressed == 0) tap_dance_state = SINGLE_TAP;
      // else tap_dance_state = SINGLE_HOLD;
	  tap_dance_state = SINGLE_TAP;
      break;
    }
	
    case 2:
    {
      tap_dance_state = DOUBLE;
      break;
    }
	
    default:
    {
      tap_dance_state = DOUBLE;
      break;
    }
  }

  switch (tap_dance_state)
  {
    case SINGLE_TAP:
    {
	  send_string_with_delay_P(PSTR(SS_DOWN(X_LGUI) "L" SS_UP(X_LGUI)), 10);
      tap_dance_active = false;
      break;
    }

    case SINGLE_HOLD: 
	case DOUBLE:
	{
	  send_string_with_delay_P(PSTR(SS_DOWN(X_LCTRL) SS_DOWN(X_LALT) SS_DOWN(X_DELETE) SS_UP(X_LCTRL) SS_UP(X_LALT) SS_UP(X_DELETE)), 10);
      tap_dance_active = false;
      break;
	}
	
  }
}

void dance_reset(qk_tap_dance_state_t *state, void* user_data)
{
  tap_dance_active = false;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_KEY] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_finished, dance_reset)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(TD(TD_KEY))
};

void keyboard_post_init_user (void) {
	if (firstrun && timer_elapsed(timer) > 1000) {
	  firstrun = false;
	  rgblight_sethsv_noeeprom(0x0, 0xff, 0x80);
	  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
	  rgblight_setrgb(0xff, 0xff, 0xff);
	  rgblight_enable_noeeprom();
	  rgblight_decrease_hue_noeeprom();
	}
}

void matrix_scan_user(void) {
	dance_cycle(false);
}L
