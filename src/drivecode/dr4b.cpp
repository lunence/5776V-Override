#include "main.h"
#include "drivecode/dr4b.hpp"

const float maxLiftRot = 88;
const float errorRange = 2;

float target = 0;
float liftPos = 0;

int manualLiftState = 0;
bool manualControl = false; //true and it's manual, false and it's pid
bool override = false;

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
        override = true;
    }

    pros::delay(10); 
}

void runLift() {
    while (true) {
        float power = 0;

        // sanitize lift rotation
        liftPos = fmodf(liftRot.get_position() / 100.0f, 360.0f);
        if (liftPos > 180) liftPos -= 360;
        else if (liftPos < -180) liftPos += 360;

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
            float error = target - liftPos;
            power = liftPID.update(error, true);
            power = std::clamp(power, -127.0f, 127.0f);

            if(std::abs(error) < errorRange) power = 0;
            else lift.move(power);
        }

        // upper limit check
        if(!override && liftPos >= maxLiftRot && power > 0) power = 0;
        
        //lower limit check
        if(!override && liftLimit.get_value() == 1 && power < 0) power = 0;

        // send power
        lift.move(power);
        
        pros::delay(10);
    }
}