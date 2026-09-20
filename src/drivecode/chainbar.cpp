#include "drivecode/chainbar.hpp"
#include "drivecode/cascade.hpp"
#include "drivecode/claw.hpp"
#include "pros/misc.h"
#include <iostream>
#include <cmath>

int chainBarState = 0;
bool cbUpPressed = false;
bool cbDownPressed = false;

int targetPos = 0;

int downPos = 2;
int loadPos = 25;
int lowerScorePos = 260;
int upperScorePos = 200;

void updateChainBarManual() {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            chainBar.move_voltage(12000);
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            chainBar.move_voltage(-12000);
    } else {
        chainBar.move_voltage(0);
    }
}

void updateChainBar() {
    // if the chain bar up is pressed
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        if (!cbUpPressed) {
            // if not current pressed, ++ to chain bar state
            chainBarState += 1;
            // make sure chainBarstate is capped at 3
            chainBarState = std::min(chainBarState, 3);
        }
        cbUpPressed = true;
        // set toggle pressed to true so holding doesn't change states
    } else cbUpPressed = false;
    // if controller didn't pressed chainbar up, keep it false so code doesnt triggger

    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        // if chain bar down is pressed
        if (!cbDownPressed) {
            // check if its already been pressed
            chainBarState -= 1;
            // cap chainbarstate to 0
            chainBarState = std::max(chainBarState, 0);
            //close claw on way back
            //clawState = 0;
        }
        cbDownPressed = true;
        // if chain bar down as already been pressed, then set back to false
    } else cbDownPressed = false;
}

void runChainBar() {
    // adjust PID target positions based on chainbar states
    
    while(true) {
        switch(chainBarState) {
            case(0): {
                targetPos = downPos;
                break;
            }
            case(1): {
                targetPos = loadPos;
                break;
            }
            case(2):{ 
                targetPos = upperScorePos;
                break;
            }
            case(3): {
                targetPos = lowerScorePos;
                break;
            }
        }

        float pos = chainBarRotation.get_angle()/100.0;
        // get current chain bar rotation

        float error = targetPos - pos;
        std::cout<<"error: "<<error<<std::endl;

        // //start - increase power to go over
        // if(pos > 75 && pos < 170) {
        //     error += pos-75;
        // }
        // //end

        // calculate your error

        float power = chainBarPID.update(error, true);
        std::cout<<"power: "<<power<<std::endl;

        // calculate the PIDOutput based on error
        if(std::abs(error) < 2) power = 0;
        
        //here
        if(std::abs(power) > 127) {
            // if the pid output is greater than motor threshold
            // calculate what direction the chainbar must move
            // then set it to max volts to motors
            if(power < 0) {
                power = -127;
            } else {
                power = 127;
            }
        }


        chainBar.move(power);
        // make it move to the PID output
        pros::delay(10);
    }
        
}