#include "pfc.h"


void init_PFC(struct PFC * pfc, int id, pid_t pid, function routine, int * pipe_in, int * pipe_out) {
  pfc->id = id;
  pfc->pid = pid;
  pfc->routine = routine;
  pfc->pipe_in = pipe_in;
  pfc->pipe_out = pipe_out;
}

void Mfork(struct PFC *child) {
  child->pid = fork();
  if (child->pid < 0) {perror("[-] Fork Failed\n"); _exit(-1);}
  else if (child->pid > 0) return; 
  else {
      close(child->pipe_in[1]);
      close(child->pipe_out[0]);

      int signal;
      while (true) {
	read(child->pipe_in[0], (int*)&signal, sizeof(int));
	printf("Ho letto la pipe!\n");
	fflush(stdout);
          switch (signal) {
	      case (SIG_ROUTINE):
		read(child->pipe_in[0], (function*)&child->routine, 8);
		child->routine();
		break;
              case (SIG_ABORT): kill(getpid(), SIGINT); break;
       	      case (SIG_FREEZE): break;
          }
      }
  }
}

