#include <stdlib.h>
#include <stdio.h>
typedef void (*function) ();

void fn () {
  printf("PORCODDIO");
};

int main () {
  function routine;
  routine();
  return 1;
}
