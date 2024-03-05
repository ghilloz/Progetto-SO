/// Process Fork Control Header

struct PFC {
  int id;
  pid_t pid;                         
  void (*routine)();    //process routine function ptr
  int *pipe_in;         //process input pipe (read)
  int *pipe_out;        //process output pipe (write)
};

// Directive type kill, change, mem_free, freeze process
enum DirType {KILL, CHNG, FREE, FRZ};

void init_PFC (struct PFC *, int, pid_t, void *, int *, int *);

void Mfork (struct PFC *);
