#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H
#include "socket.h"

class ServerSocket : public Socket
{
 public:
  ServerSocket();
  virtual int  ConfigSocket(int family, int type, int protocol);
  virtual int  CloseSocket();
  int          BindAddress();
  int          ListenConnections(size_t maxconnections);
  int          AcceptConnection();
  int          GetSocketId();

 private:
  #ifdef _WIN32
  WSADATA      wsadata_;
  #endif
  struct sockaddr_in serveraddress_, clientaddress_;

  int          socketid_, listenerid_;
  char	       messagebuffer_[300];
};

#endif // ! SERVERSOCKET_H
