
#include QMK_KEYBOARD_H

enum layers{
    _MAIN,
  };

  const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAIN] = LAYOUT(
      KC_Z, KC_Y, KC_A,
      KC_C, KC_D, KC_S
    )
  };
