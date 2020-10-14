/** @file   gameover.c
    @authors Troy Tomlins, William Chen // # Ids: wch99, tpt38, 47994832, 53494295
    @date   8th Oct
    @brief  ends game, displays score for winner, and prompts for a 
    restart
*/
#include <string.h>

#include "system.h"
#include "button.h"
#include "tinygl.h"
#include "pacer.h"
#include "../fonts/font3x5_1.h"
#include "ir_uart.h"
#include "uint8toa.h"

#include "gameover.h"
#include "game.h"
#include "readyup.h"
#include "lives.h"
#include "messenger.h"


static bool ready;
static bool opponent_ready;

/** Asks if user wants to play again.
 *  Returns true if both players ready
 */
static bool play_again(void)
{
    button_update();
    if (button_down_p(0) && !ready) {
        ready = true;

        if(!opponent_ready) {
            // if this kit readied first, it is set as player 1
            init_messenger(true);
        } else {
            init_messenger(false);
        }
        tinygl_text(READY_TEXT);
        ir_uart_putc(READY_CODE); // Tells opponent that player is ready
    }
    if (ir_uart_read_ready_p() && !opponent_ready) {
        uint8_t in;
        in = ir_uart_getc ();

        if(in == READY_CODE) {
            // opponent has readied up
            opponent_ready = true;
            tinygl_text(OPPONENT_READY_TEXT);
        }
    }
    return (opponent_ready && ready);
}

/** Game over.
 * Displays if you won or lost, and a score if you won. 
 * Then asks if you want to play again.
 * If players play again, clears tinygl and resets the task scheduler.
 */
void game_over(uint8_t state)
{
    tinygl_clear();
    tinygl_update(); // updates screen to be clear while the restart loads
    
    ready = false;
    opponent_ready = false;
    bool restart = false;

    if (state == 0) {
        tinygl_text(LOSE_TEXT);
        ir_uart_putc(OVER_CODE); // Tells winner that game is over
        if(!get_sender()) {
            // if player is not the sender, the opponent is.
            // So we need to wait a little to make sure opponent is ready to recieve
            // the gameover message.
            uint8_t i = 0;
            while(i++ != SAFETY_WAIT_LOOPS) {
                pacer_wait();
                continue;
            }
        }
        ir_uart_putc(OVER_CODE); // Tells winner that game is over
    } else if (state == 1) {
		// use buffer to store string, adds remaining lives to the end of the string
		// before displaying.
		char buffer[25];
        char *str = buffer;

        strcpy (str, WIN_TEXT);
        while (*str) {
            str++;
        }
        uint8toa (get_lives(), str, 0);
        while (*str) {
            str++;
        }
        tinygl_clear ();
        tinygl_text (buffer);
    }

    while(!restart) {
        // until both players ready up, prompt for readyness
        pacer_wait ();
        tinygl_update ();
        restart = play_again();
    }
    // clear in prep for restart
    tinygl_clear();
    tinygl_update();
    init_game_objects(); // reset game objects
    re_schedule();
}
