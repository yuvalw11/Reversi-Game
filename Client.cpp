#include "Client.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include "Cell.h"

using namespace std;

Client::Client(): ip(NULL), portNumber(0), sock(0) {
    memset(sin, 0, sizeof(*sin));
}

Client::Client(int portNumber, char* ip): ip(ip), portNumber(portNumber) {
    memset(sin, 0, sizeof(*sin));
    this->sock = socket(AF_INET, SOCK_STREAM, 0);
    if (this->sock == 0) {
        cout << "could not create socket" << endl;
    }
    
    this->sin->sin_family = AF_INET;
    this->sin->sin_addr.s_addr = inet_addr(this->ip);
    this->sin->sin_port = htons(this->portNumber);
}

bool Client::connectToServer() {
    bool isConnected = connect(sock, (struct sockaddr*)this->sin, sizeof(*sin)) > 0;
    if (isConnected) {
        int sentBytes = send(this->sock, "connected", 10, 0);
        if (sentBytes = 0) {
            cout << "error sending connected message" << endl;
        }
    }
    return isConnected;
}

void Client::EndConnection() {
    close(sock);
}

bool Client::sendMessageToServer(int x, int y) {
    string xStr = to_string(x);
    string yStr = to_string(y);
    const char* yChars = yStr.c_str();
    const char* xChars = xStr.c_str();
    char message[30];
    strcat(message, xChars);
    strcat(message, ", ");
    strcat(message, yChars);
    
    size_t messageLen = strlen(message);
    size_t sentBytes = send(this->sock, message, messageLen, 0);
    return sentBytes > 0;
}

void Client::recieveMessage() {
    char buffer[100];
    int i;
    for (i = 0; i < 100; i++) {
        buffer[i] = '\0';
    }
    int readBytes = recv(this->sock, buffer, sizeof(buffer), 0);
    if (readBytes < 0) {
        cout << "no message recieved" << endl;
        return;
    } else if (strcmp(buffer, "1") == 0) {
        
    } else if (strcmp(buffer, "2") == 0) {
        
    } else {
        int index = 0;
        int x = 0, y = 0;
        string first;
        string last;
        stringstream ss1;
        stringstream ss2;
        while (buffer[index] != ',') {
            ss1 << buffer[index];
            index++;
        }
        index += 2;
        while (index < readBytes) {
            ss2 << buffer[index];
            index++;
        }
        ss1 >> first;
        ss2 >> last;
        x = stoi(first);
        y = stoi(last);
        Cell c = Cell(x, y);
    }
    
}
