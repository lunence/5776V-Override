#include "drivecode/toggle.hpp"

int toggleState = 0;

const int redUpperLim = 0;
const int redLowerLim = 0;
const int blueUpperLim = 0;
const int blueLowerLim = 0;

char teamColor;

bool autoToggle = false;

void updateManualToggle() {
    if (controller.get_digital(toggleButton)) toggleState = 1;
    else toggleState = 0;
}

void updateAutoToggle() {
    if(controller.get_digital(autoToggleButton)) autoToggle = true;
    else autoToggle = false;
}

void runToggle() {
    while(true) {
        // manual control code
        if(!autoToggle) {
            if(toggleState == 0) toggle.move(0); //state 0 off
            else if(toggleState == 1) toggle.move(127); //state 1 on
        }
    
        // auto toggle code
        else if(autoToggle) {
            float color = toggleOptical.get_hue();
            //if NOT red, keep moving
            if (!(color < redUpperLim && color > redLowerLim) && teamColor == 'R') toggle.move(127);
            //if NOT blue, keep going
            else if (!(color < blueUpperLim && color > blueLowerLim) && teamColor == 'B') toggle.move(127);
            //otherwise stop
            else toggle.move(0);
        }
        pros::delay(10);
    }
}