#include "tcpSocket.h"

int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

int client(int port, const char* serverIP) {
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, serverIP, &serverAddr.sin_addr);

    errorCheck(connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)), "Failed to connect client to server");

    while (true) {
        char message[1024];
        std::cin.getline(message, 1024);
        send(clientSocket, message, strlen(message), 0);
    }
}

std::tuple<int, const char*> userInput() {
    int port;
    std::string serverIP;

    std::cout << "Please enter port to connect to:\n";
    std::cin >> port;

    std::cout << "Please enter IP address to connect to:\n";
    std::cin >> serverIP;
    const char* serverIPString = serverIP.c_str();

    return std::make_tuple(port, serverIPString);
}

int main() {
    std::tuple<int, std::string> input = userInput();

    client(std::get<0>(input), std::get<1>(input).c_str());
    return 0;
}