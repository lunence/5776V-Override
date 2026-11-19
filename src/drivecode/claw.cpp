#include "drivecode/claw.hpp"
#include "drivecode/objects.hpp"

int clawState = 0;
bool clawSpinPressed = false;

void updateClaw() {
    // constantly checks if clawButton held; if not then set claw to temp roller
    if (controller.get_digital(clawOpen)) {
        clawState = 2;
    } else if (clawState != 1) clawState = 0;
    
    if (controller.get_digital(clawSpin)) {

        if (!clawSpinPressed) {
            // if it is not rolling in turn it rolling in
            if (clawState != 1) clawState = 1;

            // if it is rolling in turn it off
            else if (clawState == 1) clawState = 0;
        }

        clawSpinPressed = true;
    } 
    else clawSpinPressed = false;
}

void runClaw() {
    while (true) {
        switch (clawState) {
            // claw off
            case 0: {
                claw.move_voltage(0);
                break;
            }

            // spin in, full power
            case 1: {
                claw.move_voltage(12000);
                break;
            }

            // open claw, half power
            case 2: {
                claw.move_voltage(-6000);
                break;
            }

            // retain intake, quarter power
            case 3:  {
                claw.move_voltage(3000);
                break;
            }
        }
        
        pros::delay(10);
    }
}