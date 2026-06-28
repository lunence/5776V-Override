#include "drivecode/pistons.hpp"
#include "drivecode/intake.hpp"
#include "pros/misc.h"
#include "drivecode/objects.hpp"

int clawRotateState = 0;       // 0 down
int clawCloseState = 0;       // 0 down

bool clawRotatePressed = false;
bool clawClosePressed = false;

void updatePistons() {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        if (!clawRotatePressed) {
            if (clawRotateState == 0) {
                clawRotateState = 1;
            } else {
                clawRotateState = 0;
            }
        }
        clawRotatePressed = true;
    } else {
        clawRotatePressed = false;
    }
    
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        if (!clawClosePressed) {
            if (clawCloseState == 0) {
                clawCloseState = 1;
            } else {
                clawCloseState = 0;
            }
        }
        clawClosePressed = true;
    } else {
        clawClosePressed = false;
    }
}

void runPistons() {
    while (true) {
        if (clawRotateState == 0) {
            pistonClawRotate.set_value(false);
        } else if (clawRotateState == 1) {
            pistonClawRotate.set_value(true);
        }   
    
        if (clawCloseState == 0) {
            pistonClawClose.set_value(false);
        } else if (clawCloseState == 1) {
            pistonClawClose.set_value(true);
        }   
    }
}