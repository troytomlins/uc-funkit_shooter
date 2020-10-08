/** @file   player.c
    @authors Troy Tomlins, William Chen
    @date   7th Oct
    @brief  Player module, responsible for processing player input and 
    moving the player object
*/

#include "tinygl.h"
#include "navswitch.h"
#include "shoot.h"


/** define player */
typedef struct {
    tinygl_point_t pos;
} player_t;


static player_t player = {{2,6}};

/** Updates Player's location */
static void move_player(int inc)
{
    // changes player x position by inc
    // un-draws player prior to moving
    // re-drawing unnecessary due to draw task is main game loop
    if ((inc == 1) && (player.pos.x != 4)) {
        tinygl_draw_point(player.pos, 0);
        player.pos.x += inc;
    } else if ((inc == -1) && (player.pos.x != 0)) {
        tinygl_draw_point(player.pos, 0);
        player.pos.x += inc;
    }
}

// returns player's x position
tinygl_point_t get_player_pos(void)
{
    return player.pos;
}


void take_input(void)
{
    navswitch_update();

    // Checks position change, then changes player by the direction moved
    if (navswitch_push_event_p (1)) {
        move_player(1);
    } else if (navswitch_push_event_p(3)) {
        move_player(-1);
    } else if (navswitch_push_event_p (4)) {
        start_shot(player.pos.x);
    }
}


/** Display's Player's location */
void draw_player(void)
{
    tinygl_draw_point(player.pos, 1);
}





