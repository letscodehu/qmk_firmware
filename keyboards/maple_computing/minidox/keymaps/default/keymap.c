#include QMK_KEYBOARD_H
#include "keymap_hungarian.h"
#include <debug.h>


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_names {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  MCT_SCR
};

// TMUX stuff
void tmux_prefix(void) {
  register_code(KC_LCTL);
  tap_code(KC_B);
  unregister_code(KC_LCTL);
}
// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))
#define TMUX_LD LCTL(KC_B)
#define SCRCAP LSFT(LGUI(KC_4)) //Screen capture controls
uint8_t current_layer = 0;
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  |           |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  |           |   H  |   J  |   K  |   L  |   é  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  |           |   N  |   M  |   ,  |   .  |   -  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  | Ctrl | LOWER|      |    |      | RAISE| Shift|
 *                  `-------------| Space|    |BckSpc|------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_QWERTY] = LAYOUT_split_3x5_3(
  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                    KC_LCTL, LOWER, KC_BSPC,         KC_SPC, RAISE, OSM(MOD_LSFT)
),

/* Raise
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |           |   6  |   7  |   8  |   9  |   ö  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Tab | Left | Down |  Up  | Right|           |T Scr |   ü  |   ó  |   ő  |   ú  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   @  |   0  |  GUI |  Alt |      |           |Tmux  |   m  |   í  |   ű  |   á  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      | LOWER|      |    |      | RAISE|      |
 *                  `-------------|      |    |      |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_RAISE] = LAYOUT_split_3x5_3(
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
  KC_TAB,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,      MCT_SCR, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC,
  HU_AT, KC_GRV,  KC_LGUI, KC_LALT, _______,      TMUX_LD, _______, KC_NUBS, KC_BSLS,  KC_QUOT,
                    _______, _______, _______,      _______, _______, _______
),

/* Lower
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   '  |   "  |   +  |   !  |   %  |           |   /  |   =  |   (  |   )  |   Ö  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Esc |   |  |   &  |   {  |   }  |           |   *  |   Ü  |   Ó  |   Ő  |   Ú  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   \  |   ~  |   #  |   <  |   >  |           |   ;  |   [  |   ]  |   Ű  |   Á  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      | LOWER|      |    |      | RAISE|  Del |
 *                  `-------------|      |    | Enter|------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_LOWER] = LAYOUT_split_3x5_3(
  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
  KC_ESC,  HU_PIPE, HU_AMPR, HU_LCBR, HU_RCBR,      HU_ASTR, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR,
  HU_BSLS, KC_TILD, HU_HASH, HU_LABK, HU_RABK,      HU_SCLN, HU_LBRC, HU_RBRC, KC_PIPE,  KC_DQT,
                    _______, _______, _______,      KC_ENT,  _______, KC_DEL
),

/* Adjust (Lower + Raise)
 *
 * ,----------------------------------.           ,----------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |           |   F6 |  F7  |  F8  |  F9  |  F10 |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  F11 |  F12 |      |      |      |           |      |      |      |Scrnsh|caltde|
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | Reset|      |      |      |      |           |      |      |      |      |      |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      | LOWER|      |    |      | RAISE|      |
 *                  `-------------|      |    |      |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_ADJUST] =  LAYOUT_split_3x5_3(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
  KC_F11,  KC_F12,  RGB_SAD, RGB_VAD, RGB_HUD,      _______, _______, _______, SCRCAP, CALTDEL,
  QK_BOOT,   RGB_HUI, RGB_SAI, RGB_VAI, RGB_TOG,      _______, _______, _______, _______,  _______,
                    _______, _______, _______,      _______,  _______, _______
)
};
layer_state_t layer_state_set_user(layer_state_t state) {
	current_layer = get_highest_layer(state);
	return state;
}

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistant_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
    case MCT_SCR: // Tmux scroll mode
      if(record->event.pressed){
        tmux_prefix();
        tap_code(KC_PGUP);
      }
      break;
  }
	uprintf("ErgoKB:%u,%u,%u,%u,%u\n", record->event.key.col, record->event.key.row, record->event.pressed, current_layer, keycode);
  return true;
}
