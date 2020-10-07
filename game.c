#include "system.h"
#include "navswitch.h"
#include "pio.h"
#include "pacer.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "shoot.h"
#include "player.h"
#include "task.h"
#include "tinygl.h"
#include "shells.h"
#include "led.h"

/* Define polling rates in Hz.  */
#define GAME_TICK_RATE 10
#define BEAM_TIME 
#define INPUT_RATE 10
#define DISPLAY_RATE 200

static int8_t player_pos;

void process_input(__unused__ void *data){
	//pio_output_high(LEDMAT_ROW7_PIO);
    navswitch_update();

    // Checks position change
    if (navswitch_push_event_p (1))
    {
        update_player(1);
    }

    // Checks position change
    if (navswitch_push_event_p (3))
    {
        update_player(-1);
    }
    // Player shot
    if (navswitch_push_event_p (4))
    {
        player_pos = get_player_pos();
        start_shot(player_pos);
    }
    // Checks inc shot
    if (ir_uart_read_ready_p())
    {
        int8_t incoming_shot = ir_uart_getc();
        create_shell(incoming_shot);
    }
}

void update_game(__unused__ void *data){
	update_shoot_beam();
    move_shells();
}

void update_display(__unused__ void *data){
	draw_shoot_beam();
	draw_shells();
	draw_player();
    tinygl_update();
}

static void game_init(void){
    system_init ();
    navswitch_init();
    display_init();
    tinygl_init(DISPLAY_RATE);
    ir_uart_init();
    create_shell(3);
}


int main (void)
{
    // Initilize
	game_init();
    task_t tasks[] =
    {
		{.func = process_input, .period = TASK_RATE / INPUT_RATE,
         .data = 0},
        {.func = update_game, .period = TASK_RATE / GAME_TICK_RATE,
         .data = 0},
        {.func = update_display, .period = TASK_RATE / DISPLAY_RATE,
         .data = 0}
    };

    task_schedule (tasks, ARRAY_SIZE (tasks));

    return 0;
}
