#include "system.h"
#include "task.h"
#include "tinygl.h"
#include "shells.h"
#include "led.h"

/* Define polling rates in Hz.  */
#define GAME_TICK_RATE 2
#define DISPLAY_RATE 250

static void game_init(void){
	create_shell(1);
}

void update_game(__unused__ void *data){
	move_shells();
}

void update_display(__unused__ void *data){
	tinygl_update();
}

int main (void)
{
    task_t tasks[] =
    {
        {.func = update_game, .period = TASK_RATE / GAME_TICK_RATE,
         .data = 0}, 
        {.func = update_display, .period = TASK_RATE / DISPLAY_RATE,
         .data = 0}
    };

    system_init ();
    game_init();
    display_init();

    task_schedule (tasks, ARRAY_SIZE (tasks));
    return 0;
}
