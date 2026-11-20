#include "main.h"
#include "drivecode/dr4b.hpp"
#include <iostream>

const float maxLiftRot = 87;
const float errorRange = 1.5;

float liftTarget = 0;
float liftPos = 0;

int manualLiftState = 0;
bool manualControl = true; //true and it's manual, false and it's pid
bool overrideMotionLimits = false;

void updateManualLift() {
    // if lift manual up pressed
    if (controller.get_digital(liftUp)) {
        manualLiftState = 1;
    } 

    // if lift manual down pressed
    else if (controller.get_digital(liftDown)) {
        manualLiftState = 2;
    }

    // lift manual was not toggled
    else {
        manualLiftState = 0;
    }

    //override
    if (controller.get_digital(overrideButton)) {
        overrideMotionLimits = true;
    }

    pros::delay(10); 
}

void runLift() {
    float power = 0;
    while (true) {

        // sanitize lift rotation
        liftPos = fmodf(liftRot.get_position() / 100.0f, 360.0f);
        if (liftPos > 180) liftPos -= 360;
        else if (liftPos < -180) liftPos += 360;
        
        if(liftTarget > maxLiftRot)
            liftTarget = maxLiftRot;
        if(liftTarget < 0)
            liftTarget = 0;

        // manual control code
        if(manualControl) {
            // voltage checks
            switch (manualLiftState) {
                // manual lift off
                case 0: {
                    power = 0;
                    break;
                }

                // manual lift up
                case 1: {
                    power = 127;
                    break;
                }

                // manual lift down
                case 2: {
                    power = -127;
                    break;
                }
            }
        }

        // pid control
        else {
            float error = liftTarget - liftPos;
            power = liftPID.update(error, true);
            power = std::clamp(power, -127.0f, 127.0f);

            if(std::abs(error) < errorRange) power = 0;
        }

        // upper limit check
        if(!overrideMotionLimits && liftPos >= maxLiftRot && power > 0) power = 0;
        if(!overrideMotionLimits && liftPos <= -1 && power < 0) power = 0; //lower limit check

        // send power
        lift.move(power);
        
        pros::delay(10);
    }
}