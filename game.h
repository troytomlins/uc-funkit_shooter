/** @file   game.h
    @author William Chen, Troy Tomlins // # Ids: wch99, tpt38, 47994832, 53494295
    @date   11th Oct
    @brief  header for the main game
*/
#ifndef GAME_H
#define GAME_H

/* Define polling rates for game tasks in Hz.  */
#define GAME_TICK_RATE 200
#define INPUT_RATE 200
#define DISPLAY_RATE 600
#define IR_RATE 200

// initialises the game system
void game_init(void);

// inits only the game_objects
void init_game_objects(void);

// restarts the task scheduler
void re_schedule(void);
#endif
