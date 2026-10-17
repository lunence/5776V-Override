#include "drivecode/claw.hpp"
#include "drivecode/objects.hpp"

int clawState = 0;
bool clawPressed = false;

void updateClaw() {
    if (controller.get_digital(CONTROL1)) {
        if (!clawPressed) {
            // if it is on turn it off
            if (clawState == 1) {
                clawState = 0;
            }
            // if it is off turn it on
            else {
                clawState = 1;
            }
        }
        clawPressed = true;
    } 
    else {
        clawPressed = false;
    }

    pros::delay(10);
}

void runClaw() {
    while (true) {
        switch (clawState) {
            // claw off
            case 0: {
                clawRoller.move_voltage(0);
                break;
            }

            // claw rolling
            case 1: {
                // not as fast so it doesn't
                // fall over or anything
                clawRoller.move_voltage(6000);
                break;
            }
        }
        
        pros::delay(10);
    }
}