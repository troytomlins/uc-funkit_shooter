/** @file   lives.c
    @authors Troy Tomlins
    @date   11th Oct
    @brief  Lives Modulo
*/
#include "led.h"
#include "gameover.h"
#include "tinygl.h"
#include "lives.h"
#include "player.h"
#include <stdio.h>

static int lives;
static bool flash_aid = false;
static uint8_t flash_ticks = 0;

/** Show number of lives */
void show_lives(void)
{
    if (lives==3) { // LED Permanently on
        led_set (LED1, 1);
    }
    if (lives==2) { // LED Flashes
        flash_ticks++;
        if(flash_ticks == FLASH_TICKS) {
			flash_ticks = 0;
            if(flash_aid) {
                led_set (LED1, 1);
            } else {
                led_set (LED1, 0);
            }
            flash_aid = !flash_aid;
        }
    }
    if (lives==1) { // LED Permanently off
        led_set (LED1, 0);
    }
}

/** Returns number of lives remaining */
int get_lives(void){
	return lives;
}

/** Checks if shell_hits player and updates lives */
void check_hit(uint8_t shell_pos)
{
    tinygl_point_t player_pos = get_player_pos();
    if (player_pos.x==shell_pos) {
        if (!(lives==1)) { // checks if lives are remaining
            lives--;
        } else {
            game_over(0); // 0 indictates loss
        }
    }
}

/** Sets lives to default number */
void set_lives(void)
{
    lives = LIVES_NUM;
}
