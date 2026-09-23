#include "main.h"
#include "drivecode/dr4b.hpp"
#include "drivecode/objects.hpp"

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

        targetMacro = (distLiftHeight.get_distance()/25.4) + topStack;

        // get to the right position to score

        while (targetMacro > (distLiftHeight.get_distance()/25.4)) {
            // PID error calculation
            float error = targetMacro - (distLiftHeight.get_distance()/25.4);
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

        // then to get to the right height
    
    }
    liftMacro = false;
}