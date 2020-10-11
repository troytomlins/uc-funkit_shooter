/** @file   gameover.c
    @author Troy Tomlins
    @date   8th Oct
    @brief  ends game
*/

#include "navswitch.h"
#include "tinygl.h"
#include "pacer.h"
#include "../fonts/font3x5_1.h"
#include "ir_uart.h"
#include "gameover.h"

void game_over(int state)
{
    if (state == 0)
    {
        ir_uart_putc(OVER_CODE);
        tinygl_text (LOSE_TEXT);
        while(1)
        {
            pacer_wait ();
            tinygl_update ();
        }
    }
    else if (state == 1)
    {
        tinygl_text (WIN_TEXT);
        while(1)
        {
            pacer_wait ();
            tinygl_update ();
        }
    }
}
