/** @file   shell.c
    @authors William Chen, Troy Tomlins
    @date   7th Oct
    @brief  Shells module, responsible for instantiating, moving, and deleting shells
*/

#include "tinygl.h"
#include "shells.h"
#include "lives.h"

static shell_t shells[MAX_SHELLS];

//creates a shell at x coord line
void create_shell(int8_t x)
{
    uint8_t i = 0;
    bool created = false;
    //cycles through shells_list until a deactivated shell is found
    while(i < MAX_SHELLS && !created) {
        shell_t* shell = &(shells[i]);
        if(!shell->active) {
            created = true;
            shell->pos.x = x;
            shell->pos.y = -1;
            shell->active = true;
            shell->move_tick = 0;
        } else {
            i++;
        }
    }
    //if we reach here, we've hit max bullets
}

//deactivates a shell
static void deactivate_shell(shell_t* shell)
{
    shell->active = false;
}

// draws all shells
void draw_shells(void)
{
    uint8_t i;
    //cycle through shells, drawing each one
    for(i=0; i<MAX_SHELLS; i++) {
        shell_t* shell = &(shells[i]);
        //only draw if shell is active
        if(shell->active) {
            tinygl_draw_point(shell->pos, 1);
        }
    }
}

//moves all active shells and deactivates shells if they go off the ledmat
void move_shells(void)
{
    //cycle through shells, moving each one
    uint8_t i;
    for(i=0; i<MAX_SHELLS; i++) {
        shell_t* shell = &(shells[i]);
        tinygl_draw_point(shell->pos, 0);
        // if the shell is active and TICK_THRESHOLD has been reached, move the shell
        if(shell->active && (shell->move_tick++ == TICK_TO_MOVE)) {
            // note the if statement increments move-tick, regardless of true or false
            shell->pos.y ++;
            shell->move_tick = 0;
            //if shell is off ledmat, deactivate
            if(shell->pos.y > 6) {
                check_hit(shell->pos.x);
                deactivate_shell(shell);
            }
        }
    }
}





