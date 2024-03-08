#include "pfc.h"

void init_PFC(PFC * pfc, int id, int * pipe_in, int * pipe_out) {
  pfc->id = id;
  pfc->routine = routine;
  pfc->pipe_in = pipe_in;
  pfc->pipe_out = pipe_out;
}

void Mfork(PFC *child) {
  child->pid = fork();
  if (child->pid < 0) {perror("[-] Fork Failed\n"); _exit(-1);}
  else if (child->pid > 0) return; 
  else {
      close(child->pipe_in[1]);
      close(child->pipe_out[0]);

      Signal signal;
      while (true) {
	  read(child->pipe_in[0], (Signal*)&signal, sizeof(Signal));
	  printf("Segnale ricevuto : %d  %p", signal.type, signal.routine);
	  fflush(stdout);
	  child->routine = signal.routine;
          switch (signal.type) {
	      case (SIG_ROUTINE):
		  child->routine();
		  break;
              case (SIG_ABORT):
		  kill(getpid(), SIGINT);
		  break;
	  case (SIG_FREEZE): break;
          }
      }
  }
}

