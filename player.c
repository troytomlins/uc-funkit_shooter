/** @file   player.c
    @authors Troy Tomlins, William Chen // # Ids: wch99, tpt38, 47994832, 53494295
    @date   7th Oct
    @brief  Player module, responsible for storing, changing, and displaying
    information on the player
*/

#include "tinygl.h"
#include "navswitch.h"

#include "shoot.h"
#include "player.h"

static player_t player; // Default player start pos

// inits player by setting it to the start position
void init_player(void)
{
    tinygl_point_t start = PLAYER_START_POS;
    player.pos = start;
}

/** Updates Player's location by changing its x position*/
static void move_player(int8_t inc)
{
    // changes player x position by inc
    // un-draws player prior to moving
    // re-drawing unnecessary due to draw task is main game loop
    tinygl_draw_point(player.pos, 0);

    // note that an extra 5 is added to pos.x to ensure it is positive
    // after modulo-ing it. This also allows the player to jump from the 
    // far left to the far right by "moving off" the ledmat
    player.pos.x = (player.pos.x + 5+ inc) % 5;
}

/** Returns player position */
tinygl_point_t get_player_pos(void)
{
    return player.pos;
}

/** checks for any player input and processes it. */
void take_input(void)
{
    navswitch_update();
    // Checks position change, then changes player by the direction moved.
    // Or shoots if the navstick is pushed
    if (navswitch_push_event_p (NAVSWITCH_EAST)) {
        move_player(1);
    } else if (navswitch_push_event_p(NAVSWITCH_WEST)) {
        move_player(-1);
    } else if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
        start_shot(player.pos.x);
    }
}


/** Display's Player's location */
void draw_player(void)
{
    tinygl_draw_point(player.pos, 1);
}





