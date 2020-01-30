//Copyright 2018 Destin Piagentini, Kevin Yonamine

//The class implementation for the "GameofLife" class.

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "GameofLife.h"


//Default constructor. If there are no parameters given.
GameofLife::GameofLife() {

	BoardHeight = 12; //General, default board dimensions.
	BoardWidth = 12;

	GameBoard = new bool* [BoardHeight]; //Dynamic allocation of the first dimension of the array.

	AdjacentCellsGrid = new int* [BoardHeight]; //We dont need extra space for the outside rows here.

	for (int i = 0; i < BoardHeight; i++) {

		GameBoard[i] = new bool[BoardWidth]; //Dynamic allocation of the second dimension of the array, creating the columns for each row.

		AdjacentCellsGrid[i] = new int[BoardWidth]; //We dont need extra space for the outside rows here.

		for (int j = 0; j < BoardWidth; j++) { //We can start to fill the newly created columns with values. We need to wait before we start counting adjacent cells.

			if (i == 0 || i == BoardHeight - 1 || j == 0 || j == BoardWidth - 1) { //If the cell in question is on the outside of the user's requested dimensions (if in the empty rows/columns surrounding the game board).

				GameBoard[i][j] = false;
				AdjacentCellsGrid[i][j] = 0; //Fill outside with a 0 count of adjacent cells.

			} else {

				GameBoard[i][j] = (rand() % 2); //Initialized to random 0/1, which is false/true for a boolean.

			}

		}

	}

	//Do not need to update AdjacentCellsGrid as the UpdateGame function will do this. It would be an extra call for no reason.

	TurnCount = 0; //No turns have started, so TurnCount is zero.
	GameChanged = false; //Initialize to false (no rounds yet).


}

//Constructor that reads in the user's desired height/width dimensions for the board and creates the board in accordance
//int Height: How high the board will be (first dimension of the array).
//int Width: How wide the board will be (AKA how many columns, the second dimension of the array).
GameofLife::GameofLife(const int& Height, const int& Width) {

	BoardHeight = Height + 2; //Set the board's height and width to the user's desired lengths.
	BoardWidth = Width + 2; //Plus 2 for the empty rows around the outside.

	GameBoard = new bool* [BoardHeight]; //Dynamic allocation of the first dimension of the array.
	AdjacentCellsGrid = new int* [BoardHeight]; //We dont need extra space for the outside rows here.


	for (int i = 0; i < BoardHeight; i++) {

		GameBoard[i] = new bool[BoardWidth]; //Dynamic allocation of the second dimension of the array, creating the columns for each row.
		AdjacentCellsGrid[i] = new int[BoardWidth]; //We dont need extra space for the outside rows here.

		for (int j = 0; j < BoardWidth; j++) { //We can start to fill the newly created columns with values. We need to wait before we start counting adjacent cells.

			if (i == 0 || i == BoardHeight - 1 || j == 0 || j == BoardWidth - 1) { //If the cell in question is on the outside of the user's requested dimensions.

				GameBoard[i][j] = false;
				AdjacentCellsGrid[i][j] = 0; //Fill outside with a 0 count of adjacent cells.

			} else {

				GameBoard[i][j] = (rand() % 2); //Initialized to random 0/1, which is false/true for a boolean.

			}

		}

	}

	//Do not need to update AdjacentCellsGrid as the UpdateGame function will do this. It would be an extra call for no reason.

	TurnCount = 0; //No turns have started, so TurnCount is zero.
	GameChanged = false; //Initialize to false (no rounds yet).


}

//Copy Constructor
//Part of the Big Three of C++.
//Needed so, if the copy constructor is used, the "GameBoard" pointer does not point to same address in memory.
//In other words, only values copied.
//const GameofLife & Duplicate: The object who's values will be copied to the new object.

