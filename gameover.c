/** @file   gameover.c
    @authors Troy Tomlins, William Chen
    @date   8th Oct
    @brief  ends game
*/

#include "button.h"
#include "tinygl.h"
#include "pacer.h"
#include "../fonts/font3x5_1.h"
#include "ir_uart.h"
#include "gameover.h"
#include "game.h"
#include "readyup.h"
#include "lives.h"
#include "system.h"

static bool ready;
static bool opponent_ready;

/** Asks if user wants to play again.
 *  Returns true if both players ready
 */
static bool play_again(void)
{
    button_update();
    if (button_down_p(0) && !ready) {
        //if player readies up and isnt already ready, change state to reflect that
        ready = true;
        tinygl_text(READY_TEXT);
        ir_uart_putc(READY_CODE); // Tells opponent that player is ready
    }
    if (ir_uart_read_ready_p() && !opponent_ready) {
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
    return (opponent_ready&&ready);
}

/** Game over.
 * Displays if you won or lost  then asks if you want to play again.
 * If players play again, clears tinygl and resets lives.
 */
void game_over(int state)
{
	tinygl_clear();
	
    ready = false;
    opponent_ready = false;
    bool restart = false;

    if (state == 0) {
        ir_uart_putc(OVER_CODE);
        tinygl_text (LOSE_TEXT);
    } else if (state == 1) {
        tinygl_text (WIN_TEXT);
    }
    while(!restart) {
        pacer_wait ();
        tinygl_update ();
        restart = play_again (); // Returns bool if players want to play again
    }
    tinygl_clear(); // Clears tinygl
    game_init(); // Re sets lives to default
}
