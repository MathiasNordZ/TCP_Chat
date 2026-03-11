#include "../../include/socket.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <vector>

using namespace std;

int server(const int listenPort) {
  const int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket < 0) {
    perror("Failed to create socket");
    return -1;
  }

  if (constexpr int opt = 1; setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
    perror("Failed to set socket options");
    close(serverSocket);
    return -1;
  }

  sockaddr_in serverAddr{};
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(listenPort);
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

  errorCheck(bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddr),
                 sizeof(serverAddr)), "Failed to bind serverSocket.");

  errorCheck(listen(serverSocket, 5), "Failed to listen to serverSocket.");

  cout << "Server listening on port " << listenPort << "..." << endl;

  const int clientSocket = accept(serverSocket, nullptr, nullptr);
  if (clientSocket < 0) {
    perror("Failed to accept connection");
    close(serverSocket);
    return -1;
  }

  cout << "Client connected!" << endl;

  char buffer[1024] = {};
  while (true) {
    memset(buffer, 0, sizeof(buffer));
    const int bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

    if (bytesRead < 0) {
      perror("Error receiving data");
      break;
    }
    if (bytesRead == 0) {
      cout << "Client disconnected" << endl;
      break;
    }

    cout << "Message from client: " << buffer << endl;

    string response = "Message received: " + string(buffer);
    send(clientSocket, response.c_str(), response.length(), 0);
  }

  close(clientSocket);
  close(serverSocket);
  return 0;
}

int main() {
  server(8080);
}