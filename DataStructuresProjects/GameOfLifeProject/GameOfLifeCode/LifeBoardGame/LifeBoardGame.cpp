// Destin Piagentini & Kevin Yonamine
// September 20, 2018
// Professor Ammari - Data Structures
// Fordham University
//Copyright 2018 Destin Piagentini, Kevin Yonamine

// LifeBoardGame.cpp : This file contains the 'main' function. Program execution begins and ends there.


//References
//1: https://stackoverflow.com/questions/42335200/assignment-operator-overloading-returning-void-versus-returning-reference-param

#include <iostream>
#include <cstdlib> //Needed for random generator
#include <ctime> //Needed for rndom generator
#include "GameofLife.h"

int main() {

	srand(time(NULL)); //Seed the random generator.

	GameOverCondition Reason; //Variable for game-over case handling

	int Height, Width; //The variables where the user's input will be loaded into.

	char UserInput; //Will be used to determine whether to continue or quit.

	//Introduction, instructions, and gathering of input:

	std::cout << "Welcome to the game of life!\n\n";

	std::cout << "\nIn this game, a board of 'cells' (the height and width of which are decided by you) will be randomly generated.";
	std::cout << "\nInitially, some cells will be dead and some cells will be alive.";
	std::cout << "\nThe game will keep progressing through rounds aslong as there is at least one cell alive.\n";
	std::cout << "\nEach round, the following rules will be applied:";
	std::cout << "\n\n1. Living cells adjacent to exactly 2 or 3 alive cells will remain unchanged.";
	std::cout << "\n2. Living cells adjacent to less than 2 or more than 3 living cells will die.";
	std::cout << "\n3. Dead cells adjacent to exactly three alive cells will come back to life.";
	std::cout << "\nNote: all births and deaths occur at the same time during a generation.";
	std::cout << "\nNote: On the game's board, 'A' represents an alive cell and 'D' represents a dead cell.\n";

	do {

		std::cout << "\nPlease enter the board dimensions of the game.\n";
		std::cout << "Height: ";
		std::cin >> Height;
		std::cout << "Width: ";
		std::cin >> Width;
		std::cout << "\n";

		GameofLife GameInstance(Height, Width); //Instantiate the game and board with the given input data.

		std::cout << "'A' represents an alive cell, 'D' represents a dead cell.\n";

		std::cout << "Starting board: " << std::endl << std::endl;
		GameInstance.PrintBoard();

		do { //Will keep runing the game until user quits or all cells are dead.

			std::cout << "Press any key followed by 'Enter' to continue, or type 'Q' followed by 'Enter' to quit: ";
			std::cin >> UserInput;

			if (UserInput != 'Q' && UserInput != 'q') { //If the user does not want to exit, we run a turn.

				int TurnCountBeforeTurn = GameInstance.GetTurnCount();
				//Needed to check if the board remained the same so we dont print again.

				GameInstance.UpdateGame(); //Update each turn.


				if (TurnCountBeforeTurn != GameInstance.GetTurnCount()) {
					//If the turn counts are the same, the board hasnt changed (so game over).If the turn counts are different, the game is continuing.

					std::cout << "\nResults After Turn " <<
					GameInstance.GetTurnCount() << ": \n\n";

					GameInstance.PrintBoard(); //Show user updated board.

				} else { //If the game is over due to stagnation, we want to tell the user and show it.

						std::cout << "\n";

					GameInstance.PrintBoard(); //Show the user the board did not change.

						std::cout << "The board did not change.\n"; //Tell the user.

				}
			}

			//No check for Userinput != 'Q' because there should be no change to the board from last turn.
						//If there was a game over last turn, it would've shown last turn.

			if (GameInstance.CheckGameOver(Reason)) { //If game over, print a game - over screen.

					if (Reason == DEAD) {

						std::cout << "Game over! All cells died after " <<
							GameInstance.GetTurnCount() << " turns!\n";

					} else if (Reason == STAGNANT) {

						std::cout << "\nGame over! The board is unchanging from round to round, and no further changes to the board can be made!\n"; //Board does not print so we add line space at beginning to separate from previous line.

					}

			}

		} while (!GameInstance.CheckGameOver(Reason) && (UserInput != 'q' && UserInput != 'Q')); //Repeat until game is over or user quits.

			//Ask to play again.

			std::cout << "\nType 'Y' or 'y' followed by 'Enter' to play again, or any other key and 'Enter' to exit: ";
			std::cin >> UserInput;

	} while (UserInput == 'y' || UserInput == 'Y'); //If the user wants to play again we repeat.

	return 0;

}
