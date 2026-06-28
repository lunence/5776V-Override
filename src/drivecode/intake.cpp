#include "drivecode/intake.hpp"
#include "pros/misc.h"
#include "drivecode/objects.hpp"

int intakeState = 0;

bool intakePressed = false;

void updateIntake() {
    // if intake control is pressed
    if (controller.get_digital(intakeControl)) {
        if (!intakePressed) {
            // if it is intakking turn it outtake
            if(intakeState == 1) {
                intakeState = 2;
            }
            // if it is outtaking turn it off
            if(intakeState == 2) {
                intakeState = 0;
            }
            // if it is off turn it intaking
            if(intakeState == 0) {
                intakeState = 1;
            }
        }
        // intake was just toggled just now
        intakePressed = true;

    } 
    // intake was not toggled just now
    else {
        intakePressed = false;
    }
}

void runIntake() {
    while (true) {
        // based on our intake state, we toggle it on or off
        switch (intakeState) {
            // intaking
            case 1:
                intake.move_velocity(200);
            // outtaking
            case 2:
                intake.move_velocity(-200);
            // off
            case 0:
                intake.move_velocity(0);
        }
    }
}