#include "drivecode/flip.hpp"
#include "pros/misc.h"
#include "drivecode/objects.hpp"
#include "drivecode/pistons.hpp"

// flipstate for what color we're locating
// 0 yellow 1 red 2 blue
int flipState = 0;
bool flipManualOverride = false;
bool flipTogglePressed = false;

bool clawClosePressed = false;
bool clawCloseState = 0;

char 

// clawrotatecontrol is a placholder for the color change
void updateFlip() {
    // color change
    if (controller.get_digital(clawRotateControl)) {
        if (!flipTogglePressed) {
            flipState = (flipState + 1) % 3;
        }
        flipTogglePressed = true;
    } else {
        flipTogglePressed = false;
    }

    // claw close detection
    if (controller.get_digital(clawCloseControl)) {
        if (!clawClosePressed) {
            if (clawCloseState == 0) {
                clawCloseState = 1;
            } else {
                clawCloseState = 0;
            }
        }
        clawClosePressed = true;
    } else {
        clawClosePressed = false;
    }
}

void runFlip() {
    while (true) {
        switch (flipState) {
            case 0:
                // yellow
                color = "Y";
                controller.print(0, 0, "Color: %d", color);
            case 1:
                // red
                color = "R";
                controller.print(0, 0, "Color: %d", color);
            case 2:
                // blue
                color = "B";
                controller.print(0, 0, "Color: %d", color);
        }

        //  check if the largest color 
        if (vision.get_by_size(0).signature != colorSig) {
            flip it i suppose
        }
        
    }
}