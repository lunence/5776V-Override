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

void runCascade() {
    while (true) {
        switch (cascadeState) {
            // cascade dist sensor sensing is OFF
            case 0: 
                // don't move if it's off
                cascadeL.move_velocity(0);
                cascadeR.move_velocity(0);
                break;

            // cascade dist sensor sensing is ON
            case 1:
                // if the cascade distance sensor is within 1-254mm
                if (distCascade.get() <= 254 && distCascade.get() >= 1) { // less than 10 in away
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
        pros::delay(10);
    }
}