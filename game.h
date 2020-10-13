/** @file   game.h
    @author William Chen, Troy Tomlins
    @date   11th Oct
    @brief  header for the main game
*/
#ifndef GAME_H
#define GAME_H

/* Define polling rates for game tasks in Hz.  */
#define GAME_TICK_RATE 200
#define INPUT_RATE 100
#define DISPLAY_RATE 500
#define IR_RATE 100

// initialises the game system
void game_init(void);

// inits only the game_objects
void init_game_objects(void);

// restarts the task scheduler
void re_schedule(void);
#endif
