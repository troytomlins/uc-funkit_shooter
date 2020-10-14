/** @file   shell.h
    @author William Chen, Troy Tomlins // # Ids: wch99, tpt38, 47994832, 53494295
    @date   7th Oct
    @brief  Shells module header
*/
#ifndef SHELL_H
#define SHELL_H

#include "tinygl.h"

#define MAX_SHELLS 15 // Max number of shells
#define TICK_TO_MOVE 8 // amount of game ticks needed to make a shell move

/** define custom object type "shell" */
typedef struct {
    tinygl_point_t pos;
    uint8_t move_tick;
    bool active;
} shell_t;

// inits shells by deactivating all of them
void init_shells(void);

// creates a shell at x coordinate
void create_shell(int8_t x);

// draws_shells
void draw_shells(void);

// move_shells and deactivates them if they go off the ledmat.
// if they go off the ledmat, it also checks to see if they hit the player
void move_shells(void);



#endif
