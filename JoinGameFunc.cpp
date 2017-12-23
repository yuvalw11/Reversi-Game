/*
 * JoinGameFunc.cpp
 *
 *  Created on: Dec 23, 2017
 *      Author: Ofir Ben-Shoham
 */

#include "JoinGameFunc.h"

using namespace std;

JoinGameFunc::JoinGameFunc(Server* server) {
	this->setServer(server);
}

// args[0]- socket of the client that wants to enter to
// args[1] game (name of game).
void JoinGameFunc::execute(vector<string> args) {
	// first check if we really have a game in this name.

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
					newGameName) < 0) {
				// we don't have a game it this name.
				int n = write(clientSocketNumber, "-1", sizeof("-1"));
				if (n <= 0) {
					cout
							<< "Can't send to the client that he can't choose this game name, into JoinGameFunc::execute\n";
					exit(-1);
				}
			} else {
				// the second player can enter to the game.

				GameDescriptor* toEnterIntoHim = this->getServer()->getGamesManager()->getGameAccordingString(newGameName);
				toEnterIntoHim->setSecondClientSocket(clientSocketNumber); // enter the socket of the second player.
				if (!toEnterIntoHim->IsBothPlayersConnects()) {
					cout << "Not both the players are connected, JoinGameFunc::execute\n";
					exit(-1);
				} else {
					// now we know that we have two players into the game, so we can start it,
					// therefore, enter a tread.

					/*
					 * We have two players into the game, therefore I want to open new thread to run the game.
					 * the function that should run the game is workWithClients() into Server.
					 * The object that need to be send into workWithClients() is toEnterIntoHim that contains
					 * data about the name of the game and the sockets of the two clients.
					 */
					 //int rc = pthread_create(&1, NULL, toEnterIntoHim, (void *)&toEnterIntoHim);

				}
			}

		} catch (exception * e) {
			cout
					<< "Problem with prasing the input agrs, into StartGameFunc::execute\n";
			exit(-1); // can't continue ...
		}

}
