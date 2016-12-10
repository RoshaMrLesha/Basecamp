#include "clientsocket.h"
#ifdef _WIN32
#pragma comment(lib, "Ws2_32.lib")
#endif

ClientSocket::ClientSocket()
{

}
int ClientSocket::ConfigSocket(int family, int type, int protocol)
{
  #ifdef _WIN32
  if (WSAStartup(MAKEWORD(2, 1), &wsadata_)) { return ERROR; }
  #endif
  socketid_ = socket(family, type, protocol);
  if (socketid_ < 0) { return ERROR; }
  serveraddress_.sin_family = AF_INET;
  serveraddress_.sin_port = htons(STANDART_PORT);
  serveraddress_.sin_addr.s_addr = inet_addr(LOCALHOST);
  return SUCCESS;
}
int ClientSocket::ConnectToServer()
{
  std::cout << "Connecting to server...\n";
  int connected = connect(socketid_, (struct sockaddr*)&serveraddress_, sizeof(serveraddress_));
  if (connected < 0) { return ERROR; }
  std::cout << "Connected to server at 127.0.0.1\n";
  return SUCCESS;
}
int ClientSocket::GetSocketId()
{
  return socketid_;
}
int  ClientSocket::CloseSocket()
{
  #ifdef _WIN32
  WSACleanup();
  closesocket(socketid_);
  #else
  close(socketid_);
  #endif
  return SUCCESS;
}