GameofLife::GameofLife(const GameofLife& Duplicate) {

	BoardHeight = Duplicate.BoardHeight; //Copy original object's values.
	BoardWidth = Duplicate.BoardWidth; //Already + 2 from duplicate.

	GameBoard = new bool* [BoardHeight]; //Dynamically allocate first dimension in a location that is not being used, i.e. not the first objects memory location.
	AdjacentCellsGrid = new int* [BoardHeight];

	for (int i = 0; i < BoardHeight; i++) {

		GameBoard[i] = new bool[BoardWidth]; //...Same thing for the second dimension.
		AdjacentCellsGrid[i] = new int[BoardWidth];

		for (int j = 0; j < BoardWidth; j++) {

			GameBoard[i][j] = Duplicate.GameBoard[i][j]; //Since the '[]'s dereference the array, we are copying values here NOT locations.
			AdjacentCellsGrid[i][j] = Duplicate.AdjacentCellsGrid[i][j];

		}

	}

	TurnCount = Duplicate.TurnCount; //Copy the turncount's values.
	GameChanged = Duplicate.GameChanged;


}

//Destructor
//Called when the object goes out of scope.
//We need this to delete the two-dimensional dynamic arrays when we are done with them, and free up the space in memory.

GameofLife::~GameofLife() {

	for (int i = 0; i < BoardHeight; i++) { //First we delete the columns of each row.

		delete[] GameBoard[i];
		delete[] AdjacentCellsGrid[i];

	}

	delete[] GameBoard; //Finally, we delete the rows themselves.
	delete[] AdjacentCellsGrid;

}

//Overloaded assignment operator
//Needed because of the presence of a pointer in the class's interface. (Part of the C++ Big Three).
//const GameofLife & Duplicate: The object who's values will be copied.
GameofLife& GameofLife::operator = (const GameofLife& Duplicate) {

	//First we free up our 2-D arrays so we can reconstruct them.

	for (int i = 0; i < BoardHeight; i++) { //First we delete the columns of each row.

		delete[] GameBoard[i];
		delete[] AdjacentCellsGrid[i];

	}

	delete[] GameBoard; //Finally, we delete the rows themselves.
	delete[] AdjacentCellsGrid;

	BoardHeight = Duplicate.BoardHeight; //Copy original object's values.
	BoardWidth = Duplicate.BoardWidth;

	GameBoard = new bool* [BoardHeight]; //Dynamically allocate first dimension in a location that is not being used, i.e. not the first objects memory location.
	AdjacentCellsGrid = new int* [BoardHeight];

	for (int i = 0; i < BoardHeight; i++) {

		GameBoard[i] = new bool[BoardWidth]; //...Same thing for the second dimension.
		AdjacentCellsGrid[i] = new int[BoardWidth];

		for (int j = 0; j < BoardWidth; j++) {

			GameBoard[i][j] = Duplicate.GameBoard[i][j]; //Since the '[]'s dereference the array, we are copying values here NOT locations.
			AdjacentCellsGrid[i][j] = Duplicate.AdjacentCellsGrid[i][j];

		}

	}

	TurnCount = Duplicate.TurnCount; //Copy the turncount's values.
	GameChanged = Duplicate.GameChanged;


	return *this; //Return a reference to the same object.

}

