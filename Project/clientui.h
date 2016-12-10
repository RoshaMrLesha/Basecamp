#ifndef CLIENTUI_H
#define CLEINTUI_H
#include "ui.h"
#include "clientsocket.h"
#include "directoryviewer.h"
#define CHANGE_DIR 0
#define MOVE_FILE 1
#define ARROW_KEY 27
#define PAIR std::make_pair<std::string, int>
class ClientUI : public UI
{
 public:
  ClientUI();
  virtual ~ClientUI();
  virtual void ShowMenu();

 protected:
  virtual void ViewFileSystem(); 
  virtual int  SetupSocket();
  void         ShowMenuHeader(int currentselection);
  stringvector ReceiveFilesInfo();

 private:
  ClientSocket* socket_;
  DirectoryViewer* dirviewer_;
  stringvector  menuoptions_;
  std::string   currentfolder_;
  static const size_t kBufferSize_ = 250;
};

#endif // ! CLIENTUI_H
