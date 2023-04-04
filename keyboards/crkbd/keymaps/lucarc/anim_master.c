#include "oled_utils.h"
#include "anim_frames.c"
/* KEYBOARD PET START */



/* 32 * 14 os logos */
static const char PROGMEM windows_logo[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbc, 0xbc, 0xbe, 0xbe, 0x00, 0xbe, 0xbe, 0xbf, 0xbf, 0xbf, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x0f, 0x0f, 0x00, 0x0f, 0x0f, 0x1f, 0x1f, 0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const char PROGMEM mac_logo[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf0, 0xf8, 0xf8, 0xf8, 0xf0, 0xf6, 0xfb, 0xfb, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x0f, 0x1f, 0x1f, 0x0f, 0x0f, 0x1f, 0x1f, 0x0f, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

/* Smart Backspace Delete */

bool shift_held = false;

/* timers */
uint32_t anim_timer_ = 0;

/* current frame */
uint8_t current_frame = 0;

/* status variables */
int   current_wpm = 0;
led_t led_usb_state;

bool isSneaking = false;
bool isJumping  = false;
bool showedJump = true;

/* logic */
static void render_capy(int X, int Y) {
    /* Sit */

    static const char* sit [] = {
        ANIM_FRAME_0,
        ANIM_FRAME_0,
        ANIM_FRAME_0,
        ANIM_FRAME_0,
        ANIM_FRAME_0,
        ANIM_FRAME_1,
        ANIM_FRAME_2,    
        ANIM_FRAME_3,
        ANIM_FRAME_4        
        };
        
        /* jump */
        if (isJumping || !showedJump) {
            /* clear */
            oled_set_cursor(X, Y + 2);
            oled_write("     ", false);

            oled_set_cursor(X, Y - 1);

            showedJump = true;
        } else {
            /* clear */
            oled_set_cursor(X, Y - 1);
            oled_write("     ", false);

            oled_set_cursor(X, Y);
        }
    void animate_capy(void) {
        /* switch frame */
        current_frame = (current_frame + 1) % 9;
        const char* frame = sit[current_frame];

        /* animation */
        oled_write_raw_P(frame, ANIM_SIZE);
    }

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
        animate_capy();
    }
}

/* KEYBOARD PET END */
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

static void render_master_side(char* wpm_str, char* current_layer) { 
    
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
    render_capy(0, 13);

    /* KEYBOARD PET RENDER END */
}
