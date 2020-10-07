/** @file   player.c
    @author Troy Tomlins
    @date   7th Oct
    @brief  Player module
*/

#include "tinygl.h"


/** define player */
typedef struct
{
    tinygl_point_t pos;
} player_t;


static player_t player = {{2,6}};


/** Display's Player's location */
void draw_player(void){
    tinygl_draw_point(player.pos, 1);
}

// returns player's x position
int8_t get_player_pos(void){
	return player.pos.x;
}

/** Updates Player's location */
void update_player(int inc){
	// changes player x position by inc
	// un-draws player prior to moving
	// re-drawing unnecessary due to draw task is main game loop
    if ((inc == 1) && (player.pos.x != 4))
    {
        tinygl_draw_point(player.pos, 0);
        player.pos.x += inc;
    }
    else if ((inc == -1) && (player.pos.x != 0))
    {
        tinygl_draw_point(player.pos, 0);
        player.pos.x += inc;
    }
}


