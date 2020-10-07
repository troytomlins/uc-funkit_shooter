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
#define GAME_TICK_RATE 2
#define DISPLAY_RATE 250

static int8_t player_pos;
static int8_t inc_shot;

static void game_init(void){
    create_shell(1);
}

void update_game(__unused__ void *data){
    move_shells();

    pio_output_high(LEDMAT_ROW7_PIO);
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
        inc_shot = ir_uart_getc();
        tinygl_point_t inc_pos = {inc_shot, 0};
        tinygl_draw_point(inc_pos, 1);
    }
}

void update_display(__unused__ void *data){
    tinygl_update();
    draw_player();
}

int main (void)
{
    // Initilize
    system_init ();
    navswitch_init();
    game_init();
    display_init();
    pacer_init (500);
    tinygl_init(500);
    ir_uart_init();

    task_t tasks[] =
    {
        {.func = update_game, .period = TASK_RATE / GAME_TICK_RATE,
         .data = 0},
        {.func = update_display, .period = TASK_RATE / DISPLAY_RATE,
         .data = 0}
    };

    task_schedule (tasks, ARRAY_SIZE (tasks));

    return 0;
}
