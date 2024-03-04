/// Process Fork Control Header

struct PFC {
  int id;
  pid_t pid;                         
  void (*routine)();              //process routine function ptr
  int *pipe_in;                   //process input pipe (read)
  int *pipe_out;                  //process output pipe (write)
};

struct PoolP {
  int size;          //dimension of the pool 
  struct PFC* items;
};

// Directive type kill, change, mem_free, freeze process
enum DirType {KILL, CHNG, FREE, FRZ};

