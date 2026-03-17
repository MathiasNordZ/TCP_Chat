#include "tcpSocket.h"

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

  std::cout << "Server listening on port " << listenPort << "..." << std::endl;

  const int clientSocket = accept(serverSocket, nullptr, nullptr);
  if (clientSocket < 0) {
    perror("Failed to accept connection");
    close(serverSocket);
    return -1;
  }

  std::cout << "Client connected!" << std::endl;

  char buffer[1024] = {};
  while (true) {
    memset(buffer, 0, sizeof(buffer));
    const ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

    if (bytesRead < 0) {
      perror("Error receiving data");
      break;
    }
    if (bytesRead == 0) {
      std::cout << "Client disconnected" << std::endl;
      break;
    }

    std::cout << "Message from client: " << buffer << std::endl;

    std::string response = "Message received: " + std::string(buffer);
    send(clientSocket, response.c_str(), response.length(), 0);
  }

  close(clientSocket);
  close(serverSocket);
  return 0;
}

int userInput() {
  int port;
  std::cout << "Please enter port to listen to:" << std::endl;
  std::cin >> port;

  if (port < 0 || port > 65535) {
    return port;
  }
  return -1;
}

int main() {
  const int port = userInput();

  if (port == -1) {
    return -1;
  }
  server(port);
}