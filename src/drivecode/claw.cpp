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
    // hold, not toggle control
    if (controller.get_digital(clawControl)) { 
        // claw open
        clawState = 0;
    }
    else {
        //claw closed
        clawState = 1;
    }
}

void runClaw() {
    while(true) {
        switch(clawState) {
            case 0: { // claw open with rollers
                clawPiston.set_value(false);
                clawRoller.move_velocity(200);
            }
            case 1: { //claw closed w/o rollers
                clawPiston.set_value(true);
                clawRoller.move_velocity(0); 
            }

        }
    }
}