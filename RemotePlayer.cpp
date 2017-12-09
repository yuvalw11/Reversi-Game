/*
 * RemotePlayer.cpp
 *
 *  Created on: Dec 8, 2017
 *      Author: Ofir Ben Shoham
 */

#include "RemotePlayer.h"

using namespace std;

RemotePlayer::RemotePlayer(Client myClient, GameLogic gl) {
	client = myClient;
	gameLogic = gl;
	//myClient->connectToServer(isFirstPlayer);
	if (myClient.getPlayerNum() == 1) {
		// x is the first player
		currentPlayer = 'X';
	} else {
		currentPlayer = 'O';
	}
}

void RemotePlayer::printPossibleMoves(Board& b, char Ps) {
	vector<Cell> possibleMovesVec = b.possibleCellsToAssign(Ps);
	cout << "Player: " << Ps << " ,Your Possible Moves are: ";
	for (unsigned i = 0; i < possibleMovesVec.size(); i++) {
		possibleMovesVec[i].printCell();
	}
	cout << " \nPlease choose a cell from your possible options,"
			" for example write 3 and press enter" << endl
			<< "                   4 and press enter:" << endl;
}

Cell RemotePlayer::chooseCell(Board* board, char playerSign) {

	// update his board before passing to the second player his turn.
	/*DoubleCell dc;
	Cell otherTurn, myTurn;

	if (playerSign == 'X') {
		// the first player first write his turn and then read
		printPossibleMoves(*board, playerSign);
		client.setPlayerNum(1);
		dc = client.sendAndWriteToServer(); // write here his turn and then read other player turn.
	} else {
		client.setPlayerNum(2);
		// the second player first read other player sign and then write.
		dc = client.sendAndWriteToServer(); // write here his turn and then read other player turn.
	}

	otherTurn = dc.getOtherPlayerMove();
	cout << "(1) My cell to play is:";
	otherTurn.printCell();
	myTurn = dc.getCurrentPlayerMove();
	cout << "\n(1) Other cell to play is: \n";
	myTurn.printCell();

	cout << "After using client member the results are:\n";
	cout << "(2)  My cell to play is: ";
	client.getMyCell().printCell();
	cout << "\n(2) Other cell to play is: ";
	client.getOtherCell().printCell();
	cout << endl;

	// first make the other player turn.
	board->inputAssignManager(Cell::returnOtherSign(playerSign), otherTurn);

	// return the current player turn - the cell that choosen (that he entered via input from user).
	return myTurn;*/
	client.sendAndWriteToServer();
	return Cell(1,1);
}
