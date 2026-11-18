#include "drivecode/objects.hpp"
#include "main.h"
#include <cmath>
#include "drivecode/claw.hpp"
#include <vector>

// // TODO: MODIFY THESE BASED ON ACTUAL ROBOT OR DISTANCE FROM CAD
// extern const int macroMaxDist;
// extern const int goalOpticRange;

extern const float maxLiftRot;
extern const float errorRange;

extern float target;
extern float liftPos;

extern int manualLiftState;
extern bool manualControl;
extern bool override;

extern void updateManualLift();
extern void runLift();