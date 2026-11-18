#include "main.h"
#include "drivecode/objects.hpp"

// initialize motors
extern void motorInit();

// sensor settings
extern void sensorInit();

// begin all tasks
extern void taskInit();

// print screen task
extern void runScreen();

// gamepad task
extern void runConsole();

extern void liftPIDTuning(float target);
extern void linearPIDTuning(float target);
extern void angularPIDTuning(float target);