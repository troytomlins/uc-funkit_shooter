/** @file   player.c
    @authors Troy Tomlins, William Chen
    @date   8th Oct
    @brief  Core game module. Responsible for initialising the game, and starting the 
    tasks scheduler.
*/


#include "system.h"
#include "pio.h"
#include "pacer.h"
#include "tinygl.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "shoot.h"
#include "player.h"
#include "task.h"
#include "tinygl.h"
#include "shells.h"
#include "led.h"

/* Define polling rates in Hz.  */
#define GAME_TICK_RATE 10
#define INPUT_RATE 10
#define DISPLAY_RATE 200

// this task processes inputs from player and ir
void process_input(__unused__ void *data)
{
    take_input(); // processes any player input

    // Checks for incoming shot from opponent
    if (ir_uart_read_ready_p()) {
        int8_t incoming_shot = ir_uart_getc();
        create_shell(incoming_shot);
    }
}
// updates the game information
void update_game(__unused__ void *data)
{
    update_shoot_beam();
    move_shells();
}

// updates display to match game information
void update_display(__unused__ void *data)
{
    draw_shoot_beam();
    draw_shells();
    draw_player();
    tinygl_update();
}

// inits all the systems needed for the game
static void game_init(void)
{
    system_init ();
    navswitch_init();
    display_init();
    tinygl_init(DISPLAY_RATE);
    ir_uart_init();
}


int main (void)
{
    game_init();
    task_t tasks[] = {
        {
            .func = process_input, .period = TASK_RATE / INPUT_RATE,
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
