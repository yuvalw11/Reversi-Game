/*
 * AIPlayer.cpp
 *
 *  Created on: Nov 23, 2017
 *      Author: ofir
 */

#include "AIPlayer.h"
#include "MiniMaxCell.h"

namespace std {

/**
 * implement make Move for the AI player, according his algorithem to choose a cell,
 * MiniMax.
 */
void makesMove(Board board, char playerSign) {
	// step 1 in pusudo code - finding all possible moves of the AI player
	//vector<Cell> AIPossibleMoves = board.


}

} /* namespace std */

/**
 * This function takes care to parts 2b and 2c in the pesudo code.
 * Gets:
 * vector<Cell> possibleCells - all the possible cells of the enemy in the
 * new board status (to make part 2b).
 * Return the maximum grade the the enemy can to get in the new board status.
 */
MiniMaxCell AIPlayer::getEnemyMinGrade(Board &board, vector<Cell> possibleCells,
		char enemySign) {
	int minGrade = 1000, currentGrade;
	MiniMaxCell maxToReturn(Cell(100, 100), 100); // just for initilize.
	for (unsigned int i = 0; i < possibleCells.size(); i++) {
		Cell currentCell = possibleCells[i];
		currentGrade = getEnemyCurrentGrade(board, currentCell, enemySign);
		if (currentGrade < minGrade) {
			minGrade = currentGrade;
			// update maxGradeCell to the max grade with the current cell
			maxToReturn.replace(currentCell, minGrade);
		}
	}
	return maxToReturn;
}

int AIPlayer::getEnemyCurrentGrade(Board &board, Cell possibleCellToCheck,
		char enemySign) {
	// put the possible cell in the board. Board doesn't change because this
	// method gets & and not a pointer to our current board.
	// +1 because enter to board makes -1 to our values.
	board.enterToBoard(enemySign, possibleCellToCheck.getX() + 1,
			possibleCellToCheck.getY() + 1);
	// now will check what is the grade of the enemy
	int enemyCells = board.howMuchCells(enemySign);
	int AiGrade = board.howMuchCells(playerSign);
	// now, return the grade of the enemy:
	return enemyCells - AiGrade;

}
