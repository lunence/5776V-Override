#include "pros/misc.h"
#include "drivecode/objects.hpp"
#include "main.h"

extern const int macroMaxDist;
extern const int goalOpticRange;

extern std::vector<float> allianceGoalHeights;
extern std::vector<float> neutralGoalHeights;

extern float liftHeight;

extern bool liftMacroPressed;
extern int liftMacroState;

extern float closestGoalValue(const std::vector<float> &goaldistHeights, float distHeight);
extern void updateLift();
extern void macroLift();
extern void runLiftAuto(float liftTarget);