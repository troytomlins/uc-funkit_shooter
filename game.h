/** @file   game.h
    @author William Chen, Troy Tomlins
    @date   8th Oct
    @brief  header for the main game
*/
#ifndef GAME_H
#define GAME_H

/* Define polling rates for game tasks in Hz.  */
#define GAME_TICK_RATE 10 // game world updates every 100 ms
#define INPUT_RATE 10 // gives a max 100ms input delay, insanely hard to notice
#define DISPLAY_RATE 200
#endif
