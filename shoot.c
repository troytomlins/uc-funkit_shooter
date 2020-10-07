/** @file   shoot.c
    @author Troy Tomlins
    @date   7th Oct
    @brief  Shoot module
*/

#include "tinygl.h"
#include "ir_uart.h"


static int shot_cd = 0; // Shot cooldown timer
static int shot_dis = 0; // Shot display timer
static int8_t shot_col; // Shot column

/** Display / Removes Player's shot */
void shoot(int8_t shot, int i) {

    tinygl_point_t pos1 = {shot,0};
    tinygl_point_t pos2 = {shot,6};
    tinygl_draw_line(pos1, pos2, i);

}

void start_shot(int8_t shot)
{
    if (shot_cd == 0)
    {
        shot_col = shot;
        shot_dis = 1;
        shot_cd = 1;

        shoot(shot_col, 1); // Display's shot

        ir_uart_putc(shot_col); // Sends to other player
    }
}

void update_shoot_beam(void) {

    // Checks if shot needs removed from screen
    if (shot_dis == 1)
    {
        shoot(shot_col, 0);
    }

    // Checks if shot is still being displayed
    if (shot_dis > 0)
    {
        shot_dis--;
    }

    // Lowers shot cooldown
    if (shot_cd > 0)
    {
        shot_cd--;
    }
}
