#include "../../include/socket.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

int client(int port, const char* serverIP) {
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, serverIP, &serverAddr.sin_addr);

    errorCheck(connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)), "Failed to connect client to server");

    while (true) {
        char message[1024];
        cin.getline(message, 1024);
        send(clientSocket, message, strlen(message), 0);
    }

    //errorCheck(close(clientSocket), "Failed to close client socket.");
    //return 0;
}

int main() {
    client(8080, "127.0.0.1");
    return 0;
}