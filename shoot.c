/** @file   shoot.c
    @author Troy Tomlins, William Chen
    @date   7th Oct
    @brief  Shoot module, responsible for instantiating the shoot beam and
    player firing
*/

#include "tinygl.h"
#include "ir_uart.h"
#include "shoot.h"

static int shot_dis = 0; // Shot display timer
static int shot_cd = 0;
static bool shot_on = false; // States whether shot is on screen
static bool shot_ready = true; // States if player can shoot
static int8_t shot_col; // Shot column


/** Draws the shoot beam */
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

/** Mirrors a shot on the x axis.
    Required because players are opposite one another and their funkits are mirrored */
static int8_t mirror_shot(uint8_t shot){
    switch(shot){
        case 0:
            return 4;
        case 1:
            return 3;
        case 2:
            return 2;
        case 3:
            return 1;
    }
    // case 4:
    return 0;
}

/** Instantiates a shot */
void start_shot(int8_t shot)
{
    if (shot_ready) {
        shot_col = shot; // Sets shot column
        shot_on = true;
        shot_ready = false;
        shot_dis = VISUAL_COOLDOWN; // Sets visual cooldown
        shot_cd = SHOT_COOLDOWN; // Sets shot cooldown
        ir_uart_putc(mirror_shot(shot_col)); // Sends to other player
    }
}

/** Updates the shoot_beam information */
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
