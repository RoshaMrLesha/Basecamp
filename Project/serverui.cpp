#include "serverui.h"

ServerUI::ServerUI()
{
  socket_ = new ServerSocket;
  dirmanager_ = new DirectoryManager;
  #ifdef _WIN32
  currentfolder_ = "C:\\";
  #else
  currentfolder_ = "/";
  #endif
}

ServerUI::~ServerUI()
{
  socket_->CloseSocket();
  delete socket_;
  delete dirmanager_;
}

#ifndef _WIN32
int getch()
{
  struct termios oldstate, newstate;
  int symbol;
  tcgetattr(STDIN_FILENO, &oldstate);
  newstate = oldstate;
  newstate.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newstate);
  symbol = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldstate);
  return symbol;
}
#endif

void ServerUI::ShowMenu()
{
  std::cout << "r - Run server\n";
  std::cout << "e - Exit\n\n";
  std::cout << ">";
  int userinput = getch();
  if (userinput == 'r') 
  { 
    if (SetupSocket() == 0) { ViewFileSystem(); }
  }
  else if (userinput == 'e') { return; }
}
int ServerUI::SetupSocket()
{
  #ifdef _WIN32
  system("cls");
  #else
  std::cout << "\033[2J\033[1;1H";
  #endif
  int operationresult;
  if ((operationresult = socket_->ConfigSocket(AF_INET, SOCK_STREAM, 0)) < 0) { return ERROR; }
  if ((operationresult = socket_->BindAddress()) < 0) { return ERROR; }
  if ((operationresult = socket_->ListenConnections(1)) < 0) { return ERROR; }
  if ((operationresult = socket_->AcceptConnection()) < 0) { return ERROR; }
  return SUCCESS;
}
void ServerUI::ViewFileSystem()
{
  bool working = true;
  char buffer[kBufferSize_];
  int bytesread;
  while (working)
  {
    #ifdef _WIN32
    _chdir(currentfolder_.c_str());
    #else
    chdir(currentfolder_.c_str());
    #endif
    stringvector files = dirmanager_->FillVectorOfFiles();
    SendFilesInfo(files);
    for(;;) //wait for understandable recv()
    {
      bytesread = recv(socket_->GetSocketId(), buffer, kBufferSize_, 0);
      if (strcmp(buffer, "drchange") == 0)
      {
        bytesread = recv(socket_->GetSocketId(), buffer, kBufferSize_, 0);
        int bytessent = send(socket_->GetSocketId(), buffer, kBufferSize_, 0);
        buffer[bytesread] = '\0';
        currentfolder_ = std::string(buffer);
        break;
      }
      if (strcmp(buffer, "movefile") == 0)
      {
        char meta[kBufferSize_];
        bytesread = recv(socket_->GetSocketId(), meta, kBufferSize_, 0);
        std::string metadata(meta); //easy parse
        std::string filetomove(metadata.substr(0, metadata.find_first_of('|')));
        std::string newpath;
        #ifdef _WIN32
        newpath = currentfolder_ + filetomove.substr(filetomove.find_last_of('\\'), std::string::npos);
        #else
        newpath = currentfolder_ + filetomove.substr(filetomove.find_last_of('/'), std::string::npos);
        #endif
	std::cout<<"Ftm: "<<filetomove<<'\n';
	std::cout<<"Np: "<<newpath<<'\n';
        int bytessent = send(socket_->GetSocketId(), buffer, kBufferSize_, 0);
        #ifdef _WIN32
        if (currentfolder_ == filetomove.substr(0, filetomove.find_last_of('\\'))) { break; } //moving in the same folders
        #else
        if (currentfolder_ == filetomove.substr(0, filetomove.find_last_of('/'))) { break; } //moving in the same folders
        #endif
        buffer[bytesread] = '\0';
        dirmanager_->MoveFileOnRemote(filetomove, newpath);
        break;
      }
    }
  }
}

int ServerUI::SendFilesInfo(const stringvector& files)
{
  int socketid = socket_->GetSocketId(), bytesread;
  char buffer[kBufferSize_];
  bytesread = recv(socketid, buffer, 1, 0); //confirm connection
  bytesread = send(socketid, buffer, 1, 0);
  for (stringvector::const_iterator It = files.begin(); It != files.end(); ++It)
  {
    if ((bytesread = send(socketid, It->c_str(), It->size(), 0)) < 0) { break; }
    #ifdef _WIN32
    Sleep(20);
    #else
    usleep(20);
    #endif
    if ((bytesread = recv(socketid, buffer, 1, 0)) < 0) { break; }
    memset(&buffer,'\0',kBufferSize_);
  }
  return SUCCESS;
}
