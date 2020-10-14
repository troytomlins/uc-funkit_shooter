/** @file   game.c
    @authors Troy Tomlins, William Chen // # Ids: wch99, tpt38, 47994832, 53494295
    @date   8th Oct
    @brief  Core game module. Responsible for initialising the game,
    declaring and starting the
    tasks scheduler.
*/

#include "system.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "task.h"
#include "navswitch.h"
#include "button.h"

#include "readyup.h"
#include "gameover.h"
#include "game.h"
#include "lives.h"
#include "shells.h"
#include "shoot.h"
#include "player.h"
#include "shells.h"
#include "messenger.h"



// initialises all game objects except the messenger
// the messenger is initialised by readyup due to needing to know who
// player1 is
void init_game_objects(void)
{
    init_player();
    init_lives();
    init_shots();
    init_shells();
}

/** Initializes all the systems needed for the game */
void game_init(void)
{
    system_init ();
    navswitch_init();
    tinygl_init(DISPLAY_RATE); //includes display_init()
    ir_uart_init(); //includes timer0_init
    button_init();

    init_game_objects();
}


/** This task processes inputs from player and ir */
static void process_input(__unused__ void *data)
{
    take_input(); // processes any player input
}

/** Updates the game information */
static void update_game(__unused__ void *data)
{
    update_shoot_beam();
    move_shells();
}

/** Updates display to match game information */
static void update_display(__unused__ void *data)
{
    draw_shoot_beam();
    draw_shells();
    draw_player();
    tinygl_update();
    show_lives();
}


/** Does an ir task, either send or receive */
static void ir_task(__unused__ void *data)
{
    do_messages();
}

void re_schedule(void)
{
    task_t tasks[] = {
        {
            .func = process_input, .period = TASK_RATE / INPUT_RATE,
            .data = 0
        },
        {
            .func = ir_task, .period = TASK_RATE / IR_RATE,
            .data = 0
        },
        {
            .func = update_game, .period = TASK_RATE / GAME_TICK_RATE,
            .data = 0
        },
        {
            .func = update_display, .period = TASK_RATE / DISPLAY_RATE,
            .data = 0
        }
    };

    task_schedule (tasks, ARRAY_SIZE (tasks));
}

/** Main function of game */
int main (void)
{
    game_init();
    button_update();
    // Hold down the button to skip the readyup phase
    // This is for testing purposes
    if(!button_down_p(0)) {
        ready_up();
    }
    task_t tasks[] = {
        {
            .func = process_input, .period = TASK_RATE / INPUT_RATE,
            .data = 0
        },
        {
            .func = ir_task, .period = TASK_RATE / IR_RATE,
            .data = 0
        },
        {
            .func = update_game, .period = TASK_RATE / GAME_TICK_RATE,
            .data = 0
        },
        {
            .func = update_display, .period = TASK_RATE / DISPLAY_RATE,
            .data = 0
        }
    };

    task_schedule (tasks, ARRAY_SIZE (tasks));

    return 0;
}
