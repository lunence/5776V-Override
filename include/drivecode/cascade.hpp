#include "main.h"
#include "drivecode/objects.hpp"

// TODO: dsun modified the cascade cpp to fix bugs
extern float cascadeTarget; //initializes at neutral

extern bool manualControl; 
extern bool autoCascade;
extern double scoreHeights[];

extern void updateCascadeControl();
extern void updateCascadeManual();
extern void updateCascadePID();

extern void runCascadeAuto();