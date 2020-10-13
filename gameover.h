/** @file   gameover.h
    @author Troy Tomlins, William Chen
    @date   11th Oct
    @brief  Game Over module header
*/

#ifndef GAMEOVER_H
#define GAMEOVER_H

/* Message Rates and Text */
#define WIN_TEXT " YOU WON BY "
#define LOSE_TEXT " YOU LOSE"

/* Game over code */
#define SAFETY_WAIT_LOOPS 5


// Stops game and displays game over
void game_over(uint8_t state);



#endif
