#include "drivecode/cascade.hpp"
#include "pros/misc.h"
#include "drivecode/objects.hpp"

// cascade state variable
// cascadeState = 0: sensing is OFF
// cascadeState = 1: sensing is ON
int cascadeState = 0;

// boolean to track if cascade was just pressed now
// since we haven't pressed it earlier, it's off at the start
bool cascadePressed = false;

// boolean to track if the manual override is overriding
// get it? override?
bool manualOverride = false;

// boolean to track if macro is running
bool macroIsOn = false;

void updateCascade() {
    // if my certain button is pressed
    if (controller.get_digital(cascadeToggleControl)) {
        if (!cascadePressed) {
            // if at zero, change to one, if at one, change to zero
            // the two is the total number of states, the +1 refers to
            // the state coming up, so 2 would be 0 because that's the next state 
            cascadeState = (cascadeState + 1) % 2;
        }
        
        // cascade button just pressed
        cascadePressed = true;
    } else {
        // cascade button not just pressed
        cascadePressed = false;
    }
}


// macro cascade program
void runCascade() {
    while (true) {
        // cascade dist sensor sensing is OFF
        if (cascadeState == 0 && manualOverride == false) { 
            // don't move if it's off
            macroIsOn = false;
            cascadeL.move_velocity(0);
            cascadeR.move_velocity(0);
            break;
        }
        else if (cascadeState == 1 && manualOverride == false) {
            macroIsOn = (distCascade.get() <= 254 && distCascade.get() >= 1);

            // if the cascade distance sensor is within 1-254mm, and it is not overriden by manuals
            if (macroIsOn) { // less than 10 in away
                // move if it is in the range
                cascadeL.move_velocity(200);
                cascadeR.move_velocity(200);
            }
            // if not in the range, it will cease to move until further sensor results
            else {
                cascadeL.move_velocity(0);
                cascadeR.move_velocity(0);
            }
        }
        else {
            break;
        }

        pros::delay(10);
    }
}

void runManual() {
    // if manual control for cascade up pressed
    if (controller.get_digital(manualCascadeControlUp)) {
        // cascade move up
        cascadeL.move_velocity(200);
        cascadeR.move_velocity(200);
        manualOverride = true;
    }

    // if manual control for cascade down pressed
    else if (controller.get_digital(manualCascadeControlDown)) {
        // cascade move down
        cascadeL.move_velocity(-200);
        cascadeR.move_velocity(-200);
        manualOverride = true;
    }

    // if no manual controls for cascade pressed
    else if (manualOverride && !controller.get_digital(manualCascadeControlUp) || !controller.get_digital(manualCascadeControlDown) ){
        // stop providing power to cascade
        cascadeL.move_velocity(0);
        cascadeR.move_velocity(0);
        manualOverride = false;
    }

    // if manual control for chain bar up pressed
    if (controller.get_digital(manualChainBarControlUp)) {
        // chain bar rotate forwards
        chainBar.move_velocity(200);
        manualOverride = true;
    }

    // if manual control for chain bar down pressed
    else if (controller.get_digital(manualChainBarControlDown)) {
        // chain bar rotate backwards
        chainBar.move_velocity(-200);
        manualOverride = true;
    }

    // if no manual controls for chain bar pressed
    else if (manualOverride && !controller.get_digital(manualChainBarControlUp) || !controller.get_digital(manualChainBarControlDown) ){
        // stop providing power to cascade
        chainBar.move_velocity(0);
    }
}