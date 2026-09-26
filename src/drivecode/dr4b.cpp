#include "main.h"
#include "drivecode/dr4b.hpp"
#include "drivecode/objects.hpp"
#include "pros/optical.hpp"
#include <iostream>
#include <cmath>
#include <vector>

const int macroMaxDist = 0;
const int goalOpticRange = 0;


//float scoreHeights[2][8] = {
//    {3.25,10,17,23,30,37.5,43.5,47},
//    {5.77,12.5,19,26,32.5,39.5,46,49.5},
//};
// TODO: GET THE VALUES FOR THESE FROM THE CODE IN #harbor_bot
std::vector<float> allianceGoalHeights = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
std::vector<float> neutralGoalHeights = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

// SOPHIYA USE THIS TO SET CURRENT GOAL HEIGHTS TO ALLIANCE/NEUTRAL GOAL HEIGHTS
// std::vector<float> currentGoalHeights = allianceGoalHeights;

float closestGoalValue(const std::vector<float> &goaldistHeights, float distHeight) {
    // set closest value to the first value as a fallback
    float closest = goaldistHeights[0];

    // iterate through everything in goaldistHeights onwards
    for (int i = 1; i < goaldistHeights.size(); i++) {
        // if the distance from the current value of goaldistHeights is closer:
        if (std::abs(goaldistHeights[i] - distHeight) <= std::abs(closest - distHeight)) {
            // set the closest to the current value of goaldistHeights
            closest = goaldistHeights[i];
        }
    }

    return closest;
}

void updateLift() {
    if (controller.get_digital(liftMacroControl)) {
        if (!liftMacroPressed) {
            // if it is on turn it off
            if(liftMacroState == 1) {
                liftMacroState = 0;
            }

            // if it is off turn it on
            else {
                liftMacroState = 1;
            }
        }
        // intake was just toggled just now
        liftMacroPressed = true;

    } 
    // intake was not toggled just now
    else {
        liftMacroPressed = false;
    }

    pros::delay(10);
}

// float get_hue();


void macroLift() {
    while (true) {
        switch (liftMacroState) {
            // macro is off
            case 0: {
                break;
            }

            // macro is on
            case 1: {
                //Blue goal optical sensor value: 184
                //red goal optical sensor value: 00
                int currentHue = goalOptical.get_hue();
                
                if ((currentHue <= 184 + goalOpticRange && 184 - goalOpticRange <= currentHue) || // blue logic
                    (currentHue <= 2 * goalOpticRange)) {                                         // red logic
                    std::vector<float> currentGoalHeights = allianceGoalHeights;
                } else {
                    std::vector<float> currentGoalHeights = neutralGoalHeights;
                }

                while (lemlib::mmToIn(distLift.get()) <= macroMaxDist) {
                    reversebar.move_voltage(12000);
                }
                reversebar.move_voltage(0); 
                
                // i is write here
                // TODO: FINISH WRITING LOGIC FOR SNAP HERE
                
                liftMacroState = 0;
                break;
            }
        }
    }
}

void runLiftAuto(float liftTarget) {
    float errorRange = 0.00;

    // set cascade height to current height from floor
    // set error to the difference between target and height
    // set power to the power we need to give the cascade to get to target
    float cascadeHeight = lemlib::mmToIn(distLiftHeight.get_distance());
    float error = liftTarget - cascadeHeight;
    float power = liftPID.update(error, true);

    while (std::abs(error) > errorRange) {
        cascadeHeight = lemlib::mmToIn(distLiftHeight.get_distance());
        error = liftTarget - cascadeHeight;
        power = liftPID.update(error, true);

        // if power is over/under 127/-127 set to 127/-127 as a bound
        if (std::abs(power) > 127) {
            if (power < 0) {
                // set bounds to -127
                power = -127;
            }
            else {
                // set bounds to 127
                power = 127;
            }
        }

        if(std::abs(error) < 0.25) {
            return;
        }

        // set rpm for each motor to the power divided by 127 multiplied by the rotation
        float fullsRPM = power / 127 * 600;

        // move cascades with their power values
        reversebar.move_velocity(fullsRPM);

        pros::delay(10);
    }

    return;
}

/*
// TODO: SOMEBODY MADE THIS THING IT IS COMMENTED DUE TO UNCERTAINTY
bool liftMacro = false;
const int topStack = 0;
float targetMacro = 0;

void distLiftMacro() {
    if (liftMacro) {
        // send voltage until dist sensor doesnt see anything
        // it will be seeing the stack while going up
        while (distLift.get_distance() < 10) {
            reversebar.move_voltage(127);
        }

        targetMacro = (distLiftdistHeight.get_distance()/25.4) + topStack;

        // get to the right position to score

        while (targetMacro > (distLiftdistHeight.get_distance()/25.4)) {
            // PID error calculation
            float error = targetMacro - (distLiftdistHeight.get_distance()/25.4);
            float power = reversePID.update(error, false);

            // power
            if(std::abs(power) > 127) {
                // if the pid output is greater than motor threshold
                // calculate what direction the chainbar must move
                // then set it to max volts to motors
                if(power < 0) {
                    power = -127;
                } else {
                    power = 127;
                }
            }
            reversebar.move_voltage(power);
        }

        // then to get to the right distHeight
    
    }
    liftMacro = false;
} 
*/