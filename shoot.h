/** @file   shoot.h
    @author Troy Tomlins, William Chen
    @date   7th Oct
    @brief  Shoot module header
*/
#ifndef SHOOT_H
#define SHOOT_H

/* Defines cooldown times */
#define SHOT_COOLDOWN 50
#define VISUAL_COOLDOWN 10
// inits the shots module
void init_shots(void);

// draws the shooting beam
void draw_shoot_beam(void);

// creates a shooting beam at given x coord
void start_shot(int8_t shot);

// updates the shoot beam
void update_shoot_beam(void);


#endif
