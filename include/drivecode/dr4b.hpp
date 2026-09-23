#include "pros/misc.h"
#include "drivecode/objects.hpp"
#include "main.h"

extern float liftTarget; //initializes at neutral

extern bool manualControl; 
extern bool autoLift;
extern double scoreHeights[];
extern bool liftMacro;
extern const int topStack;

extern void updateCascadeControl();
extern void updateCascadeManual();
extern void updateCascadePID();

extern void runCascadeAuto();