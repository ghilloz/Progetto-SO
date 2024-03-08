#include <stdio.h>
#include "pfc.h"

#define X 50

int main () {
  PFC child[X];
  int m_pipe[2];
  int c_pipes[X][2];
  
  init_pipe(m_pipe);
  
  for (int i = 0; i < X; i++) {
      printf("Creazione figlio %d\n", child[i].id = i);

      init_pipe(c_pipes[i]);

      init_PFC(&child[i], i, c_pipes[i], m_pipe);

      Mfork(&child[i]);

      close(m_pipe[1]);
      close(child[i].pipe_in[0]);
    }

    for (int i = 0; i < X; i++) {
        getchar();
        function r = &routine;
        Signal s = init_signal(SIG_ROUTINE, (function*)(&r));
      
        write(c_pipes[i][1], (Signal *)&s, sizeof(Signal));
        getchar();
        s = init_signal(SIG_ABORT, (function*)NULL);
        write(c_pipes[i][1], (Signal*)&s, sizeof(Signal));
	close(c_pipes[i][1]);
    }

    return (0);
}
