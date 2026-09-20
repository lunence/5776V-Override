#include "drivecode/claw.hpp"
#include "drivecode/objects.hpp"

int clawState = 0;
bool clawPressed = false;

void updateManualClaw() {
    if (controller.get_digital(clawControl)) { //TODO: replace with actual control
        if (!clawPressed) {
            // modulo fun
            if (clawState != 0) {
                clawState = 0;
            } else {
                clawState = 1;
            }
        }

        clawPressed = true;
    
    } else {
        clawPressed = false;
    }

    // hold, not toggle control
    if (controller.get_digital(clawOpenControl)) { 
        // claw open no roller
        clawState = 2;
    }
        
    pros::delay(10);
}

void runClaw() {
    while(true) {
        if(clawState == 0) {
            clawRoller.move(0);
            clawPiston.set_value(false);
        } else if(clawState == 1) {
            clawRoller.move(127);
            clawPiston.set_value(true);
        } else if(clawState == 2) {
            clawRoller.move(0);
            clawPiston.set_value(true);
        }

        pros::delay(10);
    }
}