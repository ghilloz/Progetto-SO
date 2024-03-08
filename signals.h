#include "functions.h"

typedef struct Signal {
    int type;
    function routine;
    // 2DO
} Signal;

Signal init_signal(int, function*);