//A public member function that will be used to print the current game's board to the screen, called in "main".
//Includes typography for readability by the user.
//Const: Is not intended to change any values, just print them.
void GameofLife::PrintBoard() const {

	//All i/j = 1 and BoardHeight/BoardWidth - 1 to account and not print empty rows/columns.

	//Generation of table top border.

	//We should have a two char deficit (on account of the beginning "| "), but the table ends in an invisible space char, so only one "-" is needed to allign everything.
	std::cout << '-';

	for (int j = 1; j < BoardWidth - 1; j++) {

		std::cout << "----"; // D/A char + " | " = four char spaces each run through

	}

	std::cout << '\n'; //Extra line for row start.

	//Now we go down the rows to generate the actual table.

	for (int i = 1; i < BoardHeight - 1; i++) {

		std::cout << "| "; // "| " for table typography.

		for (int j = 1; j < BoardWidth - 1; j++) {

			if (GameBoard[i][j]) { //If this cell's value is "true", print it as 'A' (Alive) for readability.

				std::cout << "A | ";

			} else { //If this cell's value is "false", print it as 'D' (Dead) for readability.

				std::cout << "D | ";

			}
		}

		//We should have a two char deficit (on account of the beginning "| "), but the table ends in an invisible space char, so only one "-" is needed to allign everything.
		std::cout << std::endl << '-';

		for (int j = 1; j < BoardWidth - 1; j++) {

			std::cout << "----"; // D/A char + " | " = four char spaces each run through

		}

		std::cout << '\n'; //Extra line for readability and to seperate each row.

	}

	std::cout << '\n'; //Extra line for readability.

}

//A private member function that will be used to print the current game's adjacent cell count board to the screen, called in "UpdateGame".
//This function exists for debugging purposes only.
//Includes typography for readability by the user.
//Const: Is not intended to change any values, just print them.

void GameofLife::PrintAdjacentCellsGrid() const {

	//Generation of table top border.

	//All i/j = 1 and BoardHeight/BoardWidth - 1 to account and not print empty rows/columns.

	//We should have a two char deficit (on account of the beginning "| "), but the table ends in an invisible space char, so only one "-" is needed to align everything.
	std::cout << '-';

	for (int j = 1; j < BoardWidth - 1; j++) {

		std::cout << "----"; // D/A char + " | " = four char spaces each run through

	}

	std::cout << '\n'; //Extra line for row start.

	for (int i = 1; i < BoardHeight - 1; i++) {

		std::cout << "| "; // "| " for table typography.

		for (int j = 1; j < BoardWidth - 1; j++) {

			std::cout << AdjacentCellsGrid[i][j] << " | "; //Print the adjacent cell count for that cell.

		}

		std::cout << std::endl << '-'; //We should have a two char deficit, but the table ends in an invisible space char, so only one "-" is needed to allign everything.

		for (int j = 1; j < BoardWidth - 1; j++) {

			std::cout << "----"; //number + " | " = four spaces each run

		}

		std::cout << '\n'; //Extra lines for visibility

	}

	std::cout << '\n'; //Extra lines for visibility

}

//This is the function called every "turn" to decide the fates of the cells on the board, and advance the game.
//Handles cases for death and birth (surviving doesn't require any instruction).
//If adjacent count 2 or 3 and alive, that cell survives. If the adjacent count is below 2 or above 3, that cell dies.
//If a dead cell is surrounded by exactly 3 cells (adjacent count = 3), that cell comes back to life.
void GameofLife::UpdateGame() {

	GameChanged = false;

	UpdateAdjacentCellsGrid(); //Take a "snapshot" of the board's adjacent count before we make changes.

	//PrintAdjacentCellsGrid(); //Debugging - User shouldnt see this function run, but useful for debugging and having the program show us its process.

	for (int i = 1; i < BoardHeight - 1; i++) { //Cycle through each cell and decide their fate. Skip empty rows/columns.

		for (int j = 1; j < BoardWidth - 1; j++) {

			//Death
			if ((AdjacentCellsGrid[i][j] > 3 || AdjacentCellsGrid[i][j] < 2) && GameBoard[i][j] == true) { //If alive and adjacent count is more than 3 or less than 2.

				GameBoard[i][j] = false; //Cell dies
				GameChanged = true;


			}

			//Birth
			if (AdjacentCellsGrid[i][j] == 3 && GameBoard[i][j] == false) { //If dead and surrounded by excatly three adjacents.

				GameBoard[i][j] = true; //Cell comes back to life.
				GameChanged = true;


			}

		}

	}

	if (GameChanged) { //If the game has changed at all (and, thus, a new round has passed).

		TurnCount++; //New turn so we update the count.

	}

}

