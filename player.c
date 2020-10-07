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
static void draw_player(void){
    tinygl_draw_point(player.pos, 1);
}

/** Updates Player's location */
static void update_player(int inc){

    if ((inc == 1) && (player.pos.x != 4))
    {
        tinygl_draw_point(player.pos, 0);
        player.pos.x += inc;
        tinygl_draw_point(player.pos, 1);
    }
    else if ((inc == -1) && (player.pos.x != 0))
    {
        tinygl_draw_point(player.pos, 0);
        player.pos.x += inc;
        tinygl_draw_point(player.pos, 1);
    }
}


