/** @file   shell.h
    @author William Chen, Troy Tomlins
    @date   7th Oct
    @brief  Shells module header
*/
#ifndef SHELL_H
#define SHELL_H

#include "system.h"
#include "tinygl.h"

#define MAX_SHELLS 5
#define TICK_THRESHOLD 5

// define custom object type "shell"
typedef struct {
    tinygl_point_t pos;
    int move_tick;
    bool active;
} shell_t;

// creates a shell
void create_shell(int8_t x);

// draws_shells
void draw_shells(void);

// move_shells and deactivates if they go off the ledmat
void move_shells(void);



#endif
