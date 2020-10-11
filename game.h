/** @file   game.h
    @author William Chen, Troy Tomlins
    @date   11th Oct
    @brief  header for the main game
*/
#ifndef GAME_H
#define GAME_H

/* Define polling rates for game tasks in Hz.  */
#define GAME_TICK_RATE 100
#define INPUT_RATE 100
#define DISPLAY_RATE 500

// checks if shell hits
void check_hit(uint8_t shell_pos);

void restart_game(void);

#endif
