//
// Created by Mathias Nord on 11/03/2026.
//

#ifndef TCP_CHAT_SOCKET_H
#define TCP_CHAT_SOCKET_H

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

inline int errorCheck(const int method, const std::string& errorMessage) {
  if (method != 0) {
    std::cout << "ERROR: " << errorMessage;
    return method;
  }
  return 0;
}

#endif //TCP_CHAT_SOCKET_H
