/// Process Fork Control Header

#include "pipes.h"
#include <stdbool.h>
#include <sys/wait.h>
#include <stdio.h>
#include "routines.h"
#include "signals.h"

#define SIG_ABORT 0
#define SIG_FREEZE 1
#define SIG_ROUTINE 2

typedef struct PFC {
  int id;
  pid_t pid;                         
  function routine;    //process routine function ptr
  int *pipe_in;         //process input pipe (read)
  int *pipe_out;        //process output pipe (write)
} PFC;

// Directive type kill, change, mem_free, freeze process

void init_PFC (PFC *, int, int *, int *);

void Mfork (PFC *);
