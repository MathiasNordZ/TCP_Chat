#include "../../include/socket.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
using namespace std;

int server(int listenPort) {
  int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket < 0) {
    perror("Failed to create socket");
    return -1;
  }

  sockaddr_in serverAddr{};
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(listenPort);
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

  errorCheck(bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddr),
                   sizeof(serverAddr)), "Failed to bind serverSocket.");

  errorCheck(listen(serverSocket, 5), "Failed to listen to serverSocket.");

  int clientSocket = accept(serverSocket, nullptr, nullptr);
  while (true) {
    if (clientSocket < 0) {
      perror("Failed to accept connection");
      continue;
    }

    char buf[1024] = {};
    recv(clientSocket, buf, sizeof(buf), 0);
    cout << "Message from client: " << buf << endl;

    close(clientSocket);
  }
}

int main() {
  server(8080);
}