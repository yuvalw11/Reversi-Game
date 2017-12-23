/*
 * CommandsManager.cpp
 *
 *  Created on: Dec 23, 2017
 *      Author: Ofir Ben-Shoham.
 */

#include "CommandsManager.h"
#include "StartGameFunc.h"
#include "ListGamesFunc.h"
#include "JoinGameFunc.h"
#include "PlayTurnFunc.h"
#include "CloseGameFunc.h"

using namespace std;

CommandsManager::CommandsManager(Server* newServer) {
	this->server = newServer;
	// now, initialize the commands.
	commandsMap["start"] = new StartGameFunc(this->server);
	commandsMap["list_games"] = new ListGamesFunc(this->server);
	commandsMap["join"] = new JoinGameFunc(this->server);
	commandsMap["play"] = new PlayTurnFunc(this->server);
	commandsMap["close"] = new CloseGameFunc(this->server);
}

CommandsManager::~CommandsManager() {
	map<string, Command *>::iterator it;
	for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
		delete it->second;
	}
}

void CommandsManager::executeCommand(string command, vector<string> args) {
	Command *commandObj = commandsMap[command];
	commandObj->execute(args);
}
