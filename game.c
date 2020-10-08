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
#include "readyup.h"
#include "game.h"

static bool start_game = false;

// cleans an ir input to make sure it is valid (prevents invalid ir inputs)
// a safety precaution against crashes.
static bool clean_ir(int8_t in)
{
    if(in >= 0 && in <= 4) {
        return true;
    } else {
        return false;
    }
}

// inits all the systems needed for the game
static void game_init(void)
{
    system_init ();
    navswitch_init();
    tinygl_init(DISPLAY_RATE);
    ir_uart_init();
}


// this task processes inputs from player and ir
void process_input(__unused__ void *data)
{
    take_input(); // processes any player input

    // Checks for incoming shot from opponent
    if (ir_uart_read_ready_p()) {
        int8_t incoming_shot = ir_uart_getc();
        if(clean_ir(incoming_shot)) {
			// only create the shell if the shot is valid
            create_shell(incoming_shot);
        }
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
	led_set(LED1, 1);
    draw_shoot_beam();
    draw_shells();
    draw_player();
    tinygl_update();
}

int main (void)
{
	game_init();
    ready_up();// only proceeds after both players ready up
	
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
