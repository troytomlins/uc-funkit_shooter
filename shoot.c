/** @file   shoot.c
    @author Troy Tomlins
    @date   7th Oct
    @brief  Shoot module
*/

#include "tinygl.h"
#include "ir_uart.h"


static int shot_cd = 0; // Shot cooldown timer
static int shot_dis = 0; // Shot display timer
static bool shot_on = false; 
static int8_t shot_col; // Shot column

// draws the shoot beam
void draw_shoot_beam(void)
{
    if(shot_on){
		tinygl_point_t pos1 = {shot_col,0};
		tinygl_point_t pos2 = {shot_col,6};
		tinygl_draw_line(pos1, pos2, 1);
	} else {
		tinygl_point_t pos1 = {shot_col,0};
		tinygl_point_t pos2 = {shot_col,6};
		tinygl_draw_line(pos1, pos2, 0);
	}
}

// instantiates a shot
void start_shot(int8_t shot)
{
    if (shot_cd == 0) {
        shot_col = shot;
		shot_on = true;
        shot_dis = 1;
        shot_cd = 1;
        ir_uart_putc(shot_col); // Sends to other player
    }
}

// updates the shoot_beam information
void update_shoot_beam(void)
{
    // Checks if shot needs removed from screen
    if (shot_dis == 0) {
        shot_on = false;
    }

    // Checks if shot is still being displayed
    if (shot_dis > 0) {
        shot_dis--;
    }

    // Lowers shot cooldown
    if (shot_cd > 0) {
        shot_cd--;
    }
}
