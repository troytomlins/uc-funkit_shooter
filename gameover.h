/** @file   gameover.h
    @author Troy Tomlins, William Chen
    @date   11th Oct
    @brief  Game Over module header
*/

#ifndef GAMEOVER_H
#define GAMEOVER_H

/* Message Rates and Text */
#define WIN_TEXT " YOU WIN"
#define LOSE_TEXT " YOU LOSE"

/* Game over code */
#define OVER_CODE 9 // arbitrary as long sa it isn't 0,1,2,3,4 or 13


// Stops game and displays game over
void game_over(int state);

#endif
