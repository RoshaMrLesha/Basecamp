#ifndef SERVERUI_H
#define SERVERUI_H
#include "ui.h"
#include "serversocket.h"
#include "directorymanager.h"

class ServerUI : public UI
{
 public:
  ServerUI();
  virtual ~ServerUI();
  virtual void ShowMenu();
	
 protected:
  virtual void ViewFileSystem();
  virtual int  SetupSocket();
  stringvector FillVectorOfFiles();
  int          SendFilesInfo(const stringvector& files);
  void         ListDirFiles(const stringvector& files, size_t currentFileIndex);
  void         ListDirInfo();
  int          MoveFileOnRemote(std::string& filepath, std::string& newpath);

 private:
  ServerSocket* socket_;
  DirectoryManager* dirmanager_;
  std::string currentfolder_;
  static const size_t kBufferSize_ = 250;
};

#endif // ! SERVERUI_H

