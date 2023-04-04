#pragma once

//-------- CONFIGURATION START --------
#ifndef FAST_TYPE_WPM
    #define FAST_TYPE_WPM 45 //Switch to fast animation when over words per minute
#endif
//-------- CONFIGURATION END--------

#include "oled_utils.h"


/* logic */
static void render_animation(int X, int Y) {
    /* Sit */

    #if OLED_TIMEOUT > 0
        /* the animation prevents the normal timeout from occuring */
        if (last_input_activity_elapsed() > OLED_TIMEOUT && last_led_activity_elapsed() > OLED_TIMEOUT) {
            oled_off();
            return;
        } else {
            oled_on();
        }
    #endif

    /* animation timer */

    if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
        anim_timer = timer_read32();
    }
}

static void render_slave_side(char* wpm_str, char* current_layer) { 
    
    oled_set_cursor(0,0);
    oled_write("WPM", false);
    oled_set_cursor(0,1);
    oled_write(wpm_str, false);
    
    oled_set_cursor(0,4);
    oled_write("LAYER", false);
    oled_set_cursor(0,5);
    oled_write(current_layer, false);

    /* KEYBOARD PET RENDER START */
    oled_set_cursor(0, 10);
    render_animation(0, 13);

    /* KEYBOARD PET RENDER END */
}