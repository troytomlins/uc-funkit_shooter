/** @file   shell.c
    @authors William Chen, Troy Tomlins
    @date   7th Oct
    @brief  Shells module, responsible for instantiating, moving, and deleting shells
*/

#include "tinygl.h"
#include "system.h"
#include "led.h"
#define MAX_SHELLS 5
#define TICK_THRESHOLD 5
// define custom object type "shell"
typedef struct {
    tinygl_point_t pos;
    int move_tick;
    bool active;
} shell_t;

// define custom list for shells
typedef struct {
    shell_t array[MAX_SHELLS];
} shells_list_t;

static shells_list_t shells;

//creates a shell at x coord line
void create_shell(int8_t x)
{
    int i = 0;
    bool created = false;
    //cycles through shells_list until a deactivated shell is found
    while(i < MAX_SHELLS && !created) {
        shell_t* shell = &shells.array[i];
        if(!shell->active == true) {
            shell->pos.x = x;
            shell->pos.y = -1;
            shell->active = true;
            shell->move_tick = 0;
            created = true;
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
    int i;
    //cycle through shells, drawing each one
    for(i=0; i<MAX_SHELLS; i++) {
        shell_t* shell = &shells.array[i];
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
    int i;
    for(i=0; i<MAX_SHELLS; i++) {
        shell_t* shell = &shells.array[i];
        tinygl_draw_point(shell->pos, 0);
        // if the shell is active and TICK_THRESHOLD has been reached, move the shell
        if(shell->active && (shell->move_tick++ == 5)) {
            // note the if statement increments move-tick, regardless of true or false
            shell->pos.y ++;
            shell->move_tick = 0;
            //if shell is off ledmat, deactivate
            if(shell->pos.y > 6) {
                deactivate_shell(shell);
            }
        }
    }
}





