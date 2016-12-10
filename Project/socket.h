#ifndef SOCKET_H
#define SOCKET_H
#ifdef _WIN32
#include <winsock.h>
#include <nettypes.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <iostream>

#define LOCALHOST "127.0.0.1"
#define ERROR -1 //simplicity for now
#define SUCCESS 0
#define STANDART_PORT 5000

class Socket
{
 public:
  virtual ~Socket() {}
  virtual int  CloseSocket() = 0;
  virtual int  ConfigSocket(int family, int type, int protocol) = 0;
};

#endif // ! SOCKET_H
