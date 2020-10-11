/** @file   gameover.h
    @author Troy Tomlins
    @date   11th Oct
    @brief  Game Over module header
*/

#ifndef GAMEOVER_H
#define GAMEOVER_H

#define MESSAGE_RATE 30
#define PACER_RATE 200
#define GAME_OVER_TEXT "  GAME OVER"
#define WIN_TEXT "  YOU WIN"
#define LOSE_TEXT "  YOU LOSE"
#define OVER_CODE 9 // arbitrary as long sa it isn't 0,1,2,3,4 or 13

// Stops game and displays game over
void game_over(int state);

#endif
