TODO:  (P = Priority, E = Extra)
E- include how many lives were remaining for the winner
E- Tweak fire rate and shell movement to make game more interesting

Setting up:
 - When you start up the game, text will scroll prompting you to begin. Both player must be ready before the game begins
 - Sit opposite your opponent. Both player then set their funkits side by side so that each player's navsticks are on their right. 
 - Doing so should also align the ir emmiters and recievers. 
 - To ready up, each player should press on the non-resetting button

Moving the player:
 - Your player is at the bottom of the screen. Use the navstick to move it left and right.
 - You can loop around from the far right to the left. Eg if you move off the screen on the left, 
	you will re-appear on the right
	
Attacking:
 - Press down on the navstick to shoot at your opponent.
 - A shooting beam will appear on your screen, sending a bullet towards your enemy on their screen.

Getting hit:
 - Contact with a moving shell means you lose a life.
 - You have three lives, losing all lives means you lose the game.

Lives:
 - You have three lives. This is represented through the blue LED. It changes as follows: TO BE IMPLEMENTED
    - 3 lives: With all your lives, the blue LED stays on constantly
    - 2 lives: After getting hit once, the blue LED will start flashing
    - last life: When you are on your final life, the blue LED will turn off
 - When you run out of lives, you lose the game

Game Over:
 - When the game is over, text will scroll telling you if you won or lost and ask if you want to play again.
 - Once both players press ready the game will restart.


CODE INFORMATION
 - IR Comms Codes:
	0-4 = shot sent/received from x xoord 0-4
	13 = player ready 
    9 = game over

 - You can skip the readyup phase by holding the non-resetting button down while loading the game
	Note that by skipping the readyup phase, an opponent may not be able to complete the ready phase if they haven't skipped

MODULES INFO
game: contains the tasks scheduler and is in charge of calling functions from the other modules to run the game
gameover: contains implementations for the gameover screen that runs when a player loses. Also prompts for a restart of the game
lives: keeps track of the player's lives
player: keeps track of the player and processes player inputs
readyup: is ran when the game is loaded. Prompts for players to readyup before main game begins
shells: contains the shells that move towards the player and the functions that manipuate the shells
shoot: contains implementation of the shooting beam 

