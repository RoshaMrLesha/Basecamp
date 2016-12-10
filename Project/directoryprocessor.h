#ifndef DIRECTORYPROCESSOR_H
#define DIRECTORYPROCESSOR_H
#ifdef _WIN32
#include <winsock.h>
#include <direct.h>
#include <sys/types.h>
#include <conio.h>
#include <io.h>
#else
#include <sys/socket.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#endif
#include <sys/stat.h>
#include <iomanip>
#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#define ERROR -1
#define SUCCESS 0
typedef std::vector<std::string> stringvector;

class DirectoryProcessor
{
 public:
  virtual ~DirectoryProcessor() {}
  virtual void ListDirFiles(const stringvector& files, size_t currenfileindex) = 0;
};
//derived : DirectoryViewer(client-side), DirectoryManager(server-side)
#endif // ! DIRECTORYPROCESSOR_H
