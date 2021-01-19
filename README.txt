Project description
Kevin Luo
Description: 

	The game board was represented as a 2D int array, with the initial state as value of the elements. The game starts up by asking user for their initial position and trap them until a valid position is given, then the AI will choose its starting point accordingly. After that, the user will be prompt to make their nexrt move, and the AI will make its move after user. The AI's movement algorithm is to chase for 3s first, then go close to the player if there's enough safe space around the player. If not, a random, vallid 2 will be selected. If there are no reachable, safe 2s, the AI will move to a nearby valid point with the most movement options around it. After each move by each player, their score will be stored in a 1D array dedicated to the player. Such a process repeats until both of the players have no where left to go. Finally, the score of both players will be printed in the required format, and the winner will be decided accordingly. 

                               
video demo link: 

https://drive.google.com/file/d/1WU0xvIHCHZiftNyOlLPoH9_ybd9pemwJ/view?usp=sharing
