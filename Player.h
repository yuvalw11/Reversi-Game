/*
 * Player.h
 *
 *  Created on: Nov 23, 2017
 *      Author: Ofir Ben Shoham
 */

#ifndef PLAYER_H_
#define PLAYER_H_
#include <vector>
#include "Board.h"

class Player {

public:

	Player(){playerSign = ' ';} // default constructor.
	Player(char player) {
		playerSign = player;
	}

	/**
	 * returns the sign of the player - X or 0.
	 */
	char getPlayerSign() { return playerSign; }
	virtual ~Player(){}

	/**
	 * virtual method, makes a move in the board.
	 * This function is diffrent between the AI player and the
	 * human player, therefore we use a virual function.
	 * Gets:
	 * char playerSign - the sign of the player who makes the move.
	 *
	 */
	virtual void makesMove(Board *board, char playerSign) = 0;

private:
	char playerSign; // the sign of this player - X OR O.

#endif /* PLAYER_H_ */
};

inline void Player::makesMove(Board* board, char playerSign) {
}
