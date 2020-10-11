TODO:  (P = Priority, E = Extra)
E- include how many lives were remaining for the winner
E- Have the blue LED show lives remaining (partially implemented)
E- Give the player a certain amount of invulnerability time after getting hit
E- Tweak fire rate and shell movement to make game more interesting

Setting up:
 - When you start up the game, text will scroll prompting you to begin. Both player must be ready before the game begins
 - Sit opposite your opponent. Both player then set their funkits side by side so that each player's navsticks are on their right. 
 - Doing so should also align the ir emmiters and recievers. 

Moving the player:
 - Your player is at the bottom of the screen. Use the navstick to move it left and right.

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
	10 = player ready                                  13???????
    9 = game over

 - You can skip the readyup phase by holding the non-resetting button down while loading the game
	Note that by skipping the readyup phase, an opponent may not be able to complete the ready phase if they haven't skipped
