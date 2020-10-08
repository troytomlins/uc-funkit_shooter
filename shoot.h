/** @file   shoot.h
    @author Troy Tomlins, William Chen
    @date   7th Oct
    @brief  Shoot module header
*/
#ifndef SHOOT_H
#define SHOOT_H

#include "system.h"
#include "tinygl.h"

// FORCES PLAYER TO SHOOT AT THEMSELVES
// TEST CODE REMOVE LATER
void test_shot(int8_t x);


// draws the shooting beam
void draw_shoot_beam(void);

// creates a shooting beam at given x coord
void start_shot(int8_t shot);

// updates the shoot beam
void update_shoot_beam(void);


#endif
