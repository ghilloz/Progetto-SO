/// Process Fork Control Header

#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

#define SIG_ABORT 0
#define SIG_FREEZE 1
#define SIG_ROUTINE 2

struct PFC {
  int id;
  pid_t pid;                         
  void (*routine)();    //process routine function ptr
  int *pipe_in;         //process input pipe (read)
  int *pipe_out;        //process output pipe (write)
};

// Directive type kill, change, mem_free, freeze process
void init_PFC (struct PFC *, int, pid_t, void *, int *, int *);

void Mfork (struct PFC *);
