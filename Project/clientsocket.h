#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H
#include "socket.h"

class ClientSocket : public Socket
{
 public:
  ClientSocket();
  virtual int  ConfigSocket(int family, int type, int protocol);
  virtual int  CloseSocket();
  int          ConnectToServer();
  int          GetSocketId();

 private:
  #ifdef _WIN32
  WSADATA      wsadata_;
  #endif
  int          socketid_;
  char         messageBuffer_[512];
  struct sockaddr_in serveraddress_;
};

#endif // ! CLIENTSOCKET_H
