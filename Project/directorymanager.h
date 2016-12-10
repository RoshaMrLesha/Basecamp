#ifndef DIRECTORYMANAGER_H
#define DIRECTORYMANAGER_H

#include "directoryprocessor.h"

class DirectoryManager : public DirectoryProcessor
{
 public:
  DirectoryManager() {}
  virtual      ~DirectoryManager() {}
  virtual void ListDirFiles(const stringvector& files, size_t currenfileindex);
  stringvector FillVectorOfFiles();
  int          MoveFileOnRemote(std::string& filepath, std::string& newpath);
 private:
  static const size_t kBufferSize_ = 250;
};
#endif // ! DIRECTORYMANAGER_H
