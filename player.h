
/** @file   player.h
    @author Troy Tomlins
    @date   7th Oct
    @brief  Player module
*/
#ifndef PLAYER_H
#define PLAYER_H

#include "system.h"
#include "tinygl.h"

int8_t get_player_pos(void);

void update_player(int inc);

void draw_player(void);



#endif
