#include "directoryviewer.h"

void DirectoryViewer::ListDirFiles(const stringvector& files, size_t currenfileindex)
{
  #ifdef _WIN32
  system("cls");
  std::cout << _getcwd(NULL, 0) << "\n-----------------------------\n";
  #else
  std::cout << "\033[2J\033[1;1H";
  std::cout << getcwd(NULL, 0) << "\n------------------------------ \n";
  #endif
  for (stringvector::const_iterator It = files.begin(); It != files.end(); ++It)
  {
    if (std::distance(files.begin(), It) == currenfileindex) { std::cout << "-> "; }
    else { std::cout << "   "; }
    std::cout << std::setw(40) << std::left << *It << '\n';
  }
}

void DirectoryViewer::SetSelectedFile(const std::string& filename)
{
  selectedfile_ = filename;
}

std::string DirectoryViewer::GetSelectedFile()
{
  return selectedfile_;
}

std::pair<std::string, int>  DirectoryViewer::ListDirInfo(stringvector& files)
{
  std::string path, delimiter;
  #ifdef _WIN32
  path = _getcwd(NULL, 0);
  delimiter = "\\";
  #else
  path = getcwd(NULL, 0);
  delimiter = "/";
  #endif
  int currentFileIndex = 0;
  if (files.size() == 1) { std::cout << "Empty...\n"; } //just --back-- option
  size_t currentfileindex = 0;
  ListDirFiles(files, currentfileindex);
  bool inputting = true;
  while (inputting)
  {
    int inputcode = getch(), inputcode2 = 0;
    #ifdef _WIN32
    if (inputcode == 224) { inputcode2 = getch(); }  //inputCode2 used to handle arrow keys
    #else
    if (inputcode == ARROW_KEY) 
    {
      getch(); //catch useless, but existing second scancode
      inputcode2 = getch();
    }
    #endif

    if (inputcode2 == KEY_UP && currentfileindex != 0) {
      ListDirFiles(files, --currentfileindex);
    }
    else if (inputcode2 == KEY_DOWN && currentfileindex < files.size() - 1) {
      ListDirFiles(files, ++currentfileindex);
    }
    else if (inputcode2 == KEY_UP && currentfileindex == 0) {
      currentfileindex = files.size() - 1;
      ListDirFiles(files, currentfileindex);
    }
    else if (inputcode == KEY_O || inputcode == KEY_ENTER) {
      std::string selectedfile(files.at(currentfileindex));
      if (selectedfile.find("...", selectedfile.size() - 3) != std::string::npos) {
        selectedfile.resize(selectedfile.size() - 4);
        if (path.size() == ROOT_LEN) { return PAIR(path + selectedfile, CHANGE_DIR); } //on drive e.g. C:
        else { return PAIR(path + delimiter + selectedfile, CHANGE_DIR); }
      }
      else if (selectedfile == "--Back---") {
        return PAIR(path.substr(0, path.find_last_of("/\\")) + delimiter, CHANGE_DIR);
      }
    }
    else if (inputcode == KEY_B) {
      return PAIR(path.substr(0, path.find_last_of("/\\")) + delimiter, CHANGE_DIR);       //go back
    }
    else if (inputcode == KEY_X) {
      std::string selectedfile(files.at(currentfileindex));
      if (selectedfile.find("...", selectedfile.size() - 3) == std::string::npos) // not a folder
      {
        selectedfile_ = path + delimiter + selectedfile;
      }
      return PAIR(std::string(path), CHANGE_DIR); //nothing changes really
    }
    else if (inputcode == KEY_V && selectedfile_.size()) { //if file already selected
      return PAIR(std::string(path), MOVE_FILE);
    }
  }
}
