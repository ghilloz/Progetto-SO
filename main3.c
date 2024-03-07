#include "pfc.h"
#include <fcntl.h>

int main () {
  int pipe_fd[2];
  int x = SIG_FREEZE;

  printf("%d",x);

  struct PFC child;
  Mfork(&child);
  int f = fcntl(pipe_fd[0], F_GETFL, 0);
  close(pipe_fd[0]);
  printf("%d",f);
  f |= O_NONBLOCK;
  printf("%d", f);
  fflush(stdout);
  while (true) {
      write(pipe_fd[1], (int*)&x, sizeof(int));
      getchar();
  }    

  
  
}
