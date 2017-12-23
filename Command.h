/*
 * Command.h
 *
 *  Created on: Dec 22, 2017
 *      Author: Ofir Ben-Shoham.
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include <vector>
#include <string>
#include "Server.h"
#include <stdlib.h>

using namespace std;
class Command {

public:
 virtual void execute(vector<string> args) = 0; // to be implemente in the derived classes.
 virtual ~Command() {}

	Server* getServer() {return server;}

	void setServer(Server* server) {this->server = server;}

private:
 /**
  * define in the base class the server as a field, in order to avoid
  * duplicate it in all the derived classes.
  */
 Server* server;
};



#endif /* COMMAND_H_ */
