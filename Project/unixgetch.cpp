#ifndef _WIN32
#include "unixgetch.h"
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


