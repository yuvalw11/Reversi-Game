
#ifndef Client_hpp
#define Client_hpp

#include <arpa/inet.h>
#include <string>
#include <stdio.h>
#include "GameRunner.h"



class Client {
private:
    char* ip;
    int portNumber;
    int sock;
    struct sockaddr_in* sin;
    
    
public:
    Client();
    Client(int portNumber, char* ip);
    bool sendMessageToServer(int x, int y);
    void EndConnection();
    void recieveMessage();
    bool connectToServer();
    
};

#endif /* Client_hpp */
