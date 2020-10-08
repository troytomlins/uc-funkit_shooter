/** @file   shell.h
    @author William Chen, Troy Tomlins
    @date   7th Oct
    @brief  Shells module header
*/
#ifndef SHELL_H
#define SHELL_H

#include "system.h"
#include "tinygl.h"

// creates a shell
void create_shell(int8_t x);

// draws_shells
void draw_shells(void);

// move_shells and deactivates if they go off the ledmat
void move_shells(void);



#endif
