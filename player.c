/** @file   player.c
    @authors Troy Tomlins, William Chen
    @date   7th Oct
    @brief  Player module, responsible for storing, changing, and displaying 
    information on the player
*/

#include "tinygl.h"
#include "navswitch.h"
#include "shoot.h"
#include "player.h"

static player_t player = {PLAYER_START_POS};

/** Updates Player's location by changing its x position*/
static void move_player(int inc)
{
    // changes player x position by inc
    // un-draws player prior to moving
    // re-drawing unnecessary due to draw task is main game loop
	tinygl_draw_point(player.pos, 0);
	
	// note that an extra 5 is added to pos.x to ensure it is positive 
	// pos.x is also a signed int, so it can be momentarily negative
	player.pos.x = (player.pos.x + inc + 5) % 5;
}

// returns player's position
tinygl_point_t get_player_pos(void)
{
    return player.pos;
}

// checks for any player input and processes it.
void take_input(void)
{
    navswitch_update();
    // Checks position change, then changes player by the direction moved
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





