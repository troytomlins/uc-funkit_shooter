/** @file   player.c
    @authors Troy Tomlins, William Chen
    @date   8th Oct
    @brief  Core game module. Responsible for initialising the game, and starting the
    tasks scheduler.
*/

#include "system.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "shoot.h"
#include "player.h"
#include "task.h"
#include "navswitch.h"
#include "shells.h"
#include "led.h"
#include "readyup.h"
#include "button.h"
#include "gameover.h"
#include "game.h"
#include "lives.h"

/** cleans an ir input to make sure it is valid (prevents invalid ir inputs)
    a safety precaution against crashes. */
static bool clean_ir(int8_t in)
{
    if(in >= 0 && in <= 4) {
        return true;
    } else {
        return false;
    }
}

/** Initializes all the systems needed for the game */
static void game_init(void)
{
    system_init ();
    navswitch_init();
    tinygl_init(DISPLAY_RATE);
    ir_uart_init();
    button_init();
    init_player()
    set_lives(); // Sets default number of lives
}


/** This task processes inputs from player and ir */
static void process_input(__unused__ void *data)
{
    take_input(); // processes any player input

    // Checks for incoming shot from opponent
    if (ir_uart_read_ready_p()) {
        int8_t incoming = ir_uart_getc();
        if (incoming==OVER_CODE) // Game over win
        {
            game_over(1); // 1 indictates win
        }
        else if(clean_ir(incoming)) // incoming shot
        {
            // only create the shell if the shot is valid
            create_shell(incoming);
        }
    }
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
