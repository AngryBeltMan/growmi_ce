#ifndef INPUT_H
#define INPUT_H
#include <keypadc.h>

typedef enum {
    InputClear,
    InputUp,
    InputDown,
    InputLeft,
    InputRight,
    Input2nd,
    InputAlpha,
    InputOther
} KeyInput;

// captures the keys pressed
// only gets keys in the KeyInput enum
// If no keys are pressed or another character is pressed that is not in the input enum it will return InputOther
static inline KeyInput get_input() {
    // scans what keys were pressed
    kb_Scan();
    if (kb_IsDown(kb_Down)) return InputDown;
    if (kb_IsDown(kb_Up)) return InputUp;
    if (kb_IsDown(kb_Left)) return InputLeft;
    if (kb_IsDown(kb_Right)) return InputRight;
    if (kb_IsDown(kb_Clear)) return InputClear;
    if (kb_IsDown(kb_2nd)) return Input2nd;
    if (kb_IsDown(kb_Alpha)) return InputAlpha;
    return InputOther;
}

#endif
