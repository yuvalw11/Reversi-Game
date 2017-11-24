/*
 * AIPlayer.cpp
 *
 *  Created on: Nov 23, 2017
 *      Author: ofir
 */

#include "AIPlayer.h"

namespace std {

/**
 * implement make Move for the AI player, according his algorithem to choose a cell,
 * MiniMax.
 */
void AIPlayer::makesM(Board *board, char playerSign) {
	MiniMaxCell AINextMove = AIPlayer::returnNextMove(*board, playerSign);
	// now put the move that was choosen by our mini-max algorithem,
	// into our REAL Board.
	Cell c = AINextMove.getCellToPut();
	board->enterToBoard(playerSign, c.getX() + 1, c.getY() + 1);
	cout << "AI Played: (" << c.getX() + 1 << ", " << c.getY() + 1 << ")"<<endl;
}

/**
 * This function takes care to parts 2b and 2c in the pesudo code.
 * Gets:
 * vector<Cell> possibleCells - all the possible cells of the enemy in the
 * new board status (to make part 2b).
 * Return the maximum grade the the enemy can to get in the new board status.
 */
MiniMaxCell AIPlayer::getEnemyCurrentMaxGrade(Board &board,
		vector<Cell> enemyPossibleCells, char enemySign) {
	int maxGrade = 1000, currentGrade;
	MiniMaxCell maxToReturn(Cell(-1, -1), -1); // just for initilize.
	for (unsigned int i = 0; i < enemyPossibleCells.size(); i++) {
		Cell currentCell = enemyPossibleCells[i];
		currentGrade = getEnemyCurrentGrade(board, currentCell, enemySign);
		if (currentGrade < maxGrade) {
			maxGrade = currentGrade;
			// update maxGradeCell to the max grade with the current cell
			maxToReturn.replace(currentCell, maxGrade);
		}
	}
	return maxToReturn;
}

/**
 *  put the possible cell in the board. Board doesn't change because this
 *  method gets (&) of the fake board (that changed) and not a pointer to our real board.
 *  now will check what is the grade of the enemy and returns this grade.
 */
int AIPlayer::getEnemyCurrentGrade(Board &board, Cell possibleCellToCheck,
		char enemySign) {

	int enemyCells = board.howMuchCells(enemySign);
	char AIPlayerSign = Cell::returnOtherSign(enemySign);
	int AiGrade = board.howMuchCells(AIPlayerSign);
	// now, return the grade of the enemy:
	return enemyCells - AiGrade;

}

MiniMaxCell AIPlayer::returnNextMove(Board& board, char playerSign) {
	int lowestGrade = 1000;
		char enemySign = Cell::returnOtherSign(playerSign);
		MiniMaxCell lowestGradeToReturn, currentCellAndGrade;

		// step 1 in pusudo code - finding all possible moves of the AI player
		vector<Cell> AIPossibleMoves = board.possibleCellsToAssign(playerSign);
		// for each possible moves of the AI player:
		for (unsigned int i = 0; i < AIPossibleMoves.size(); i++) {
			// part 2a, make the move in the memory (without any real change) but update the "fake" board.
			Board fakeBoard = board.copyConstructor(board);
			// +1 because enterToBoard makes -1 to the inputs.
			fakeBoard.enterToBoard(playerSign, AIPossibleMoves[i].getX(), // +1 REMOVED
					AIPossibleMoves[i].getY());

			// Part 2b: checks the possibles moves of the enemy (not the AI player)
			// after the cell we added to fakeBoard
			vector<Cell> enemyPossibleMoves = fakeBoard.possibleCellsToAssign(
					enemySign);
			currentCellAndGrade.replace(
					AIPlayer::getEnemyCurrentMaxGrade(fakeBoard, enemyPossibleMoves,
							enemySign));
			if (currentCellAndGrade.getGradeForThisCell() < lowestGrade) {
				// swap the lowest grade
				lowestGrade = currentCellAndGrade.getGradeForThisCell();
				// swap the lowest object with the lowest grade for the enemy next move.
				lowestGradeToReturn.replace(currentCellAndGrade);
			}
		}
		return lowestGradeToReturn;
}

} /* namespace std */

