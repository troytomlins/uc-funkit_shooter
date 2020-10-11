
/** @file   player.h
    @author Troy Tomlins, William Chen
    @date   7th Oct
    @brief  Player module header
*/
#ifndef PLAYER_H
#define PLAYER_H

#include "tinygl.h"

#define PLAYER_START_POS {2,6} // Player start pos

/** define player */
typedef struct {
    tinygl_point_t pos;
} player_t;

// places player at player start position
void init_player(void)

// processes any navswitch inputs
void take_input(void);

// returns the player's posititon
tinygl_point_t get_player_pos(void);

// draws the player
void draw_player(void);



#endif
