/*
 * AIPlayer.h
 * The AI player extends Player "interface", because it has
 * it's own implementation of the makeMove method.
 *  Created on: Nov 23, 2017
 *      Author: ofir
 */

#ifndef AIPLAYER_H_
#define AIPLAYER_H_
#include "Player.h"
#include "Board.h"
#include "MiniMaxCell.h"
//#include <vector>


namespace std {

class AIPlayer: public Player {
public:

	/**
	 * constructor method of AI player.
	 * Gets:
	 * char pSign - the sign of the player.
	 */
	AIPlayer(char Psign) { playerSign = Psign; }

	/**
	 * virtual deconstructor.
	 */
	virtual ~AIPlayer(){};

	/**
	 * returns the sign of the AI player.
	 */
	char getAIplayerSign() { return playerSign; }

	/**
	 * Part 2B in the mini-max pasudo code.
	 * Gets a vector of cells, that represents the possible cells
	 * Return MiniMaxCell object that contains minimum grade of the cell and the cell itself.
	 */
	MiniMaxCell getEnemyMinGrade(Board &board, vector<Cell> possibleCells, char enemySign);

	/**
	 *
	 */
	int getEnemyCurrentGrade(Board &board, Cell possibleCellToCheck, char enemySign);

private:
	char playerSign; // the sign of the AI player in the board.
};

} /* namespace std */

#endif /* AIPLAYER_H_ */
