#include "drivecode/mascade.hpp"
#include "pros/misc.h"
#include "drivecode/objects.hpp"


bool macronPressed = false;

void updateMacron() {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        if (!macronPressed) {
            macron = !macron;
        }
        macronPressed = true;
    } else {
        macronPressed = false;
    }
}

void updateTopStack() {
    if (!macron) return;

    int dist = distCascade.get();

    while (macron && dist >= 1 && dist <= 300) {
        topStack = false;
        dist = distCascade.get();
    }

    if (macron) topStack = true;
}

void runCascade() {
    if (!macron) return;

    while (macron && !topStack) {
        cascadeL.move_voltage(12000);
        cascadeR.move_voltage(12000);
    }

    cascadeL.move_voltage(0);
    cascadeR.move_voltage(0);
}




