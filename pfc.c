#include "pfc.h"

void init_PFC(struct PFC * pfc, int id, pid_t pid, void * routine, int * pipe_in, int * pipe_out) {
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
	printf("sono il figlio aspetto un segnale..");
	while(read(child->pipe_in[0], &signal, sizeof(int)) < 0) usleep(1000);   
          switch (signal) {
	      case (SIG_ROUTINE): 
		read(child->pipe_in[0], &child->routine, sizeof(void*()));
		child->routine(child);
	        break;
              case (SIG_ABORT): kill(getpid(), SIGINT); break;
       	      case (SIG_FREEZE): break;
          }
      }
  }
}
