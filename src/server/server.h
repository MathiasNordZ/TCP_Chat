//
// Created by mathias-nord on 3/11/26.
//

#ifndef TCP_CHAT_SERVER_H
#define TCP_CHAT_SERVER_H
#include <arpa/inet.h>

void createAddr(int listenPort, sockaddr_in &serverAddr);
int server(int listenPort);
void serverLoop(int clientSocket, char buffer[1024]);

#endif //TCP_CHAT_SERVER_H