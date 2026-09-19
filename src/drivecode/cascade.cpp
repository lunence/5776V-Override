#include "drivecode/cascade.hpp"
#include "lemlib/util.hpp"

//set controlType to 1 if you want to use pid
//cascade pid currently inaccessible in driver


bool cbUpPressed = false;
bool cbDownPressed = false;
int controlType = 0; 
double scoreHeights[2][8] = {
    {3.25,10,17,23,30,37.5,43.5,47},
    {5.77,12.5,19,26,32.5,39.5,46,49.5},
};
// manual score height measurements for each pin/cup 

float cascadeHeight = 0;
int currentLevel = 0;
int heightConstant = 0;
int targetInches = 0;
float cascadeTarget = scoreHeights[0][0]; 

void runCascadeManual() {
    if (controller.get_digital(cascadeUpControl)) {
        if (cascadeRotation.get_position() < 100) {
            cascadeFulls.move_velocity(600);
            cascadeHalf.move_velocity(200);
        }
        else {
            cascadeFulls.move_velocity(0);
            cascadeHalf.move_velocity(0);
        }
    }
    
    else if (controller.get_digital(cascadeDownControl)) {
        if (cascadeRotation.get_position() > 0) {
            cascadeFulls.move_velocity(-600);
            cascadeHalf.move_velocity(-200);
        }
        else {
            cascadeFulls.move_velocity(0);
            cascadeHalf.move_velocity(0);
        }
    }
}

void runCascadePID(int goalType) {
    // goalType: 0 is alliance, 1 is neutral
    

    // while cascade is going up
    while (controller.get_digital(cascadeUpControl)) {
        cascadeHeight = lemlib::mmToIn(distCascade.get_distance());
        // tracking the level of pin/cup height that we're at. using integer division to truncate our level down
        currentLevel = static_cast<int>(cascadeHeight / heightConstant);
    }
        // set snap target to the closest score height
        targetInches = scoreHeights[goalType][currentLevel + 1]; 

    // while the current level is less than the target snap 
    while (lemlib::mmToIn(distCascade.get_distance()) < targetInches) { //TODO: cant override with other controls
        runCascadeAuto();
    }
}

void runCascadeAuto() {
    // set cascade height to current height from floor
    // set error to the difference between target and height
    // set power to the power we need to give the cascade to get to target
    float cascadeHeight = lemlib::mmToIn(distCascade.get_distance());
    float error = cascadeTarget - cascadeHeight;
    float power = cascadePID.update(error, true);

    // if power is over/under 127/-127 set to 127/-127 as a bound
    if (std::abs(power) > 127) {
        if (power < 0) {
            // set bounds to -127
            power = -127;
        }
        else  {
            // set bounds to 127
            power = 127;
        }
    }

    // set rpm for each motor to the power divided by 127 multiplied by the rotation
    float fullsRPM = power / 127 * 600;
    float halfRPM = power / 127 * 200;

    // move cascades with their power values
    cascadeFulls.move_velocity(fullsRPM);
    cascadeHalf.move_velocity(halfRPM);
}

void runCascade() {
    // adjust PID target positions based on chainbar states
    while (true) {
        runCascadeManual();
        pros::delay(10);
    }
}