#include "drivecode/mascade.hpp"
#include "pros/misc.h"
#include "drivecode/objects.hpp"

bool macronPressed = false;
bool topStack = false;
bool macron = false;

void updateMacron() {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
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
    
    if (macron) topStack = true;

    while (macron && dist >= 1 && dist <= 300) {
        topStack = false;
        dist = distCascade.get();
    }
}

void runMascade() {
    if (!macron) return;

    while (macron && !topStack) {
        cascadeL.move_velocity(600);
        cascadeR.move_velocity(600);
    }

    cascadeL.move_velocity(0);
    cascadeR.move_velocity(0);
}
