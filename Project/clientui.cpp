#include "clientui.h"

ClientUI::ClientUI()
{
  socket_ = new ClientSocket;
  dirviewer_ = new DirectoryViewer;
  menuoptions_.push_back("Connect to server");
  menuoptions_.push_back("Instructions");
  menuoptions_.push_back("Exit");
  #ifdef _WIN32
  currentfolder_ = "C:\\";
  #else
  currentfolder_ = "/";
  #endif
}

ClientUI::~ClientUI()
{
  socket_->CloseSocket();
  delete socket_;
  delete dirviewer_;
}

int ClientUI::SetupSocket()
{
  #ifdef _WIN32
  system("cls");
  #else
  std::cout << "\033[2J\033[1;1H";
  #endif
  int operationresult;
  if ((operationresult = socket_->ConfigSocket(AF_INET, SOCK_STREAM, 0)) < 0) { return ERROR; }
  if ((operationresult = socket_->ConnectToServer()) < 0) { return ERROR; }
  return SUCCESS;
}
void ClientUI::ViewFileSystem()
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
    stringvector files = ReceiveFilesInfo();
    std::pair<std::string, int> dirprocessingresult = dirviewer_->ListDirInfo(files);
    currentfolder_ = dirprocessingresult.first; //std::string e.g. path
    if (dirprocessingresult.second == CHANGE_DIR) {
      bytesread = send(socket_->GetSocketId(), "drchange", SYS_MESSAGE_LEN, 0); 
      #ifdef _WIN32 
	Sleep(20);
      #else 
	usleep(20);
      #endif
      bytesread = send(socket_->GetSocketId(), currentfolder_.c_str(), currentfolder_.size(), 0);
      bytesread = recv(socket_->GetSocketId(), buffer, kBufferSize_, 0);
    } else if (dirprocessingresult.second == MOVE_FILE) { 
      bytesread = send(socket_->GetSocketId(), "movefile", SYS_MESSAGE_LEN, 0); 
      std::string message = dirviewer_->GetSelectedFile() + '|' + currentfolder_ + '|';
      #ifdef _WIN32 
	Sleep(20);
      #else 
	usleep(20);
      #endif
      bytesread = send(socket_->GetSocketId(), message.c_str(), message.size(), 0); //old file path (full)
      bytesread = recv(socket_->GetSocketId(), buffer, kBufferSize_, 0);
      dirviewer_->SetSelectedFile("");
    }
  }
}

stringvector ClientUI::ReceiveFilesInfo()
{
  stringvector files;
  bool receiving = true;
  char buffer[kBufferSize_] = "\0";
  int bytesread, socketid = socket_->GetSocketId();
  bytesread = send(socketid, buffer, 1 ,0); //confirm connection
  bytesread = recv(socketid, buffer, 1, 0);
  while (receiving)
  {
    int bytessent;
    if ((bytesread = recv(socketid, buffer, kBufferSize_, 0)) < 0) { break; }
    if ((bytessent = send(socketid, buffer, kBufferSize_, 0)) < 0) { break; }
    buffer[bytesread] = '\0';
    files.push_back(buffer);
    if (memcmp(buffer, "--Back---" , SYS_MESSAGE_LEN) == 0) { receiving = false; }
  }
  return files;
}

void ClientUI::ShowMenuHeader(int currentselection)
{
  #ifdef _WIN32
  system("cls");
  #else
  std::cout << "\033[2J\033[1;1H";
  #endif
  std::cout << "Welcome to Remote Commander v. 0.1.\n\n";
  for (stringvector::iterator It = menuoptions_.begin(); It != menuoptions_.end(); ++It)
  {
    if (std::distance(menuoptions_.begin(), It) == currentselection) { std::cout << "-> "; }
    else { std::cout << "   "; }
    std::cout << std::setw(40) << std::left << *It << '\n';
  }
}
void ClientUI::ShowMenu()
{
  size_t currentselectionindex = 0;
  bool inputting = true;
  while (inputting)
  {
    #ifdef _WIN32
    system("cls");
    #else
    std::cout << "\033[2J\033[1;1H";
    #endif
    ShowMenuHeader(currentselectionindex);
    int inputcode = getch();
    #ifdef _WIN32
    if (inputcode == KEY_UP && currentselectionindex != 0) {
      --currentselectionindex;
    } else if (inputcode == KEY_DOWN && currentselectionindex != 2) {
      ++currentselectionindex; 
    }
    #else
    if (inputcode == ARROW_KEY) {
      getch(); //catch useless, but existing second scancode
      inputcode = getch();
      if (inputcode == KEY_UP && currentselectionindex != 0) {
      --currentselectionindex;
      } else if (inputcode == KEY_DOWN && currentselectionindex != 2) {
      ++currentselectionindex; 
      }
    }
    #endif
     else if (inputcode == KEY_O || inputcode == KEY_ENTER) {
      if (currentselectionindex == 0) {
	if (SetupSocket() == SUCCESS) { ViewFileSystem(); }
      } else if (currentselectionindex == 1) {
        #ifdef _WIN32
        system("cls");
        #else
        std::cout << "\033[2J\033[1;1H";
        #endif
        std::cout << "--Key bindings--\n--------------\n";
        std::cout << "O or Enter - perfrom selected or open a folder\n";
        std::cout << "B - return to the previous folder\n";
        std::cout << "X - select file for moving\n";
        std::cout << "V - paste selected file\n";
        std::cout << "Arrow keys - navigate through the file system\n";
        std::cout << "Press any key to return back\n > ";
        getch();
      } else if (currentselectionindex == 2) {
        return;
      }
    }
  }
}
