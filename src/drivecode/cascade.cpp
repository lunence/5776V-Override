#include "drivecode/cascade.hpp"
#include "pros/misc.h"
#include "drivecode/objects.hpp"

int cascadeState = 0;
int manualCascadeStateUp = 0;
int manualCascadeStateDown = 0;
int manualChainBarStateUp = 0;
int manualChainBarStateDown = 0;

bool cascadePressed = false;

void updateCascade() {
    // if (controller.get_digital(cascadeToggleControl)) {
    if (true) {
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

    if (controller.get_digital(manualCascadeControlUp)) {
        manualCascadeStateUp = 1;
    } else {
        manualCascadeStateUp = 0;
    }

    if (controller.get_digital(manualCascadeControlDown)) {
        manualCascadeStateDown = 1;
    } else {
        manualCascadeStateDown = 0;
    }

    if (controller.get_digital(manualChainBarControlUp)) {
        manualChainBarStateUp = 1;
    } else {
        manualChainBarStateUp = 0;
    }

    if (controller.get_digital(manualChainBarControlDown)) {
        manualChainBarStateDown = 1;
    } else {
        manualChainBarStateDown = 0;
    }
}

void runCascade() {
    while (true) {
        // macro cascade
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
            
        // micro cascade
        if (manualCascadeStateUp == 1) {
            cascadeL.move_velocity(50);
            cascadeR.move_velocity(50);
        } if (manualCascadeStateDown == 1) {
            cascadeL.move_velocity(-50);
            cascadeR.move_velocity(-50);
        } else {
            cascadeL.move_velocity(0);
            cascadeR.move_velocity(0);
        }
            
        // micro chain bar
        if (manualChainBarStateUp == 1) {
            cascadeL.move_velocity(50);
            cascadeR.move_velocity(50);
        } 
        if (manualCascadeStateDown == 1) {
            cascadeL.move_velocity(-50);
            cascadeR.move_velocity(-50);
        } else {
            cascadeL.move_velocity(0);
            cascadeR.move_velocity(0);
        }

        pros::delay(10);
    }
}