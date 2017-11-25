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
#include "GameLogic.h"
//#include <vector>

namespace std {

class AIPlayer : public Player{
public:

	// REMOVE it!!!!!!!!!!!!!!!!
	void makesM(Board *board, char playerSign);
	Cell returnAICell(Board &board, char playerSign);
	Cell chooseCell(Board *board, char playerSign);




	/**
	 * constructor method of AI player.
	 * Gets:
	 * char pSign - the sign of the player.
	 */
	AIPlayer(char Psign) {
		Player::setPlayerSign(Psign); // very important
		playerSign = Psign;
	}



	/**
	 * returns the sign of the AI player.
	 */
	char getAIplayerSign() {
		return playerSign;
	}


	/**
	 * Part 2B in the mini-max pasudo code.
	 * Gets a vector of cells, that represents the possible cells
	 * Return MiniMaxCell object that contains minimum grade of the cell and the cell itself.
	 */
	static MiniMaxCell getEnemyCurrentMaxGrade(Board &board,
			vector<Cell> possibleCells, char enemySign);

	/**
	 *
	 */
	static int getEnemyCurrentGrade(Board &board,
			char enemySign);

	static MiniMaxCell returnNextMove(Board &board, char playerSign);



private:
	char playerSign; // the sign of the AI player in the board.
};

} /* namespace std */

#endif /* AIPLAYER_H_ */
