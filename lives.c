/** @file   lives.c
    @authors Troy Tomlins, William Chen // # Ids: wch99, tpt38, 47994832, 53494295
    @date   11th Oct
    @brief  Lives Module. Stores, manipulates, and displays lives
*/
#include "led.h"
#include "tinygl.h"

#include "gameover.h"
#include "lives.h"
#include "player.h"

static uint8_t lives;
static bool flash_on;
static uint8_t flash_ticks;

/** Show number of lives */
void show_lives(void)
{
    if (lives==3) { // LED always on
        led_set (LED1, 1);
    }
    if (lives==2) { // LED Flashes

        // after FLASH_TICKS amount of game ticks, toggle led
        if(flash_ticks++ == FLASH_TICKS) {
            flash_ticks = 0;
            if(flash_on) {
                led_set (LED1, 1);
            } else {
                led_set (LED1, 0);
            }
            flash_on = !flash_on;
        }
    }
    if (lives==1) { // LED always off
        led_set (LED1, 0);
    }
}

/** Returns number of lives remaining */
uint8_t get_lives(void)
{
    return lives;
}

/** Checks if shell_hits player and updates lives */
void check_hit(int8_t shell_pos)
{
    tinygl_point_t player_pos = get_player_pos();
    if (player_pos.x == shell_pos) {
        lives--;
        if (lives == 0) { // reduce lives FIRST, then check if player is out of lives
            game_over(0); // input 0 indictates loss
        }
    }
}

/** Inits lives to default number */
void init_lives(void)
{
    lives = LIVES_NUM;
    flash_on = false;
    flash_ticks = 0;
}
