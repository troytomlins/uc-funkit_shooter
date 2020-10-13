/** @file   readyup.c
    @author William Chen, Troy Tomlins
    @date   8th Oct
    @brief  Prompts and waits for players to ready up
*/

#include "tinygl.h"
#include "pacer.h"
#include "../fonts/font3x5_1.h"
#include "ir_uart.h"
#include "button.h"

#include "readyup.h"
#include "messenger.h"

static bool ready;
static bool opponent_ready;

/** displays and waits until players are ready before allowing game to proceed */
void ready_up(void)
{
    // set up tinygl and displays start game message
    tinygl_font_set (&font3x5_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);

    //the extra spaces at the start give a "wrap around" feel to the scrolling
    tinygl_text (START_TEXT);
    pacer_init (PACER_RATE);

    // waits for both player and opponent to be ready
    ready = false;
    opponent_ready = false;
    while(!(ready && opponent_ready)) {
        // note that while waiting for player to be ready,
        // opponent can ready up first
        pacer_wait ();
        tinygl_update ();

        button_update ();

        if (button_down_p(0) && !ready) {
            tinygl_clear();
            //if player readies up and isnt already ready, change state to reflect that
            ready = true;
            if(!opponent_ready){
				// if this kit readied first, it is set as player 1
				init_messenger(true);
			} else {
				init_messenger(false);
			}
            tinygl_text(READY_TEXT);
            ir_uart_putc(READY_CODE); // Tells opponent that player is ready
        }

        if (ir_uart_read_ready_p () && !opponent_ready) {
            tinygl_clear();
            // If recieved ir input and opponent is not ready, check if input is valid
            // then update message state to reflect opponent status
            uint8_t in;
            in = ir_uart_getc ();

            if(in == READY_CODE) {
                // If input is 1, opponent has readied up
                opponent_ready = true;
                tinygl_text(OPPONENT_READY_TEXT);
            }
        }
    }

    // both players are ready, clear display and let the game run
    tinygl_clear();
}

