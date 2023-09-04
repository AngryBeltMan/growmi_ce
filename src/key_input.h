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
    //  is the section where the arrow keys are located
    if (kb_Data[7] & kb_Down) return InputDown;
    if (kb_Data[7] & kb_Up) return InputUp;
    if (kb_Data[7] & kb_Left) return InputLeft;
    if (kb_Data[7] & kb_Right) return InputRight;

    if (kb_Data[2] & kb_Alpha) return InputAlpha;
    /* if (kb_Data[7]) { */
    /*     switch (kb_Data[7]) { */
    /*         case kb_Down: { */
    /*                           return InputDown; */
    /*                           break; */
    /*                       } */
    /*         case kb_Up: { */
    /*                         return InputUp; */
    /*                         break; */
    /*                     } */
    /*         case kb_Left: { */
    /*                           return InputLeft; */
    /*                           break; */
    /*                       } */
    /*         case kb_Right: { */
    /*                            return InputRight; */
    /*                            break; */
    /*                        } */
    /*         default: break; */
    /*     } */
    /* } */
    return InputOther;
}

#endif
