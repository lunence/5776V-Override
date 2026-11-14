#include "main.h"
#include "drivecode/dr4b.hpp"
#include "drivecode/claw.hpp"
#include "pros/motors.h"
#include <cmath>

const float maxLiftHeight = 88;
const float minLiftHeight = 0;

float liftHeight;

int manualLiftState = 0;
bool manualControl = false;

// how do i solve this 

void updateManualLift() {
    // if lift manual up pressed
    if (controller.get_digital(liftUp)) {
        manualLiftState = 1;
        manualControl = true;
    } 
    // if lift manual down pressed
    else if (controller.get_digital(liftDown)) {
        manualLiftState = 3;
        manualControl = true;
    } 
    // lift manual was not toggled
    else {
        manualLiftState = 0;
        manualControl = false;
    }

    if (controller.get_digital(liftFullDown)) {
        manualControl = false;
        liftTarget = initialHeight;
    }


    pros::delay(10); 
}

bool reset = false;

//16 degrees to -722
void runLift() {
    while (true) {
        //TODO: UNCOMMENT FOR LIFT LIMITS

        float liftDeg = (liftRot.get_position()/100+3600)%360; //lift.get_position();

        // if liftheight is over the limits AND you want to manual control then do not allow the lift to move past bounds
        if (manualControl && liftDeg >= maxLiftHeight && manualLiftState == 1) {
            manualLiftState = 0;
        }

        if((liftDeg < 8 || liftDeg > 140) && manualLiftState == 0) {
            // manualLiftState = 2;
            // pros::delay(50);
            // manualLiftState = 0;
            //lift.tare_position_all();
            lift.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
            liftRot.set_position(0);
            reset = true;
        }

        // otherwise it's ok to go and lift up/down
        // else {
            switch (manualLiftState) {
                // manual lift off
                case 0: {
                    lift.move_voltage(0);
                    break;
                }

                // manual lift up
                case 1: {
                    lift.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
                    lift.move_voltage(12000);
                    reset = false;
                    break;
                }

                // manual lift down
                case 2: {
                    lift.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
                    lift.move_voltage(-6000);
                    break;
                }

                // half speed
                case 3: {
                    lift.move_voltage(-10000);
                    reset = false;
                    break;
                }

                case 4: {
                    lift.move_voltage(-4000);
                    reset = false;
                    break;
                }
            }
            
            pros::delay(10);
        }
    // }
}