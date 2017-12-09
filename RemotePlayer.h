/*
 * RemotePlayer.h
 *
 *  Created on: Dec 8, 2017
 *      Author: ofir
 */

#ifndef REMOTEPLAYER_H_
#define REMOTEPLAYER_H_
#include "Client.h"
#include "temp/GameRunner.h"

namespace std {

class RemotePlayer : public Player {
public:
	RemotePlayer(Client myClient, GameLogic gl);
	Cell chooseCell(Board* board, char playerSign);
	void printPossibleMoves(Board &board, char playerSign);
	char getPlayerSign() { return this->currentPlayer; }

	//RemotePlayer(){}
private:
	GameLogic gameLogic;
	Client client; // in order his socket will really change when return to RemotePlayer.
	char currentPlayer;
};

} /* namespace std */

#endif /* REMOTEPLAYER_H_ */
