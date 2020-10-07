/** @file   shoot.h
    @author Troy Tomlins
    @date   7th Oct
    @brief  Shoot module
*/
#ifndef SHOOT_H
#define SHOOT_H

#include "system.h"
#include "tinygl.h"


void start_shot(int8_t shot);

void shoot(int8_t shot, int i);

void shot_update(void);

#endif
