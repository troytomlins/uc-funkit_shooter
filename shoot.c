/** @file   shoot.c
    @author Troy Tomlins, William Chen
    @date   7th Oct
    @brief  Shoot module, responsible for instantiating the shoot beam and
    player firing
*/

#include "tinygl.h"
#include "ir_uart.h"
#include "shells.h"
#include "shoot.h"

#define SHOT_COOLDOWN 5
#define VISUAL_COOLDOWN 1

static int shot_dis = 0; // Shot display timer
static int shot_cd = 0;
static bool shot_on = false;
static bool shot_ready = true;
static int8_t shot_col; // Shot column


// draws the shoot beam
void draw_shoot_beam(void)
{
    if(shot_on) {
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
    if (shot_ready) {
        shot_col = shot;
        shot_on = true;
        shot_ready = false;
        shot_dis = VISUAL_COOLDOWN;
        shot_cd = SHOT_COOLDOWN;
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
    
    // checks if gun has been reloaded
    if(shot_cd == 0){
		shot_ready = true;
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