//This is a private Helper function used to count the cells adjacent to a given cell at any given time, and returns that number.
//const int & VertSpot: The row of the inspected cell (who's adjacents will be counted).
//const int & HorzSpot: The column of the inspected cell (who's adjacents will be counted).

int GameofLife::CountAdjacentCells(const int& VertSpot, const int& HorzSpot) const {

	int AdjacentCount = 0; //Variable that will ultimately be returned.

	//Must use temporary variables because we need the originals to compare against for for-loop exit.
	int i, j;

	//Check i and j are valid spots of the array. Cells outlining the edges are considered invalid.

	if (VertSpot >= BoardHeight - 1 || VertSpot < 1 || HorzSpot >= BoardWidth - 1 || HorzSpot < 1) { //Checks to ensure the locations given are valid. If not, returns 0 adjacent cells.

		return 0;

	}

	if (GameBoard[VertSpot][HorzSpot] == false) {

		//To avoid having to check if the cells in the search area are the given cell each time, we simply deduct one to our final total count to account for the given cell.

		//This, however, will only work if the given cell is alive. Therefore we need to count the cell whether its dead or not for this method.

		//Therefore, we count the dead cell before the for-loop to avoid having a comparison each time for the given cell. This reduces total comparisons needed.

		AdjacentCount++;

	}

	//Example: Do not check if j is above the range 

	for (i = VertSpot - 1; i <= VertSpot + 1; i++) { //Cycles through the row above, to the row of, to the row below.

		for (j = HorzSpot - 1; j <= HorzSpot + 1; j++) { //Cycles to the column left of, to the column of, to the column right of.

			//Execution order:
			//Upper left cell, cell above, upper right cell
			//Cell left of, same cell (which is ignored), cell right of
			//Lower left cell, cell below, lower right cell

			//Do not need to check for valid locations due to outside cells.

			if (GameBoard[i][j] == true) { //Checks to make sure the cell is alive. Will count given cell, but we reduce by 1 at the end to negate this.

				AdjacentCount++; //If alive and not the given cell, we have an adjacent!

			}


		}

	}

	return AdjacentCount - 1; //Return the accumulated count.

}

//This is a private helper function used to update the AdjacentCellsGrid, which records the number of cells adjacent to any given cell at any given instance.
//The 2-D array stores the number in a table where the actual cell is for practicality. AKA this table is a mirror of the board with numbers for each cell's adjacents.

void GameofLife::UpdateAdjacentCellsGrid() {

	for (int i = 1; i < BoardHeight - 1; i++) { //Cycle through all cells except those on the outside.

		for (int j = 1; j < BoardWidth - 1; j++) {

			AdjacentCellsGrid[i][j] = CountAdjacentCells(i, j); //Uses the CountAdjacaentCell helper function to get an accurate count.

		}

	}

}

//This function will scan the board for any alive cells.
//If all are dead, there is no possible way for the game to continue.
//This is called in "main" to know when to stop the game.

bool GameofLife::CheckGameOver(GameOverCondition& Reason) const {

	bool AllDead = true; //This will only be changed if we find an alive cell. If this does not change, we know all cells are dead.

	if (GameChanged == false) { //If the game hasn't changed we know 

		Reason = STAGNANT;

		return true;

	} else {

		for (int i = 1; i < BoardHeight - 1; i++) { //Skip outside columns/rows.

			for (int j = 1; j < BoardWidth - 1; j++) {

				if (GameBoard[i][j] == true) { //If we find that one cell is still alive.

					AllDead = false;
					Reason = DEAD;

					//Skip to the end of the loops. No more calculations. We only need one counterexample.

					j = BoardWidth;
					i = BoardHeight;

				}

			}

		}

	}

	return AllDead; //If we get this far, we know the game’s changed. So we return whether all cells are dead or not.

}
