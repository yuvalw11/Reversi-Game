/*
 * Client.h
 *
 *  Created on: Dec 6, 2017
 *      Author: ofir
 */

#ifndef CLIENT_H_
#define CLIENT_H_
#include "temp/Cell.h"
#include "temp/DoubleCell.h"
// include the game runner

namespace std {

class Client {
public:
	Client(const char *serverIP, int serverPort);

	Client() {
		DoubleCell d;
		clientSocket = 0;
		serverIP = 0;
		serverPort = 0;
		playerNum = 0;
		turnsToPlay = d;
	}
	void connectToServer(bool firstClient = false);
	DoubleCell sendAndWriteToServer();
	void readHisCilentNum();
	Cell getCurrentTurn();
	void sendTurnToServer(int row, int col);
	void startClient();
	Cell getMyCell() { return this->turnsToPlay.getCurrentPlayerMove(); }
	Cell getOtherCell() { return this->turnsToPlay.getOtherPlayerMove(); }

	int getPlayerNum() const {
		return playerNum;
	}

	DoubleCell getTurnsToPlay() const {
		return turnsToPlay;
	}

	void setPlayerNum(int playerNum) {
		this->playerNum = playerNum;
	}

private:
	const char *serverIP;
	int serverPort;
	int clientSocket;
	int playerNum;
	DoubleCell turnsToPlay;

};
/* namespace std */
}

#endif /* CLIENT_H_ */
