#ifndef DIRECTORYVIEWER_H
#define DIRECTORYVIEWER_H

#include "directoryprocessor.h"
#ifndef _WIN32
#include "unixgetch.h"
#endif
#define CHANGE_DIR 0
#define MOVE_FILE 1
#define PAIR std::make_pair<std::string, int>
#ifdef _WIN32
#define KEY_ENTER 13
#define KEY_UP 72
#define KEY_DOWN 80
#define ROOT_LEN 3
#else
#define KEY_ENTER 10
#define KEY_UP 65
#define KEY_DOWN 66
#define ARROW_KEY 27
#define ROOT_LEN 1
#endif
#define KEY_B 98
#define KEY_O 111
#define KEY_X 120
#define KEY_V 118
#define SYS_MESSAGE_LEN 9

class DirectoryViewer : public DirectoryProcessor
{
 public:
  virtual      ~DirectoryViewer() {}
  virtual void ListDirFiles(const stringvector& files, size_t currenfileindex);
  std::pair<std::string, int>  ListDirInfo(stringvector& files);
  void SetSelectedFile(const std::string& filename);
  std::string GetSelectedFile();
 private:
  std::string selectedfile_;
};
#endif // ! DIRECTORYVIEWER_H
