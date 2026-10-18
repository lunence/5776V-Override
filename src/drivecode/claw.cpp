#include "drivecode/claw.hpp"
#include "drivecode/objects.hpp"

int clawState = 0;
bool clawPressed = false;

void updateClaw() {
    if (controller.get_digital(CONTROL1)) {
        if (!clawPressed) {
            // if it is rolling in turn it rolling out
            if (clawState == 1) {
                clawState = 2;
            }
            // if it is rolling out turn it off
            if (clawState == 2) {
                clawState = 0;
            }
            // if it is off turn it rolling in
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

            // claw rolling in
            case 1: {
                clawRoller.move_voltage(12000);
                break;
            }

            // claw rolling out
            case 2: {
                clawRoller.move_voltage(-6000);
                break;
            }
        }
        
        pros::delay(10);
    }
}