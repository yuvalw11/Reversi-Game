/*
 * ListGamesFunc.cpp
 *
 *  Created on: Dec 22, 2017
 *      Author: Ofir Ben-Shoham
 */

#include "ListGamesFunc.h"

using namespace std;

ListGamesFunc::ListGamesFunc(Server* newServer) {
	this->setServer(newServer);
}

void ListGamesFunc::execute(vector<string> args) {
	// as I wrote, the programmer need to give us the socket of the client that
	// ask to run this command, into args[0]. Therefore:
	try {
		string socketString = args[0];
		const char* socketTemp = socketString.c_str();
		int clientSocketNumber = atoi(socketTemp);
		if (clientSocketNumber <= 0) {
			cout << "Failed to prase the number in ListGamesFunc::execute() \n";
			exit(-1);
		}
		string gamesString = this->getServer()->getOnePlayerGames();
		cout << "My string is:" << gamesString<<endl;
		const char* stringToSend = gamesString.c_str();

		// now, we want to send to the client sokcet the string of the current games.
		if (write(clientSocketNumber, stringToSend, strlen(stringToSend)) < 0) {
			throw "Error writing the games with one player to the client socket, into ListGamesFunc::execute()\n";
		}

		// and the client read it in his class.

	} catch (exception* e) {
		cout
				<< "I don't have the socket number into args[0], ListGamesFunc::execute()\n";
		exit(-1); // can't continue ...
	}
}

