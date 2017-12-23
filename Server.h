/*
 * Server.h
 *
 *  Created on: Dec 2, 2017
 *      Author: Ofir Ben Shoham.
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <string.h>
#include "GameManager.h"
#include <stdio.h>


namespace std {

class Server {
public:

	/**
	 * constructor of the server. Gets:
	 * const char* ipNum - the ip adress of the server.
	 * int portNum - the numebr of the port.
	 * Both helps us to make a connection.
	 */
	Server(int portNum, GameManager* gm);

	/**
	 * return true if we can continue to ask from the clients for inputs.
	 * Until the game is ended or ("END" was sent).
	 */
	bool checkIfcanContinue();

	/**
	 * Ask for input from the client, interprets him and send the result
	 * (the printed board after the change), to the other client.
	 * Then, continue with that process for the other client.
	 *
	 * int clientSocToRead - the socket number of the client that we read the cell from.
	 * int clientSocToWrite - the socket number of the client that we will pass the cell to.
	 *
	 * Important: in the assignment page, it's written that we get assume that the
	 * input is legal - It means: no needed to check the input from the clients.
	 */
	void handleWithInput(int clientSocToRead, int clientSocToWrite);

	/**
	 * Initialize the socket of the server and checks that it's valid.
	 */
	void socketInitialize();

	/**
	 * start the server and set him.
	 */
	void setAndStartServer();

	/**
	 * define client sockets by accepting them.
	 */
	void defineClientsSockets();

	/**
	 * accept the first & second client into the server and return his socket number.
	 */
	int acceptFirstClientSocket();
	int acceptSecondClientSokcet();

	/**
	 * This method starting the game with the clients.
	 * gets GameDescriptor gameDes- contian data about the first & second clients sockets. And name of game.
	 */
	void workWithClients(GameDescriptor gameDes);

	/**
	 * close the socket of the server.
	 */
	void closeServer();

	/**
	 * read x,y from clientSocToGetFrom
	 * write x,y to clientSocToSend.
	 */
	void GetAndSendIntsToClient(int clientSocToGetFrom, int clientSocToSend);

	/**
	 * int clientSocToWriteInto - to which client socket to write.
	 * write the turn in cell (row, col).
	 */
	void sendTurn(int clientSocToWriteInto, int row, int col);

	/**
	 * get the games with just one client into them.
	 */
	string getOnePlayerGames();

	/**
	 * return pointer to gameManager.
	 */
	GameManager* getGamesManager() {return gamesManager;}

private:
	// the files of the server are ip adress & port number.
	int serverSocket;
	int serverPortNumber;
	GameManager* gamesManager;
	bool canContinue;

};

} /* namespace std */

#endif /* SERVER_H_ */
