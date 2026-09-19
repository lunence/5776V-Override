#include "drivecode/claw.hpp"
// #include "pros/misc.h"
#include "drivecode/objects.hpp"

// initialize state variables
int rollerState = 0;
bool rollerPressedIn = false;
bool rollerPressedOut = false;

int clawState = 0;
bool clawPressed = false;

void updateManualClaw() {
    if (controller.get_digital(clawControl)) {
        // claw open
        clawState = 0;
    }
    else {
        clawState = 1;
    }
}

void runClaw() {
    switch(clawState) {
        case 0: {
            clawPiston.set_value(false);
            clawRoller.move_velocity(200);
        }
        case 1: {
            clawPiston.set_value(true);
            clawRoller.move_velocity(0); 
        }

    }
}