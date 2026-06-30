#include "main.h"
#include "drivecode/objects.hpp"

// cascade state variable
// cascadeState = 0: sensing is OFF
// cascadeState = 1: sensing is ON
extern int cascadeState;

// boolean to track if cascade was just pressed now
// since we haven't pressed it earlier, it's off at the start
extern bool cascadePressed;

void updateCascade();
void runCascade();