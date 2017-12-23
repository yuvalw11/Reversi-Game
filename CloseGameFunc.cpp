/*
 * CloseGameFunc.cpp
 *
 *  Created on: Dec 23, 2017
 *      Author: Ofir Ben-Shoham.
 */

#include "CloseGameFunc.h"

using namespace std;

CloseGameFunc::CloseGameFunc(Server* server) {
	this->setServer(server);
}

/**
 * *** NEED TO CONTINUE IT ***
 */
void CloseGameFunc::execute(vector<string> args) {
	// close the tread the has responssiblity of this game.

	// first get the name
	try {
		string nameOfGameToClose = args[0];
		int threadIndexToClose = this->getServer()->getGamesManager()->findGameAccordingString(nameOfGameToClose);
		this->getServer()->getGamesManager()->removeGame(nameOfGameToClose); // remove the game.

		/*
		 * Close Here the thread with the index : threadIndexToClose.
		 */
		// ADD IT HERE...


	} catch (exception* e ) {
		cout << "There is a problem into loseGameFunc::execute\n";
	}
}
