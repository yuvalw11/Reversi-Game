/*
 * StartGameFunc.cpp
 *
 *  Created on: Dec 22, 2017
 *      Author: Ofir Ben-Shoham
 */

#include "StartGameFunc.h"

StartGameFunc::StartGameFunc(Server* server) {
	this->setServer(server);
}

void StartGameFunc::execute(vector<string> args) {
	try {
		string socketString = args[0];
		const char* socketTemp = socketString.c_str();
		int clientSocketNumber = atoi(socketTemp);
		if (clientSocketNumber <= 0) {
			cout << "Failed to prase the number in ListGamesFunc::execute() \n";
			exit(-1);
		}

		// now, want to create new game according args[1]
		string newGameName = args[1];
		if (this->getServer()->getGamesManager()->findGameAccordingString(
				newGameName) >= 0) {
			// it means that we allready have a game in this name, therefore return -1 to the client socket.
			int n = write(clientSocketNumber, "-1", sizeof("-1"));
			if (n <= 0) {
				cout
						<< "Can't send to the client that he can't choose this game name, into StartGameFunc::execute\n";
				exit(-1);
			}
		} else {
			// can to open new game with this name.
			// without the players, just open new game
			this->getServer()->getGamesManager()->addGame(newGameName, clientSocketNumber, -1);
			cout << "Added the new name \n";
		}

	} catch (exception * e) {
		cout
				<< "Problem with prasing the input agrs, into StartGameFunc::execute\n";
		exit(-1); // can't continue ...
	}
}
