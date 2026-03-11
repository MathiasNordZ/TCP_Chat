//
// Created by Mathias Nord on 11/03/2026.
//

#ifndef TCP_CHAT_SOCKET_H
#define TCP_CHAT_SOCKET_H

#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

int errorCheck(const int method, const string& errorCheck) {
  if (method != 0) {
    cout << "ERROR: " << errorCheck;
    return method;
  }
  return 0;
}

#endif //TCP_CHAT_SOCKET_H
