#include QMK_KEYBOARD_H

#include "joystick.h"

enum my_keycodes {
  JOYSTICK_L = SAFE_RANGE,
  JOYSTICK_R,
  JOYSTICK_U,
  JOYSTICK_D,
  JOYSTICK_M,
};
#ifdef ANALOG_JOYSTICK_ENABLE

//joystick config
joystick_config_t joystick_axes[2] = {
    [0] = JOYSTICK_AXIS_VIRTUAL,
    [1] = JOYSTICK_AXIS_VIRTUAL
};

//static uint8_t precision_val = 70;
static uint8_t axesFlags = 0;
enum axes {
    Precision = 1,
    Axis1High = 2,
    Axis1Low = 4,
    Axis2High = 8,
    Axis2Low = 16
};

bool checkFlag(uint8_t flag) {
    return (axesFlags >> (flag - 1)) & 1;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
#ifdef ANALOG_JOYSTICK_ENABLE
        // virtual joystick
#    if JOYSTICK_AXES_COUNT > 1
        case JOYSTICK_U:
            if (record->event.pressed) {
                axesFlags |= Axis2Low;
            } else {
                axesFlags &= ~Axis2Low;
            }
            joystick_status.status |= JS_UPDATED;
            break;
        case JOYSTICK_D:
            if (record->event.pressed) {
                axesFlags |= Axis2High;
            } else {
                axesFlags &= ~Axis2High;
            }
            joystick_status.status |= JS_UPDATED;
            break;
#    endif
        case JOYSTICK_L:
            if (record->event.pressed) {
                axesFlags |= Axis1Low;
            } else {
                axesFlags &= ~Axis1Low;
            }
            joystick_status.status |= JS_UPDATED;
            break;
        case JOYSTICK_R:
            if (record->event.pressed) {
                axesFlags |= Axis1High;
            } else {
                axesFlags &= ~Axis1High;
            }
            joystick_status.status |= JS_UPDATED;
            break;
        case JOYSTICK_M:
            if (record->event.pressed) {
                axesFlags |= Precision;
            } else {
                axesFlags &= ~Precision;
            }
            joystick_status.status |= JS_UPDATED;
            break;
        joystick_status.axes[0] =
            (checkFlag(Axis1Low) ? -127 : 0) +
            (checkFlag(Axis1High) ? 127 : 0);
        joystick_status.axes[1] =
            (checkFlag(Axis2Low) ? -127 : 0) +
            (checkFlag(Axis2High) ? 127 : 0);
#endif

    }
    return true;
}
