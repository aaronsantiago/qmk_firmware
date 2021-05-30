
#include QMK_KEYBOARD_H

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_ENT):
            return true;
        case LT(3,KC_SPC):
        default:
            return false;
    }
}