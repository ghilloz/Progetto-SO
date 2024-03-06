#include <stdio.h>
#include "pfc.h"

#define X 10


void fn(struct PFC *p) {
  int out = getpid(),
      in;
  printf("Indirizzo logico figlio: %p\n", &(p->id));
  printf("SONO IL FIGLIO :: PID_%d\n", out);

  write(p->pipe_out[1], (const void*)&out, sizeof(int));
  read(p->pipe_in[0], (void*)&in, sizeof(int));
}


int main () {
  struct PFC child[X];
  int m_pipe[2];
  int c_pipes[X][2];
  
  if (pipe(m_pipe) == -1) {
    perror("[-] Pipe creation failed");
    exit(-1);
  }

  
  for (int i = 0; i < X; i++) {
    printf("Creazione figlio %d\n", i);
    
    child[i].id = i;

    if (pipe(c_pipes[i]) == -1) {
      perror("[-] Pipe creation failed");
      exit(-1);
    }
    
    child[i].pipe_in = c_pipes[i];
    child[i].pipe_out = m_pipe;
    Mfork(&child[i]);
    close(m_pipe[1]);
    close(child[i].pipe_in[0]);
    
    int signal = SIG_ROUTINE;
      getchar();
      write(c_pipes[i][1], (int*)&signal, sizeof(int));
      write(c_pipes[i][1], (function)&routine, sizeof(function));
    /*
      printf("Figlio creato | pid %d | id %d | logic_add %p\n", child[i].pid, child[i].id, &(child[i].id)); */
  }

  /*
  close(m_pipe[1]);
  for (int i = 0; i < X;) {
    int buf, bytes, out = 1;
    
    if (bytes = (read(m_pipe[0], (void*)&buf, sizeof(int)))) {
      printf("pid : %d, bytes : %d\n", buf, bytes);
      write(c_pipes[i][1], (const void*)&out, sizeof(int));
      i++;
    }
  }

  int stat_loc, tmp;
  while ((tmp = wait(&stat_loc)) != -1)
    printf("%d\n", tmp);
  */

  return (0);
}
