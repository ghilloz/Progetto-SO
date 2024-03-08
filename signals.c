#include "signals.h"

Signal init_signal (int type, function* fun/* 2DO */) {
  Signal s;

  s.type = type;

  if (fun) s.routine = *fun;
  else s.routine = (function)0;
    
  return s;
}
