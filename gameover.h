/** @file   gameover.h
    @author Troy Tomlins, William Chen
    @date   11th Oct
    @brief  Game Over module header
*/

#ifndef GAMEOVER_H
#define GAMEOVER_H

/* Message Rates and Text */
#define WIN_TEXT " YOU WIN  PRESS TO REPLAY"
#define LOSE_TEXT " YOU LOSE  PRESS TO REPLAY"

/* Game over code */
#define SAFETY_WAIT_LOOPS 200
#define OVER_CODE 9 // arbitrary as long sa it isn't 0,1,2,3,4 or 13
#define CONFIRM_OVER 122
void set_opponent_ready(void);

// Stops game and displays game over
void game_over(uint8_t state);

void confirm_gameover(void);

#endif
