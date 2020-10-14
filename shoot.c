/** @file   shoot.c
    @author Troy Tomlins, William Chen // Ids: wch99, tpt38, 47994832, 53494295
    @date   7th Oct
    @brief  Shoot module, responsible for instantiating the shoot beam and
    player firing
*/

#include "tinygl.h"
#include "shoot.h"
#include "messenger.h"

static uint8_t shot_dis; // Shot display timer
static uint8_t shot_cd;
static bool shot_on; // States whether shot is on screen
static bool shot_ready; // States if player can shoot
static int8_t shot_col; // Shot column

void init_shots(void)
{
    shot_dis = 0;
    shot_cd = 0;
    shot_on = false;
    shot_ready = true;
}

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
static int8_t mirror_shot(int8_t shot)
{
    return(4-shot);
}

/** Instantiates a shot */
void start_shot(int8_t shot)
{
    if (shot_ready) {
        shot_col = shot; // Sets shot column
        add_message(mirror_shot(shot_col)); // Sends to other player using messenger module
        shot_on = true;
        shot_ready = false;
        shot_dis = VISUAL_COOLDOWN; // Sets visual cooldown
        shot_cd = SHOT_COOLDOWN; // Sets shot cooldown
    }
}

/** Updates the shoot_beam information */
void update_shoot_beam(void)
{
    // decrements shot_dis and shot_cd and checks if they've hit 0
    // then turns the shot beam off or reloads.

    if (shot_dis-- == 0) {
        shot_on = false;
    }

    if(shot_cd-- == 0) {
        shot_ready = true;
    }
}
