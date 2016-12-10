#include "serversocket.h"
#ifdef _WIN32
#pragma comment(lib, "Ws2_32.lib")
#endif

ServerSocket::ServerSocket()
{

}
int  ServerSocket::ConfigSocket(int family, int type, int protocol)
{
  #ifdef _WIN32
  if (WSAStartup(MAKEWORD(1, 1), &wsadata_)) { return ERROR; }
  #endif
  listenerid_ = socket(family, type, protocol);
  if (listenerid_ < 0) { return ERROR; }
  serveraddress_.sin_family = AF_INET;
  serveraddress_.sin_port = htons(STANDART_PORT);
  serveraddress_.sin_addr.s_addr = INADDR_ANY;
  return SUCCESS;
}
int ServerSocket::BindAddress()
{
  if(bind(listenerid_,(struct sockaddr*)&serveraddress_,sizeof(serveraddress_)) < 0)
  {
    CloseSocket();
    return ERROR;
  }
  return SUCCESS;
}
int ServerSocket::ListenConnections(size_t maxconnections)
{
  if(listen(listenerid_, maxconnections) < 0)
  {
    CloseSocket();
    return ERROR;
  }
  return SUCCESS;
}
int ServerSocket::AcceptConnection()
{
  printf("Waiting for connections...\n");
  #ifdef _WIN32
  int socketAddressSize = sizeof(sockaddr_in);
  #else
  socklen_t socketAddressSize = sizeof(sockaddr_in);
  #endif
  socketid_ = accept(listenerid_, (sockaddr*)&clientaddress_, &socketAddressSize);
  if (socketid_ < 0) { return ERROR; }
  printf("Client connected\n");
  return SUCCESS;
}
int ServerSocket::GetSocketId()
{
  return socketid_;
}
int ServerSocket::CloseSocket()
{
  #ifdef _WIN32
  closesocket(socketid_);
  #else
  close(socketid_);
  #endif
  return SUCCESS;
}
