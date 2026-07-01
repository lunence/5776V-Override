#include "main.h"
#include "drivecode/objects.hpp"

extern int flipState;
extern bool flipManualOverride;
extern bool flipTogglePressed;

extern bool clawClosePressed;
extern int clawCloseState;

extern char color;
extern pros::vision_signature_s_t colorSig;
extern uint16_t detected;
extern char detectedStr;

void updateFlip();
void runFlip();