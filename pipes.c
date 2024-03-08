#include "pipes.h"

void init_pipe (int * p) {
  if (pipe(p) < 0) {
    perror("Pipe creation failed\n");
    exit(-1);
  }
};
