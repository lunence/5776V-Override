#include "drivecode/objects.hpp"
#include "main.h"
#include <cmath>

extern pros::controller_digital_e_t toggleButton;
extern pros::controller_digital_e_t autoToggleButton;
extern int toggleState;

extern char teamColor;
extern bool autoToggle;

extern void updateManualToggle();
extern void updateAutoToggle();
extern void runToggle();