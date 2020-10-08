/** @file   readyup.c
    @author William Chen
    @date   8th Oct
    @brief  Prompts and waits for players to ready up
*/

#include "system.h"
#include "navswitch.h"
#include "tinygl.h"
#include "pacer.h"
#include "../fonts/font3x5_1.h"
#include "ir_uart.h"
#include "readyup.h"

#define LOOP_RATE 300
#define MESSAGE_RATE 10

// displays and waits until players are ready before allowing game to proceed
void ready_up(void)
{
	// set up tinygl and displays start game message
    tinygl_font_set (&font3x5_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
    tinygl_text ("Press on navstick to start");
    
    // waits for both player and opponent to be ready
    bool ready = false;
    bool opponent_ready = false;
    while(!(ready && opponent_ready)) {
		// note that while waiting for player to be ready,
		// opponent can ready up first
        pacer_wait ();
        tinygl_update ();

        navswitch_update ();

        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
			// if the player readies up, display READY
            ready = true;
			tinygl_text("READY!");
        }

        if (ir_uart_read_ready_p ()) {
			// If recieved input
            uint8_t in;
            in = ir_uart_getc ();

            if(in == 1) {
				// If input is 1, opponent has readied up
                opponent_ready = true;
				tinygl_text("OPPONENT READY!");
            }
        }
    }
    // both players are ready, return to game.c
}

