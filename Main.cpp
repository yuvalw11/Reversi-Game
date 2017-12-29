/*
 * Main.cpp
 *
 *  Created on: Dec 2, 2017
 *     Names : Yuval Weinstein & Ofir Ben Shoham.
 *     Id: 208580613 & 208642496.
 */
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "Server.h"
#include "ListGamesFunc.h"
#include "StartGameFunc.h"
#include "ThreadStarter.h"
#include "ThreadServer.h"

using namespace std;

void exitFromAllTheGames(Server* server) {
	// first, pass on the games
	GameManager* gameMng = server->getGamesManager();
	vector<GameDescriptor*> gamesToRemove = gameMng->getGamesDesList();
	unsigned int index = 0;
	for (index = 0; index < gamesToRemove.size(); index++) {
		// remove each game
		GameDescriptor* d = gamesToRemove[index];
		string currentGameName = d->getNameOfGame();

		// because if the clients gets (-100, -100) he knows that he needs to finish the game, and close his socket.
		write(d->getFirstClientSocket(), "-100", sizeof("-100")); // send -100 to the socket of the first client
		write(d->getFirstClientSocket(), "-100", sizeof("-100")); // send -100 to the socket of the first client
		write(d->getSecondClientSocket(), "-100", sizeof("-100")); // the same for the second client.
		write(d->getSecondClientSocket(), "-100", sizeof("-100")); // the same for the second client.

		// close the thread of the game and remove it from the vector<GameDescriptor>:
		gameMng->removeGame(currentGameName);

		// the socket are closed into the games itself, since they get -100 as an input cell.
		// now, after closing the clients sockets we want to close the thread of this game
	}

}

int main() {

	int portNumber;
	string line;
	ifstream myfile("exe/ConnectingDetails.txt");

	if (!myfile.is_open()) {
		cout << "Unable to open file";
		return -1;
	}
	// Otherwise, opened the file.

	getline(myfile, line); // no use of the ip adress in the server.

	getline(myfile, line);
	size_t posPort = line.find(":") + 1;
	if (posPort > 0) {
		string temp = line.substr(posPort);
		portNumber = atoi(temp.c_str());
	}
	myfile.close();

	GameManager gm;

	Server server(portNumber, &gm); // the port we read from the file.
	server.socketInitialize();
	server.setAndStartServer();

	GameManager gameManager; // initialize game manager with the vector of all the games.

	struct argsToThreadServer* argsToPass = new argsToThreadServer;
	argsToPass->gameManager = &gameManager;
	argsToPass->serverSocket = server.getServerSocket();
	argsToPass->secondClientSocket = -1; // by default, because we didn't do accept to the second client.

	pthread_t thread;
	// add the needed in the next line:
	cout << " call to gamesRunner thread\n";
	int rc = pthread_create(&thread, NULL, ThreadServer::gamesRunner,
			(void*) argsToPass);

	if (rc) {
		cout << "error with creating thread" << endl;
	}

	delete argsToPass;

	exitFromAllTheGames(&server); // call to helper method to exit from the games.
	cout << "Exit from the server thread\n";

	/*/expecting new connections all the time
	 while (true) {
	 argsToPass.firstClientSocket = server.acceptClientSocket(server.getServerSocket());
	 argsToPass.secondClientSocket = -1; // by defualt, because we didn't do accept to the second client.
	 ThreadStarter::readAndRunCommand((void*) &argsToPass); // pass the struct with the data.
	 }*/

	return 0;
}
