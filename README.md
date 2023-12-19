# BattleShip the Circuit Playground Game

# Author
Jonah Carr

## General Comments
This repository holds code for my ENGR 103 BattleShip game.

## Game Rules: 
1.	The game is very similar to the Battleship board game.
2.	One player will have 5 LED’s (0-4) and a button (Pin #4) on their side of the CPX board while the other player will have the opposite 5 LED’s (5-9) and the opposite button (Pin #5).
3.	When the game starts the first player (button pin #4) will tap his button until the Pixel on his side of the CPX board is in the spot he would like it to be in while the other player faces away. To place a ship, a player will flip the switch.
4.	This process will be repeated until both players have placed two ships.
5.	Then, the light will appear on the opposite side of the board to the first player. The first player will press their button until the pixel LED is in a spot, they believe their opponents ship to be in. Then they will flip the switch. 
6.	Flipping the switch indicates a change of turn.
7.	Once the switch is flipped, lights will light up red to indicate that a ship has been hit, or nothing will happen to indicate that the ship has not been hit. If a ship has already been hit, the same spot will not light up red if it is targeted.
8.	The second player will continue in a similar fashion to the first player and turns will be taken by both players until both ships are hit.
9.	Once both ships are hit, the entire circuit playground board will light up red, and the game will cease to work after a period of 5 seconds.

## Game Inputs and Outputs:
Inputs:
-	One button on each side of the CPX board for each player.
-	One switch to be used by both players to switch turns and start a new game.
Outputs:
-	10 Pixel LED’s
-	Sound Module on CPX Board
