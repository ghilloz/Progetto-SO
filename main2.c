#include "pfc.h"

int main () {
  int pipe_in[2];
    int pipe_out[2];
  struct PFC child;
  if (pipe(pipe_in) < 0) exit(-1);
  if (pipe(pipe_out) < 0) exit(-1);
  child.id = 1;
  child.pipe_in = pipe_in;
  child.pipe_out = pipe_out;
  Mfork(&child);
  close(pipe_out[1]);
  close(pipe_in[0]);

  int signal = SIG_ROUTINE;
  function send = routine;

  write(pipe_in[1], &signal, sizeof(int));
  write(pipe_in[1], (function)&send, 8);

  signal = SIG_ABORT;

  write(pipe_in[1], (int*)&signal, sizeof(int));

  return 1;
}
