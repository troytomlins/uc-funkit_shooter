/** @file   shoot.h
    @author Troy Tomlins
    @date   7th Oct
    @brief  Shoot module
*/
#ifndef SHOOT_H
#define SHOOT_H

#include "system.h"
#include "tinygl.h"

void draw_shoot_beam(void);

void start_shot(int8_t shot);

void update_shoot_beam(void);


#endif
