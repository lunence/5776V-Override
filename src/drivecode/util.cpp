#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "drivecode/util.hpp"
#include "drivecode/objects.hpp"

// motor settings
void motorInit() {
}

// sensor settings
void sensorInit() {}

// initialize all tasks inside of pros task
void taskInit() {
    pros::Task screenTask(runScreen, "screen task");
}

// brain telemetry task
void runScreen() {
    while(true) {
        lemlib::Pose pose = chassis.getPose();

        pros::screen::print(pros::E_TEXT_MEDIUM, 1, "X: %.3f", pose.x);
        pros::screen::print(pros::E_TEXT_MEDIUM, 2, "Y: %.3f", pose.y);
        pros::screen::print(pros::E_TEXT_MEDIUM, 3, "Theta: %.3f", pose.theta);
        pros::screen::print(pros::E_TEXT_MEDIUM, 4, "hi vinish you're now on camera through text");
        
        pros::delay(50);
    }
}

// console task
void runConsole() {
    while(true) {
        pros::delay(50);
    }
}