
/** @file   shell.c
    @author W Chen
    @date   7th Oct
    @brief  Shells module
*/

#include "tinygl.h"
#include "system.h"
#include "led.h"
#define MAX_SHELLS 5

typedef struct {
    tinygl_point_t pos;
    bool active;
} shell_t;

typedef struct {
    shell_t array[MAX_SHELLS];
} shells_list_t;

static shells_list_t shells;
static int tick_count = 0;

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
            created = true;
        }
    }
    //if we reach here, we've hit max bullets
}

//deactives a shell
static void deactivate_shell(shell_t* shell)
{
    shell->active = false;
}

// draws all shells
static void draw_shells(void)
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
            if(shell->active) {
                shell->pos.y ++;
                //if shell is off ledmat, deactivate
                if(shell->pos.y > 6) {
                    deactivate_shell(shell);
                }
            }
        }
    
    draw_shells();
}





