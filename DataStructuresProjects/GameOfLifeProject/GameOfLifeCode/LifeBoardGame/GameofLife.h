//Copyright 2018 Destin Piagentini, Kevin Yonamine

//The class interface for "GameofLife" class.

#pragma once

enum GameOverCondition { STAGNANT, DEAD };


class GameofLife {

public:

	//Constructors/Destructors
	GameofLife();
	GameofLife(const int&, const int&);
	GameofLife(const GameofLife&); //Copy constructor
	~GameofLife();

	//Overloaded Assignent Operator
	GameofLife& operator = (const GameofLife&);

	//Public functions
	void PrintBoard() const; //Prints the current board.

	bool CheckGameOver(GameOverCondition&) const; //Checks if all cells are dead, thus ending the game.

	void UpdateGame();

	//Accessor function for the TurnCount data member.
	int GetTurnCount() const {

		return TurnCount;

	}

private:

	//Data Members
	int BoardWidth; //Board's width length

	int BoardHeight; //Board's height length

	bool** GameBoard; //Two-Dimensional array that will become the game's board.

	int** AdjacentCellsGrid; //Two-DeimensionalArray that will "snapshot" the cells adjacent cell count at the beginning of a turn before changes are made.

	int TurnCount; //Keeps track of how many turns have passed.

	bool GameChanged; //Keeps track of whether the game is stagnot or not. If no changes between rounds then game is over.

	//Helper Functions

	int CountAdjacentCells(const int&, const int&) const; //Counts adjcent cells to any given location.

	void UpdateAdjacentCellsGrid(); //Updates the adjacent count 2-D array to reflect new changes.

	void PrintAdjacentCellsGrid() const; //Prints the AdjacentCellsGrid. **FOR DEBUGGING PURPOSES**

};
