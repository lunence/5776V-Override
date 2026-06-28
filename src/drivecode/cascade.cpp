#include "drivecode/cascade.hpp"
#include "pros/misc.h"
#include "drivecode/objects.hpp"

int cascadeState = 0;

bool cascadePressed = false;

void updateCascade() {
    if (controller.get_digital(cascadeToggleControl)) {
        if (!cascadePressed) {
            if (cascadeState == 0) {
                cascadeState = 1;
            } if (cascadeState == 1) {
                cascadeState = 2;
            } if (cascadeState == 2) {
                cascadeState = 0;
            }
        }
        
        cascadePressed = true;
    } else {
        cascadePressed = false;
    }
}

void runCascade() {
    while (true) {
        if (cascadeState == 1) {
            if (distCascade.get() < 254) { // less than 10 in away
                cascadeL.move_velocity(200);
                // cascadeR.move_velocity(200);
                chainBar.move_velocity(0);
            } else {
                cascadeState = 2;
            }
        
        } if (cascadeState == 2) {
            cascadeL.move_velocity(0);
            // cascadeR.move_velocity(0);
            chainBar.move_velocity(100);
        }

        if (cascadeState == 0) {
            cascadeL.move_velocity(0);
            // cascadeR.move_velocity(0);
            chainBar.move_velocity(0);
        }

        pros::delay(10);
    }
}