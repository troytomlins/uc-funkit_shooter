
/** @file   player.h
    @author Troy Tomlins, William Chen
    @date   7th Oct
    @brief  Player module header
*/
#ifndef PLAYER_H
#define PLAYER_H

#include "system.h"
#include "tinygl.h"

// processes any navswitch inputs
void take_input(void);

// returns the player's posititon
tinygl_point_t get_player_pos(void);

// draws the player
void draw_player(void);



#endif
