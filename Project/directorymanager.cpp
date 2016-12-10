#include "directorymanager.h"

void DirectoryManager::ListDirFiles(const stringvector& files, size_t currenfileindex)
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

stringvector DirectoryManager::FillVectorOfFiles()
{
  stringvector files;
  #ifdef _WIN32
  struct _finddata_t* currentfile = new struct _finddata_t;
  intptr_t filehandle;
  if ((filehandle = _findfirst("*.*", currentfile)) == -1L) { return files; }
  do
  {
    if (currentfile->name[0] == '.' || currentfile->attrib & _A_SYSTEM) { continue; }
    files.push_back(currentfile->name);
    if (currentfile->attrib & _A_SUBDIR) { files.back().append(" ..."); }
  } while (_findnext(filehandle, currentfile) == SUCCESS);
  _findclose(filehandle);
  #else
  DIR *directory;
  struct dirent *sysdirent;
  directory = opendir(getcwd(NULL, 0));
  while ((sysdirent = readdir (directory)) != NULL) 
  { 
    if (sysdirent->d_name[0] == '.') { continue; }
    files.push_back(sysdirent->d_name); 
    if (sysdirent->d_type == DT_DIR) { files.back().append(" ..."); }
  }
  #endif
  files.push_back("--Back---");
  return files;
}

int DirectoryManager::MoveFileOnRemote(std::string& filepath, std::string& newpath)
{
  #ifdef _WIN32
  std::ifstream oldpathstream(filepath);
  if (!oldpathstream) { return ERROR; }
  std::ofstream newfilestream(newpath);
  if (!newfilestream) { return ERROR; }
  char tempsymbol;
  bool writing = true;
  while (writing)
  {
    oldpathstream >> tempsymbol;
    if (oldpathstream.eof()) { break; }
    newfilestream << tempsymbol;
  }
  oldpathstream.close();
  newfilestream.close();
  remove(filepath.c_str());
  #else
  FILE* pathold, *pathnew;
  char buffer[5];
  int readingflag;
  pathold = fopen(filepath.c_str(), "rb");
  pathnew = fopen(newpath.c_str(), "wb");
  while (readingflag = fread(buffer, 1, 5, pathold)) { fwrite(buffer, 1, readingflag, pathnew);}
  fclose(pathold);
  fclose(pathnew);
  unlink(filepath.c_str());
  #endif
  return SUCCESS;
}
