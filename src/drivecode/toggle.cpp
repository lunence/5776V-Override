#include "drivecode/toggle.hpp"
#include "drivecode/objects.hpp"

const int toggleOpticRange = 30;
int toggleState = 0;

void updateToggle() {
    // if toggle optical sensor sees a toggle
    if (toggleOptical.get_proximity() <= 100) {
        // if toggle optical color is within the appropriate range 
        // TODO: NEEDS TO BE FIXED SO IT CHECKS IF IT'S OUR ALLIANCE COLOR
        if (!(toggleOptical.get_hue() > 100 + toggleOpticRange && toggleOptical.get_hue() < 100 - toggleOpticRange)) {
            toggleState = 1;
        }
        else {
            toggleState = 0;
        }
    }

    pros::delay(10);
}

void runToggle() {
    while (true) {
        switch (toggleState) {
            // toggle off
            case 0: {
                toggleRoller.move_voltage(0);
                break;
            }

            // toggle rolling
            case 1: {
                toggleRoller.move_voltage(12000);
                break;
            }
        }
        
        pros::delay(10);
    }
}