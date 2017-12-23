/*
 * PlayTurnFunc.cpp
 *
 *  Created on: Dec 23, 2017
 *      Author: ofir
 */

#include "PlayTurnFunc.h"
#include <iostream>

using namespace std;

PlayTurnFunc::PlayTurnFunc(Server* server) {
	this->setServer(server);
}

void PlayTurnFunc::execute(vector<string> args) {
	int firstClientSokcet, secondClientSocket, x, y;

	// get from args[0] the socket number of the first client.
	string firstSocketString = args[0];
	const char* socketTemp = firstSocketString.c_str();
	firstClientSokcet = atoi(socketTemp);
	if (firstClientSokcet <= 0) {
		cout << "Failed to prase the number in ListGamesFunc::execute() \n";
		exit(-1);
	}

	// the same, for args[1] and the second client.
	string secondSocketString = args[1];
	const char* secondSocketTemp = secondSocketString.c_str();
	secondClientSocket = atoi(secondSocketTemp);
	if (secondClientSocket <= 0) {
		cout << "Failed to prase the number in ListGamesFunc::execute() \n";
		exit(-1);
	}

	// get from args[2] the x value of the cell that the first player choose.
	string xString = args[2];
	const char* xStringTemp = xString.c_str();
	x = atoi(xStringTemp);
	if (x <= 0) {
		cout << "Failed to prase the number in ListGamesFunc::execute() \n";
		exit(-1);
	}

	// get from args[3] the y value of the cell that the first player choose.
	string yString = args[3];
	const char* yStringTemp = xString.c_str();
	y = atoi(yStringTemp);
	if (y <= 0) {
		cout << "Failed to prase the number in ListGamesFunc::execute() \n";
		exit(-1);
	}

	// send it to the second socket client (secondClientSocket) as follows:
	int n = write(secondClientSocket, &x, sizeof(x));
	if (n < 0) {
		throw "Error writing x to socket";
	}
	if (write(secondClientSocket, &y, sizeof(y)) < 0) {
		throw "Error writing y to socket";
	}

}
