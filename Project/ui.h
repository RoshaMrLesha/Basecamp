#ifndef UI_H
#define UI_H
#include <iostream>
#ifdef _WIN32
#include <direct.h>
#include <io.h>
#include <conio.h>
#include <winsock.h>
#else
#include <dirent.h>
#include <sys/socket.h>
#include <unistd.h>
#include <termios.h>
#endif
#include <iomanip>
#include <sys/stat.h>
#include <vector>
#include <string>
#include <sys/types.h>
#include <fstream>
#ifdef _WIN32
#define KEY_ENTER 13
#define KEY_UP 72
#define KEY_DOWN 80
#else
#define KEY_ENTER 10
#define KEY_UP 65
#define KEY_DOWN 66
#endif
#define KEY_B 98
#define KEY_O 111
#define KEY_X 120
#define KEY_V 118
#define SYS_MESSAGE_LEN 9
typedef std::vector<std::string> stringvector;
class UI
{
 public:
  virtual ~UI() {}
  virtual void ShowMenu() = 0;
  virtual void ViewFileSystem() = 0;
  virtual int  SetupSocket() = 0;
};
#endif // !UI_H

