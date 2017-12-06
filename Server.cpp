/*
 * Server.cpp
 *
 *  Created on: Dec 2, 2017
 *      Author: Ofir Ben Shoham.
 */

#define maxConnections 2
#include "Server.h"
#include <stdio.h>

namespace std {

Server::Server(int portNum) {
	this->serverPortNumber = portNum;
	this->serverSocket = 0; // by default, will change after initalize.
	canContinue = true; // until we get "END"
}

void Server::socketInitialize() {
	this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->serverSocket < 0) {
		perror("Failed in socketInitialize() \n");
	}
}

void Server::setAndStartServer() {
	// Assign a local address to the socket
	struct sockaddr_in serverAddress;
	// now, to be ensure that all his data is empty.
	memset(&serverAddress, 0, sizeof(serverAddress));

	// initialize the serverAdress as followsthrow "Error on binding";
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(this->serverPortNumber);

	// bind according the serverSocket that we built & the serverAdress.
	if (bind(serverSocket, (struct sockaddr *) &serverAddress,
			sizeof(serverAddress)) < 0) {
		perror("Failed in bind of serverSocket at setAndStartServer() \n");
	}

	// Start listening to incoming connections
	listen(serverSocket, maxConnections);
}

void Server::handleWithInput(int clientSocToRead, int clientSocToWrite) {
	char buffer[4096]; // to the input from the reading socket.
	// first will read from the clientSocToRead
	int n = read(clientSocToRead, &buffer, sizeof(buffer));
	if (n <= 0) {
		cout << "Error when reading from the client" << endl;
		return;
	}
	if (!strcmp(buffer, "NoMove")) {
		// No possible steps therefore -> finish without writing, because we have no thing to write on,
		return;
	}

	// now writing to the second client socket.
	n = write(clientSocToWrite, &buffer, sizeof(buffer));
	if (n <= 0) {
		cout << "Error writing to socket" << endl;
		return;
	}

	// check if need to end the game.
	if (!strcmp(buffer, "End")) {
		this->canContinue = false; // the game is ended, end was read from the cilent.
	}

}

bool Server::checkIfcanContinue() {
	return this->canContinue;
}

void Server::workWithClients() {
	// Define the clients socket's structures
	struct sockaddr_in firstClientAddress, secondClientAddress;
	socklen_t firstClientAddressSize, secondClientAddressSize;

	cout << "Waiting for client connections..." << endl;
	// Accept a new client connection for the first client.
	int firstClientSocket = accept(serverSocket,
			(struct sockaddr *) &firstClientAddress, &firstClientAddressSize);
	if (firstClientSocket < 0) {
		perror("Problem in accept of the first client.\n");
	}

	// now want to read "connected" from the cilent to know that it's really connection.
	char buffer[4096];
	if (read(firstClientSocket, buffer, sizeof(buffer)) < 0) {
		perror("Problem in read() of firstClientSocket\n");
	}
	// otherwise, checks that the first is really connection, it should passes connected.
	if (!strcmp(buffer, "connected")) {
		cout << "first is really connected\n";
	} else {
		perror("The first cilent didn't send connected\n");
	}
	strcpy(buffer, ""); // reset the buffer
	// do the same to check that the second is connected.

	int secondClientSocket = accept(serverSocket,
			(struct sockaddr *) &secondClientAddress, &secondClientAddressSize);
	if (secondClientSocket < 0) {
		perror("Problem in accept of the second client.\n");
	}
	if (read(secondClientSocket, buffer, sizeof(buffer)) < 0) { // check for connection from the second client.
		perror("Problem in read() of secondClientSocket\n");
	}

	if (!strcmp(buffer, "connected")) {
		cout << "second is really connected\n";
	} else {
		perror("The second cilent didn't send connected\n");
	}
	strcpy(buffer, "1");
	if (write(firstClientSocket, buffer, sizeof(buffer)) < 0) {
		perror(
				"Failed to write 1 to the firstClientSocket after both connected");
	}
	strcpy(buffer, ""); // empty now
	strcpy(buffer, "2");
	if (write(secondClientSocket, buffer, sizeof(buffer)) < 0) {
		perror(
				"Failed to write 2 to the secondClientSocket after both connected");
	}

	strcpy(buffer, ""); // reset the buffer

	// Connect them before the loop because we want to send "1 to player 1 & 2 to player 2
	// Just once and not always.

	// start the while loop until END was sent.
	while (checkIfcanContinue()) {
		handleWithInput(firstClientSocket, secondClientSocket);
		// check if still can continue:
		if (!checkIfcanContinue()) {
			break;
		} else {
			// can continue, so do it but reverse to pass from the second to the first.
			handleWithInput(secondClientSocket, firstClientSocket);
		}
	}
	// when it comes to here, it means that we exited from the while and the game is ended.
	closeServer(); // then close the socket's server and finish the game.

}

void Server::closeServer() {
	close(this->serverSocket);
}

}

