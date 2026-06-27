#include "drivecode/cascade.hpp"
#include "pros/misc.h"
#include "drivecode/objects.hpp"

int cascadeState = 0;

bool cascadePressed = false;

void updateCascade() {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        if (!cascadePressed) {
            if (cascadeState == 0) {
                cascadeState = 1;
            } else {
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
                cascade.move_velocity(200);
            } else {
                cascade.move_velocity(0);
            }
        } else {
            cascade.move_velocity(0);
        }

        pros::delay(10);
    }
}